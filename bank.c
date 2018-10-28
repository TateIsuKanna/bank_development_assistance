#include<stdio.h>

#include"bank.h"
#include"Login.h"
#include"common.h"

struct koza all_koza_data[256];
unsigned int number_of_koza;
int current_koza_index;

int main(){
    load_infofile();

    Logo();
    while(1){
        //menu;
        Login_check=NOT_LOGGEDIN;
        Login();

        int isfin;
        puts("終了:1");
        scanf("%d",&isfin);
        if(isfin==1){
            break;
        }
    }

    save_infofile();
}
