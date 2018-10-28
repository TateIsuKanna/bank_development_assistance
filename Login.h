enum LOGIN_STATE{
    NOT_LOGGEDIN,
    LOGGEDIN_AS_NORMAL_USER,
    LOGGEDIN_AS_MASTER
};
extern enum LOGIN_STATE Login_check;

void Logo();
void Login();
void iolog(char* target_koza_id);
void master_login(char id[20],char pass[20]);

