#include "mysqlConnectionPool.h"
#include <fstream>
#include <thread>
#include <functional>
#include <mutex>
#include <string.h>
#include <errno.h>



MysqlConnectionPool::MysqlConnectionPool() {
    if (loadConfigFile() == false)      { return; }

    // 创建初始数量的连接
    for (int i = 0; i < initSize_; i++) {
        MysqlConnection* mc = new MysqlConnection();
        if (mc->connect(ip_, port_, user_, password_, dbname_) == false) {
            delete mc;
            continue;
        }
        mc->refreshAliveTime();
        mysqlConnectionQueue_.push(mc);
        mysqlConnectionCnt_++;
    }

    // 启动一个新的线程, 作为连接的生产者
    std::thread producer(std::bind(&MysqlConnectionPool::produceMysqlConnectionTask, this));
    producer.detach();

    // 启动一个新的定时线程, 扫描超过maxIdleTime时间的空闲连接, 对其进行回收
    std::thread scanner(std::bind(&MysqlConnectionPool::scanMysqlConnectionTask, this));
    scanner.detach();
}

bool MysqlConnectionPool::loadConfigFile() {
    std::fstream iniFile;
    iniFile.open("mysql.ini", std::ios::in);
    if (iniFile.fail()) {
        std::cout << "Open mysql.ini error: " << strerror(errno) << std::endl;
        return false;
    }
    std::cout << "Open mysql.ini success, ready to get config..." << std::endl;

    while (!iniFile.eof()) {
        char line[1024] = {0};
        iniFile.getline(line, sizeof(line));
        std::string str = line;
        size_t idx = str.find('=', 0);
        if (idx == std::string::npos) { // 无效的配置项
            continue;
        }

        size_t endIdx = str.find('\n', idx);
        std::string key = str.substr(0, idx);
        std::string value = str.substr(idx+1, endIdx - idx -1);

        if (key == "ip") {
            ip_ = value;
        } else if (key == "port") {
            port_ = atoi(value.c_str());
        } else if (key == "user") {
            user_ = value;
        } else if (key == "password") {
            password_ = value;
        } else if (key == "dbname") {
            dbname_ = value;
        } else if (key == "initSize") {
            initSize_ = atoi(value.c_str());
        } else if (key == "maxSize") {
            maxSize_ = atoi(value.c_str());
        } else if (key == "maxIdleTime") {
            maxIdleTime_ = atoi(value.c_str());
        } else if (key == "maxConnectionTimeout") {
            maxConnectionTimeout_ = atoi(value.c_str());
        }
    }
    std::cout << "ip = " << ip_ << " port = " << port_
                 << " user = " << user_ << " password = " << password_ 
                 << " dbname = " << dbname_ << " initSize = "<< initSize_
                 << " maxSize = " << maxSize_ << " maxIdleTime = " << maxIdleTime_
                 << " maxConnectionTimeout = " << maxConnectionTimeout_ << std::endl;
    iniFile.close();
    return true;
}

MysqlConnectionPool* MysqlConnectionPool::getMysqlConnectionPool() {
    static MysqlConnectionPool pool;    // 编译器会 lock unlock 线程安全
    return &pool;
}

std::shared_ptr<MysqlConnection> MysqlConnectionPool::getMysqlConnection() {
    std::unique_lock<std::mutex> lock(queueMutex_);
    while (mysqlConnectionQueue_.empty()) {
        if (cv.wait_for(lock, std::chrono::milliseconds(maxConnectionTimeout_)) == std::cv_status::timeout ) {
            if (mysqlConnectionQueue_.empty()) {
                std::cout << "Get mysql connection timeout, failure." << std::endl;
                return nullptr;
            }
        }
    }

    /**
     * shared_ptr 析构的时候, 会把connection资源直接delete掉, 相当于调用connection的析构函数, 
     * connection就被close掉了.
     * 这里需要自定义shared_ptr的释放资源的方式, 把connection直接归还到queue当中
    */
    std::shared_ptr<MysqlConnection> sp(mysqlConnectionQueue_.front(), 
                                        [&](MysqlConnection* mconn) {
                                            std::unique_lock<std::mutex> lock(queueMutex_);
                                            mconn->refreshAliveTime();
                                            mysqlConnectionQueue_.push(mconn);
                                        });
    
    mysqlConnectionQueue_.pop();
    cv.notify_all();

    return sp;
}

void MysqlConnectionPool::produceMysqlConnectionTask() {
    for(;;) {
        std::unique_lock<std::mutex> lock(queueMutex_);
        while (!mysqlConnectionQueue_.empty()) {
            cv.wait(lock);
        }

        if (mysqlConnectionCnt_ < maxSize_) {
            MysqlConnection* mc = new MysqlConnection();
            mc->connect(ip_, port_, user_, password_, dbname_);
            mc->refreshAliveTime();
            mysqlConnectionQueue_.push(mc);
            mysqlConnectionCnt_++;
        }

        cv.notify_all();
    }
}

void MysqlConnectionPool::scanMysqlConnectionTask() {
    for(;;) {
        std::this_thread::sleep_for(std::chrono::seconds(maxIdleTime_));

        std::unique_lock<std::mutex> lock(queueMutex_);
        while (mysqlConnectionCnt_ > initSize_) {
            MysqlConnection* mc = mysqlConnectionQueue_.front();
            if (mc->getAliveTime() >= (maxIdleTime_*1000)) {
                mysqlConnectionQueue_.pop();
                mysqlConnectionCnt_--;
                delete mc;
            } else {
                break;  // 队头的连接没有超过maxIdleTime_, 其他连接肯定也没有
            }
        }
    }
}