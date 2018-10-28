enum SEX{
    SEX_MAN,
    SEX_WOMAN
};

struct koza {
    char id[20];
    char pass[20];
    char sei[20];
    char mei[20]; 
    enum SEX sex; 
    unsigned int birthday;
    int freeze;
    unsigned int money;

    char pass_check[20];
};

//FIXME:固定長
extern struct koza all_koza_data[256];
extern unsigned int number_of_koza;
extern int current_koza_index;
