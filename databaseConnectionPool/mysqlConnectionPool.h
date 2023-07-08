#ifndef __MYSQL_CONNECTION_POOL_H__
#define __MYSQL_CONNECTION_POOL_H__

#include <iostream>
#include <memory>
#include <queue>
#include <mutex>
#include <atomic>
#include <condition_variable>

#include "mysqlConnection.h"

class MysqlConnectionPool {
public:
    // 获取连接池对象实例, 线程安全的懒汉单例函数接口
    static MysqlConnectionPool* getMysqlConnectionPool();

    //给外部提供的接口，从连接池中获取一个可用的空闲连接
    std::shared_ptr<MysqlConnection> getMysqlConnection();

private:
    // 单例#1 构造函数私有化
    MysqlConnectionPool();

    // 从配置文件中加载配置项
    bool loadConfigFile();

    // 运行在独立的线程中，专门负责生产新连接
    void produceMysqlConnectionTask();

    // 扫描超过maxIdleTime时间的空闲连接，对其进行连接回收
    void scanMysqlConnectionTask();

    std::string ip_;
    uint32_t port_;
    std::string user_;
    std::string password_;
    std::string dbname_;
    uint64_t initSize_;                 // 连接池的初始连接量
    uint64_t maxSize_;                  // 连接池的最大连接量
    uint64_t maxIdleTime_;              // 连接池的最大空闲时间
    uint64_t maxConnectionTimeout_;     // 从连接池获取连接的最大超时时间

    std::queue<MysqlConnection*> mysqlConnectionQueue_;     // 存储mysql连接的队列
    std::mutex queueMutex_;                                 // 维护连接队列线程安全的互斥锁
    std::atomic_int mysqlConnectionCnt_;                    // 记录创建mysqlConnection连接的总数量
    std::condition_variable cv;                             // 条件变量，用于生产线程和消费线程的通信
};

#endif