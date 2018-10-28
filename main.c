#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
}account;


void add_account(int koza_id);

//mainから適当にintで値引っ張って来る
int main() {
	for (int n = 0; n<3; n++) {
		add_account(n);
	}
}

void add_account(int koza_id) {

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
