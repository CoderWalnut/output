#include "mysqlConnection.h"

MysqlConnection::MysqlConnection() {
    conn_ = mysql_init(nullptr);
}

MysqlConnection::~MysqlConnection() {
    if (conn_ != nullptr) {
        mysql_close(conn_);
    }
}

bool MysqlConnection::connect(std::string ip, uint32_t port, std::string user, 
                    std::string password, std::string dbname)
{
    MYSQL* p = mysql_real_connect(conn_, ip.c_str(), user.c_str(), password.c_str(),
                                dbname.c_str(), port, nullptr, 0);
    if (p == nullptr) {
        std::cout << "Connect to mysql server failure." << std::endl;
        return false;
    } 
    return true;
}


bool MysqlConnection::exec(std::string sql) {
    if (mysql_query(conn_, sql.c_str())) {
        std::cout << "Exec sql failure: " << sql << std::endl;
        return false;
    }
    return true;
}

MYSQL_RES* MysqlConnection::query(std::string sql) {
    if (mysql_query(conn_, sql.c_str())) {
        std::cout << "Query sql failure: " << sql << std::endl;
        return nullptr;
    }

    return mysql_store_result(conn_);
}