#include<stdio.h>

#include"bank.h"
#include"Login.h"
#include"common.h"

struct koza all_koza_data[256];
unsigned int number_of_koza;
int current_koza_index;

int main(){
    FILE *fp= fopen("info.txt","rw");
    number_of_koza=0;
    while(fscanf(fp, "%s %s %s %s %u %d %d %d", all_koza_data[number_of_koza].id,all_koza_data[number_of_koza].pass,all_koza_data[number_of_koza].sei,all_koza_data[number_of_koza].mei,&all_koza_data[number_of_koza].sex,&all_koza_data[number_of_koza].birthday,&all_koza_data[number_of_koza].freeze,&all_koza_data[number_of_koza].money)!=EOF){
        number_of_koza++; 
    }

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

    for(int i=0;i<number_of_koza;i++){
        fprintf(fp, "%s %s %s %s %d %d %d %d \n", all_koza_data[i].id, all_koza_data[i].pass, all_koza_data[i].sei, all_koza_data[i].mei, all_koza_data[i].sex, all_koza_data[i].birthday, all_koza_data[i].freeze, all_koza_data[i].money);
    }
    fclose(fp);
}
