#include <iostream>
#include <string>
#include <mysqli/mysql.h>

enum sqlOpt{
    SELECT  =   1,
    UPDATE,
    DELETE,
    MODIFY
};

class MySqlConn {
    public: 
        mySqlConn();
        ~mySqlConn();

        int connect();
        int disConnect();
        int sqlQuery(string sqlStr, int sqlType);
        
    private:
        bool isConnet();

        bool isConnect;
        string ip, id, pwd;
        MYSQL myConn;
        MYSQL* res;
};
