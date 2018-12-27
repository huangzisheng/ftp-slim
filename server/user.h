#include <iostream>
#include <"mySqlConn">
class User {
    public:
        User(int userId, int passwd) {
            this.userId = userId;
            this.passwd = passwd;
        }
        
        bool checkUser(int userId, int passwd);
        bool checkPrivil(unsigned char privilege);
        
        int userLogin();
        int userRegist();
        int userFindPasswd(int userId);
    
    private :
        int userId;
        int passwd;
        unsigned char privilege;  // 11111111 is 1, 01111111 is 2 ...
}
