#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>

#include"bank.h"
#include"common.h"

void master_view(), master_detail(), master_freeze();
int master_menu();

int master_main() {
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
    free(koza_id);
    if (koza_index==-1){
        puts("その口座は存在しません。");
        return;
    }


    //情報出力
    printf("口座番号：%s\n", all_koza_data[koza_index].id);
    printf("姓：%s\n", all_koza_data[koza_index].sei);
    printf("名：%s\n", all_koza_data[koza_index].mei);
    printf("性別：");
    if (all_koza_data[koza_index].sex == SEX_MAN){
        puts("男性");
    } else {
        puts("女性");
    }
    printf("生年月日：%d\n", all_koza_data[koza_index].birthday);
    printf("凍結状態：");
    if (all_koza_data[koza_index].freeze ){
        puts("凍結されています");
    }else {
        puts("凍結されていません");
    }
    printf("預金額：%d円\n", all_koza_data[koza_index].money);
}

void master_freeze() {
    puts("凍結、もしくは凍結解除する口座の口座番号を入力してください。");
    printf("->");
    char* koza_id;
    scanf("%ms", &koza_id);

    int koza_index=search_koza_index(koza_id);
    free(koza_id);
    if (koza_index==-1){
        puts("その口座は存在しません。");
        return;
    }


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
