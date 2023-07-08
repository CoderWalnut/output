#include "mysqlConnectionPool.h"
#include <thread>

/*
编译指令：
g++ -o main main.cc mysqlConnection.cc mysqlConnectionPool.cc mysqlConnectionPool.h mysqlConnection.h -lpthread -lmysqlclient -std=c++11
*/

int main() {
    clock_t begin = clock();
#if 0
    // MysqlConnectionPool* mcp = MysqlConnectionPool::getMysqlConnectionPool();
    for (int i = 0; i < 2500; i++) {
            char sql[1024] = {0};
            snprintf(sql, sizeof(sql), "insert into student (name, age, sex) values ('%s', %d, '%s')", 
                                        "zhangshan", 20, "M");
            // 1. 不使用连接池
            // MysqlConnection conn;
            // conn.connect("127.0.0.1", 3306, "root", "123456", "school");
            // conn.exec(sql);

            // 2. 使用连接池
            std::shared_ptr<MysqlConnection> mc = mcp->getMysqlConnection();
            if (mc->exec(sql) == true) {
                // std::cout <<  "Exec sql success: " << sql << std::endl;
            }
        }
#endif
// #if 0

    std::cout << "Start to create thread1..." << std::endl;
    std::thread t1([] () {
        MysqlConnectionPool* mcp = MysqlConnectionPool::getMysqlConnectionPool();
        for (int i = 0; i < 2500; i++) {
            char sql[1024] = {0};
            snprintf(sql, sizeof(sql), "insert into student (name, age, sex) values ('%s', %d, '%s')", 
                                        "zhangshan", 20, "M");
            // 1. 不使用连接池
            // MysqlConnection conn;
            // conn.connect("127.0.0.1", 3306, "root", "123456", "school");
            // conn.exec(sql);

            // 2. 使用连接池
            std::shared_ptr<MysqlConnection> mc = mcp->getMysqlConnection();
            if (mc->exec(sql) == true) {
                // std::cout <<  "Exec sql success: " << sql << std::endl;
            }
        }
    });
    std::cout << "Start to create thread2..." << std::endl;
    std::thread t2([] () {
        MysqlConnectionPool* mcp = MysqlConnectionPool::getMysqlConnectionPool();
        for (int i = 0; i < 2500; i++) {
            char sql[1024] = {0};
            snprintf(sql, sizeof(sql), "insert into student (name, age, sex) values ('%s', %d, '%s')", 
                                        "zhangshan", 20, "M");
            // 1. 不使用连接池
            // MysqlConnection conn;
            // conn.connect("127.0.0.1", 3306, "root", "123456", "school");
            // conn.exec(sql);

            // 2. 使用连接池
            std::shared_ptr<MysqlConnection> mc = mcp->getMysqlConnection();
            if (mc->exec(sql) == true) {
                // std::cout <<  "Exec sql success: " << sql << std::endl;
            }
        }
    });

    std::cout << "Start to create thread3..." << std::endl;
    std::thread t3([] () {
        MysqlConnectionPool* mcp = MysqlConnectionPool::getMysqlConnectionPool();
        for (int i = 0; i < 2500; i++) {
            char sql[1024] = {0};
            snprintf(sql, sizeof(sql), "insert into student (name, age, sex) values ('%s', %d, '%s')", 
                                        "zhangshan", 20, "M");
            // 1. 不使用连接池
            // MysqlConnection conn;
            // conn.connect("127.0.0.1", 3306, "root", "123456", "school");
            // conn.exec(sql);

            // 2. 使用连接池
            std::shared_ptr<MysqlConnection> mc = mcp->getMysqlConnection();
            if (mc->exec(sql) == true) {
                // std::cout <<  "Exec sql success: " << sql << std::endl;
            }
        }
    });

    std::cout << "Start to create thread4..." << std::endl;
    std::thread t4([] () {
        MysqlConnectionPool* mcp = MysqlConnectionPool::getMysqlConnectionPool();
        for (int i = 0; i < 2500; i++) {
            char sql[1024] = {0};
            snprintf(sql, sizeof(sql), "insert into student (name, age, sex) values ('%s', %d, '%s')", 
                                        "zhangshan", 20, "M");
            // 1. 不使用连接池
            // MysqlConnection conn;
            // conn.connect("127.0.0.1", 3306, "root", "123456", "school");
            // conn.exec(sql);

            // 2. 使用连接池
            std::shared_ptr<MysqlConnection> mc = mcp->getMysqlConnection();
            if (mc->exec(sql) == true) {
                // std::cout <<  "Exec sql success: " << sql << std::endl;
            }
        }
    });

    t1.join();
    t2.join();
    t3.join();
    t4.join();

// #endif
    clock_t end = clock();
    double cpuTimeUsed = ((double)(end - begin)) / CLOCKS_PER_SEC;
    std::cout << "Cpu time used: " << cpuTimeUsed << " s" << std::endl;

    return 0;
}