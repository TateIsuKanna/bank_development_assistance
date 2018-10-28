enum LOGIN_STATE{
    NOT_LOGGEDIN,
    LOGGEDIN_AS_NORMAL_USER,
    LOGGEDIN_AS_MASTER
};
extern enum LOGIN_STATE Login_check;

void Logo();
void Login();
