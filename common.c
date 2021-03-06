#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"bank.h"
#include"common.h"

void input(),output(),send(),iolog(),account_info();

void load_infofile(){
    FILE *fp= fopen("info.txt","r");
    number_of_koza=0;
    while(fscanf(fp, "%s %s %s %s %u %d %d %d", 
                all_koza_data[number_of_koza].id,
                all_koza_data[number_of_koza].pass,
                all_koza_data[number_of_koza].sei,
                all_koza_data[number_of_koza].mei,
                &all_koza_data[number_of_koza].sex,
                &all_koza_data[number_of_koza].birthday,
                &all_koza_data[number_of_koza].freeze,
                &all_koza_data[number_of_koza].money
                )!=EOF){
        number_of_koza++; 
    }
    fclose(fp);
}
void save_infofile(){
    FILE* fp= fopen("info.txt","w");
    for(int i=0;i<number_of_koza;i++){
        fprintf(fp, "%s %s %s %s %d %d %d %d \n", 
                all_koza_data[i].id,
                all_koza_data[i].pass,
                all_koza_data[i].sei,
                all_koza_data[i].mei,
                all_koza_data[i].sex,
                all_koza_data[i].birthday,
                all_koza_data[i].freeze,
                all_koza_data[i].money);
    }
    fclose(fp);
}

void common_main(int koza_index){
    for(;;){
        puts("1.入金 2.出金 3.送金 4.ログの表示 5.アカウント情報 6.終了");

        int command;
        if(scanf("%d",&command)!=1){
            puts("Error:1〜6の数字を入力してください");
            scanf("%*s");
            continue;
        }
        switch(command){
            case 1:
                input(koza_index);
                break;
            case 2:
                output(koza_index);
                break;
            case 3:
                send(koza_index);
                break; 
            case 4:
                iolog(koza_index);
                break;
            case 5:
                account_info(koza_index);
                break;
            case 6:
                return ;
                break;
            default:
                puts("Error:1〜6の数字を入力してください");
        }
    }
}


int search_koza_index(char* id){
    for(int i=0;i<number_of_koza;++i){
        if(strcmp(all_koza_data[i].id,id)==0){
            return i;							//口座番号を確認し一致すると上から何行目かを返す
        }
    }
    return -1;									//なければ-1
}


void input(int koza_index){
    puts("入金する額を入力してください");
    int amount; 
    if(scanf("%d",&amount)!=1){
        puts("Error:数字を入力してください");
        scanf("%*s");
        return;
    }
    all_koza_data[koza_index].money += amount;

    FILE *fp = fopen("iolog.txt","a");
    fprintf(fp, "+%d	%d	%s\n",amount,all_koza_data[koza_index].money,all_koza_data[koza_index].id);
    fclose(fp);
}

void output(int koza_index){
    puts("出金する額を入力してください");
    int amount;
    if(scanf("%d",&amount)!=1){
        puts("Error:数字を入力してください");
        scanf("%*s");
        return;
    }
    if(all_koza_data[koza_index].money < amount) {
        puts("Error:残高不足です");
        return;
    }
    all_koza_data[koza_index].money -= amount;

    FILE *fp = fopen("iolog.txt","a");
    fprintf(fp, "-%d	%d	%s\n",amount,all_koza_data[koza_index].money,all_koza_data[koza_index].id);
    fclose(fp);
}


void send(int koza_index){
    puts("送金先の口座番号を入力してください");
    char koza_id[8];
    scanf("%s",koza_id);
    int dst_id=search_koza_index(koza_id);
    if(dst_id==-1){
        puts("Error:存在しない口座です");
        return;
    }
    if(all_koza_data[dst_id].freeze){
        puts("Error:凍結されている口座です");
        return;
    }

    puts("送金する額を入力してください");
    int amount;
    if(scanf("%d",&amount)!=1){
        puts("Error:数字を入力してください");
        scanf("%*s");
        return;
    }
    if(all_koza_data[koza_index].money < amount){
        puts("Error:残高不足です");
        return;
    }
    all_koza_data[koza_index].money -= amount;
    all_koza_data[dst_id].money += amount;

    FILE *fp = fopen("iolog.txt","a");
    fprintf(fp, "-%d	%d	%s \n+%d	%d	%s \n",amount,all_koza_data[koza_index].money,all_koza_data[koza_index].id,amount,all_koza_data[dst_id].money,all_koza_data[dst_id].id);
    fclose(fp);
}



void iolog(int target_koza_index){
    FILE *fp = fopen("iolog.txt","r");
    char amount[10],koza_id[8];
    int balance;
    while(fscanf(fp,"%s	%d	%s",amount,&balance,koza_id)!=EOF){					//とりあえず全部読み取り
        if(strcmp(koza_id,all_koza_data[target_koza_index].id)==0) printf("%s	%d \n",amount,balance); 		//口座番号が一致すればprintf 
    }
    fclose(fp);
}

void account_info(int koza_index){
    printf("登録情報\n");
    printf("	口座番号 : %s \n",all_koza_data[koza_index].id);
    printf("	姓 : %s \n",all_koza_data[koza_index].sei);
    printf("	名 : %s \n",all_koza_data[koza_index].mei);
    printf("	性別 : ");
    if (all_koza_data[koza_index].sex ==SEX_MAN){
        puts("男性");
    } else {
        puts("女性");
    }
    printf("	生年月日 : %d \n",all_koza_data[koza_index].birthday);
    printf("	残高 : %d円 \n",all_koza_data[koza_index].money);
}
