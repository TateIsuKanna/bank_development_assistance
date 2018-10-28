#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>


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
//FIXME:未初期化
struct koza all_koza_data[256];
unsigned int number_of_koza;
int current_koza_index;

void master_view(), master_detail(), master_freeze();
int master_menu();

int search_koza_index(char* id){
    for(int i=0;i<number_of_koza;++i){
        if(strcmp(all_koza_data[i].id,id)==0){
            return i;
        }
    }
    return -1;
}

int main() {
	FILE *fp = fopen("info.txt","r");
    number_of_koza=0;
	while(fscanf(fp, "%s %s %s %s %u %d %d %d", all_koza_data[number_of_koza].id,all_koza_data[number_of_koza].pass,all_koza_data[number_of_koza].sei,all_koza_data[number_of_koza].mei,&all_koza_data[number_of_koza].sex,&all_koza_data[number_of_koza].birthday,&all_koza_data[number_of_koza].freeze,&all_koza_data[number_of_koza].money)!=EOF){
        number_of_koza++;
    }


    int choices;
    for (;;) {
        choices = master_menu();
        puts("-----------------------------");
        switch (choices) {
            case 1:
                master_view();
                break;
            case 2:
                master_detail();
                break;
            case 3:
                master_freeze();
                break;
            case 4:
                exit(1);
                break;
            default:
                puts("入力された内容が不適切です。再入力してください。");
                break;
        }
        puts("-----------------------------");
    }
}


int master_menu() {
    puts("----menu----");
    puts("何をしますか？");
    puts("1:全口座一覧\n2:口座の詳細情報閲覧\n3:口座の凍結・凍結解除\n4:終了");
    printf("->");
    int command;
    if(scanf("%d", &command)!=1){
        scanf("%*s");
    }
    return command;
    //scanf("%d", r);
    //if (strlen(r) == 1) {
    //    return r[0] - '0';
    //}
    //else {
    //    return 0;
    //}
}

void master_view() {
    puts("口座番号と登録者名を表示します。");
    for(int i=0;i<number_of_koza;++i){
        printf("%s %s %s \n", all_koza_data[i].id, all_koza_data[i].sei, all_koza_data[i].mei);
    }
}

bool is_all_digit(char* s){
    for(int i=0;i<strlen(s);++i){
        if(!isdigit(s[i])){
            return false;
        }
    }
    return true;
}

void master_detail() {
    puts("詳細を確認したい口座番号を入力してください。");
    printf("->");
    char* koza_id;
    scanf("%ms", &koza_id);
    if(!is_all_digit(koza_id)){
        puts("入力された内容が不適切です。再入力してください。");
        return;
    }

    int koza_index=search_koza_index(koza_id);
    if (koza_index==-1){
        puts("その口座は存在しません。");
    }

    free(koza_id);

    //情報出力
    printf("口座番号：%s\n", all_koza_data[koza_index].id);
    printf("姓：%s\n", all_koza_data[koza_index].sei);
    printf("名：%s\n", all_koza_data[koza_index].mei);
    printf("性別：");
    if (all_koza_data[koza_index].sex == SEX_MAN){
        printf("男性\n");
    } else {
        printf("女性\n");
    }
    printf("生年月日：%d\n", all_koza_data[koza_index].birthday);
    printf("凍結状態：");
    if (all_koza_data[koza_index].freeze ){
        printf("凍結されています\n");
    }else {
        printf("凍結されていません\n");
    }
    printf("預金額：%d円\n", all_koza_data[koza_index].money);
}

void master_freeze() {
    puts("凍結、もしくは凍結解除する口座の口座番号を入力してください。");
    printf("->");
    char* koza_id;
    scanf("%ms", &koza_id);

    int koza_index=search_koza_index(koza_id);
    if (koza_index==-1){
        puts("その口座は存在しません。");
        return;
    }

    free(koza_id);

    if (all_koza_data[koza_index].freeze){
        puts("この口座は現在凍結されています。");
        puts("凍結解除しますか？(1:はい0:いいえ)");
        printf("->");
        int command;
        if(scanf("%d", &command)!=1){
            scanf("%*s");
        }
        if (command==1){
            printf("口座番号%sの口座を凍結解除しました。\n", all_koza_data[koza_index].id);
        }
        else if (command==0){
            printf("口座番号%sの口座を凍結解除せず戻ります。\n", all_koza_data[koza_index].id);
        }
        else {
            puts("入力された内容が不適切のため操作を中断し戻ります。");
        }
    } else {
        puts("この口座は現在凍結されていません。");
        puts("凍結しますか？(1:はい0:いいえ)");
        printf("->");
        int command;
        if(scanf("%d", &command)!=1){
            scanf("%*s");
        }
        if (command==1){
            printf("口座番号%sの口座を凍結しました。\n", all_koza_data[koza_index].id);
        } else if (command==0){
            printf("口座番号%sの口座を凍結せず戻ります。\n", all_koza_data[koza_index].id);
        }
        else {
            puts("入力された内容が不適切のため操作を中断し戻ります。");
        }
    }
}
