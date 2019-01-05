#include <iostream>
#include <mysqli/mysql.h>

enum sqlOpt{
    SELECT  =   1,
    UPDATE,
    DELETE,
    MODIFY
};

class mySqlConn {
    public: 
        mySqlConn();
        ~mySqlConn();

        int connect(String ip, String id, String pwd);
        int disConnect();
        int sqlQuery(String sqlStr);
        
    private:
        bool isConnet();

        bool isConnect;
        String ip, id, pwd;
        MYSQL myConn;
        MYSQL* res;
}
