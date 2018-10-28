#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"bank.h"

void add_account(int koza_id) {
    struct koza account;

    puts("口座を作成します。");
    puts("姓を入力してください。");
    scanf("%s", account.sei);

    puts("名を入力してください。");
    scanf("%s", account.mei);

    puts("性別を入力してください。(0:man,1:woman)");
    scanf("%u", &account.sex);

    puts("生年月日を入力してください。(例:19990323)");
    if(scanf("%d", &account.birthday)!=1){
        return;
    }

pass1:
    puts("パスワードを入力してください。");
    scanf("%s", account.pass);
    puts("もう一度パスワードを入力してください。");
    scanf("%s", account.pass_check);
    if (strcmp(account.pass, account.pass_check) != 0) {
        printf("パスワードが違います。");
        goto pass1;
    }

    puts("口座が作成されました。");
    sprintf(account.id, "%07d", koza_id);

    FILE *fp= fopen("info.txt", "a");
    fprintf(fp, "%s %s %s %s %u %d 0 0\n", account.id, account.pass, account.sei, account.mei, account.sex, account.birthday);
    fclose(fp);
}

int main() {
    int koza_id;
    puts("口座番号を入力してください。");
    scanf("%d",&koza_id);
    add_account(koza_id);
}
