#ifndef __MYSQL_CONNECTION_H__
#define __MYSQL_CONNECTION_H__

#include <mysql/mysql.h>
#include <string>
#include <time.h>
#include <iostream>

class MysqlConnection {
public:
    // 初始化数据库连接
    MysqlConnection();

    // 释放数据库连接
    ~MysqlConnection();

    // 连接数据库
    bool connect(std::string ip, uint32_t port, std::string user, 
                    std::string password, std::string dbname);

    // insert update delete 操作
    bool exec(std::string sql);

    // select 操作
    MYSQL_RES* query(std::string sql);

    // 刷新连接的起始空闲时间点
    void refreshAliveTime() { aliveTime_ = clock(); }

    // 返回存活的时间
    clock_t getAliveTime() const { return clock() - aliveTime_; }

private:
    MYSQL* conn_;
    clock_t aliveTime_;
};

#endif

/*
mysql_thread_init()
该函数用于初始化MySQL线程库。如果你的程序需要在多个线程中使用MySQL连接，那么在每个新线程启动之前都需要调用该函数。它返回0表示成功，-1表示失败。

mysql_thread_end()
该函数用于关闭MySQL线程库。如果你的程序不再需要使用MySQL连接，那么在程序退出之前最好调用该函数以释放资源。

mysql_init()
该函数用于初始化一个MySQL对象，可以用来建立一个新的连接。它返回一个指向该对象的指针，如果失败则返回NULL。

mysql_options()
该函数用于设置MySQL连接选项。它接受三个参数：一个指向MySQL对象的指针、选项名和选项值。选项名和选项值都是字符串。如果成功，该函数返回0，否则返回非0。

mysql_real_connect()
该函数用于建立一个MySQL连接。它接受五个参数：一个指向MySQL对象的指针、服务器地址、用户名、密码和数据库名。如果连接成功，它返回一个指向MYSQL对象的指针，否则返回NULL。

mysql_error()
该函数用于返回上一个MySQL操作产生的错误信息。它接受一个指向MYSQL对象的指针作为参数，并返回一个指向错误信息的字符串。

mysql_close()
该函数用于关闭一个MySQL连接。它接受一个指向MYSQL对象的指针作为参数，并返回void。

mysql_insert_id()
该函数用于返回上一个INSERT语句所插入的行的ID。它接受一个指向MYSQL对象的指针，并返回一个unsigned long long类型的ID。

mysql_ping()
该函数用于检查MySQL连接是否可用。如果连接正常，它返回0，否则返回非0。

mysql_query()
该函数用于执行一个SQL查询。它接受两个参数：一个指向MYSQL对象的指针和一个SQL查询字符串。如果查询成功，它返回0，否则返回非0。

mysql_affected_rows()
该函数用于返回上一个SQL语句受影响的行数。它接受一个指向MYSQL对象的指针，并返回一个unsigned long long类型的值。

mysql_store_result()
该函数用于将一个SELECT查询的结果存储在客户端。它接受一个指向MYSQL对象的指针，并返回指向MYSQL_RES对象的指针。

mysql_stmt_init()
该函数用于初始化一个MYSQL_STMT对象，该对象可以用来执行预编译的SQL语句。它返回一个指向MYSQL_STMT对象的指针，如果失败则返回NULL。

mysql_stmt_prepare()
该函数用于为预编译的SQL语句准备MYSQL_STMT对象。它接受两个参数：一个指向MYSQL_STMT对象的指针和一个SQL语句字符串。如果准备成功，它返回0，否则返回非0。

mysql_stmt_errno()
该函数用于返回上一个MYSQL_STMT操作所产生的错误代码。它接受一个指向MYSQL_STMT对象的指针，并返回一个整数错误代码。

mysql_stmt_error()
该函数用于返回上一个MYSQL_STMT操作所产生的错误信息。它接受一个指向MYSQL_STMT对象的指针，并返回一个指向错误信息的字符串。

mysql_stmt_close()
该函数用于关闭一个MYSQL_STMT对象。它接受一个指向MYSQL_STMT对象的指针，并返回void。

mysql_stmt_param_count()
该函数用于返回预编译的SQL语句中参数的数量。它接受一个指向MYSQL_STMT对象的指针，并返回一个unsigned int类型的参数数量。

mysql_stmt_execute()
该函数用于执行预编译的SQL语句。它接受一个指向MYSQL_STMT对象的指针，并返回0表示成功，否则返回非0。

mysql_stmt_insert_id()
该函数用于返回上一个INSERT语句所插入的行的ID。它接受一个指向MYSQL_STMT对象的指针，并返回一个unsigned long long类型的ID。

mysql_stmt_bind_param()
该函数用于为预编译的SQL语句绑定参数。它接受两个参数：一个指向MYSQL_STMT对象的指针和一个指向参数数组的指针。如果绑定成功，它返回0，否则返回非0。

mysql_free_result()
该函数用于释放MYSQL_RES对象占用的内存。它接受一个指向MYSQL_RES对象的指针，并返回void。

mysql_fetch_row()
该函数用于从MYSQL_RES对象中获取下一行数据。它接受一个指向MYSQL_RES对象的指针，并返回一个指向行数据的指针。如果没有更多行数据，它返回NULL。

mysql_num_rows()
该函数用于返回MYSQL_RES对象中行的数量。它接受一个指向MYSQL_RES对象的指针，并返回一个unsigned long long类型的行数。

mysql_num_fields()
该函数用于返回MYSQL_RES对象中字段的数量。它接受一个指向MYSQL_RES对象的指针，并返回一个unsigned int类型的字段数量。

mysql_fetch_lengths()
该函数用于返回MYSQL_ROW对象中每个字段的长度。它接受一个指向MYSQL_RES对象的指针和一个指向MYSQL_ROW对象的指针，并返回一个指向长度数组的指针。

mysql_stmt_result_metadata()
该函数用于获取预编译的SQL语句的结果元数据。它接受一个指向MYSQL_STMT对象的指针，并返回一个指向MYSQL_RES对象的指针。

mysql_fetch_fields()
该函数用于返回MYSQL_RES对象中每个字段的详细信息。它接受一个指向MYSQL_RES对象的指针，并返回一个指向MYSQL_FIELD对象的指针。

mysql_stmt_bind_result()
该函数用于为预编译的SQL语句绑定结果集。它接受两个参数：一个指向MYSQL_STMT对象的指针和一个指向结果集数组的指针。如果绑定成功，它返回0，否则返回非0。

mysql_stmt_store_result()
该函数用于将预编译的SQL语句的结果集存储在客户端。它接受一个指向MYSQL_STMT对象的指针，并返回0表示成功，否则返回非0。

mysql_stmt_num_rows()
该函数用于返回预编译的SQL语句的结果集中的行数。它接受一个指向MYSQL_STMT对象的指针，并返回unsigned long long类型的行数。

mysql_stmt_field_count()
该函数用于返回预编译的SQL语句的结果集中的字段数。它接受一个指向MYSQL_STMT对象的指针，并返回unsigned int类型的字段数量。

mysql_stmt_free_result()
该函数用于释放预编译的SQL语句的结果集占用的内存。它接受一个指向MYSQL_STMT对象的指针，并返回void。

mysql_select_db()
该函数用于选择要使用的数据库。它接受两个参数：一个指向MYSQL对象的指针和一个数据库名字符串。如果选择成功，它返回0，否则返回非0。

===============================================================================================================================================

MYSQL_TYPE_TINY
该类型对应MySQL中的TINYINT数据类型，表示一个有符号的8位整数。在C API中，它被定义为signed char。

MYSQL_TYPE_SHORT
该类型对应MySQL中的SMALLINT数据类型，表示一个有符号的16位整数。在C API中，它被定义为short int。

MYSQL_TYPE_LONG
该类型对应MySQL中的INTEGER和INT数据类型，表示一个有符号的32位整数。在C API中，它被定义为long int。

MYSQL_TYPE_LONGLONG
该类型对应MySQL中的BIGINT数据类型，表示一个有符号的64位整数。在C API中，它被定义为long long int。

MYSQL_TYPE_FLOAT
该类型对应MySQL中的FLOAT数据类型，表示一个单精度浮点数。在C API中，它被定义为float。

MYSQL_TYPE_DOUBLE
该类型对应MySQL中的DOUBLE数据类型，表示一个双精度浮点数。在C API中，它被定义为double。

MYSQL_TYPE_STRING
该类型对应MySQL中的CHAR、VARCHAR和TEXT数据类型，表示一个字符串。在C API中，它被定义为char *。

MYSQL_TYPE_BLOB
该类型对应MySQL中的BLOB和LONGBLOB数据类型，表示二进制数据。在C API中，它被定义为void *。

MYSQL_TYPE_TIMESTAMP
该类型对应MySQL中的TIMESTAMP数据类型，表示一个日期和时间值，精确到秒。在C API中，它被定义为MYSQL_TIME结构体。

MYSQL_TYPE_DATETIME
该类型对应MySQL中的DATETIME数据类型，表示一个日期和时间值，精确到秒。在C API中，它被定义为MYSQL_TIME结构体。

MYSQL_TYPE_DATE
该类型对应MySQL中的DATE数据类型，表示一个日期值，精确到天。在C API中，它被定义为MYSQL_TIME结构体。

MYSQL_TYPE_TIME
该类型对应MySQL中的TIME数据类型，表示一个时间值，精确到秒。在C API中，它被定义为MYSQL_TIME结构体。

*/