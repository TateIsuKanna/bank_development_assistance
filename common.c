#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#pragma warning(disable:4996)

struct koza {
	char sei[20];
	char mei[20];
	int sex; //sex=0:man, sex=1:woman
	unsigned int birthday;
	char pass[20];
	char pass_check[20];
	char id[20];
	int freeze;
	unsigned int money;
}account;

void input(),output(),/*send(),*/log(),account_info();

int main(){
	int i;
	for(;;){
		printf("1.入金 2.出金 3.送金 4.ログの表示 5.アカウント情報 6.終了\n");
		scanf("%d",&i);
		switch(i){
			case 1:
						input();
						break;
			case 2:
						output();
						break;
			/*case 3:
						send();
						break;*/ 
			case 4:
						log();
						break;
			case 5:
						account_info();
						break;
			case 6:
						exit(1);
						break;
			default:
						printf("Error:1〜6の数字を入力してください\n");
		}
	}
	return 0;
}


void input(){
	FILE *fp;
	int i;
	char r[20];
	fp = fopen("info.txt","r+");
	printf("入金する額を入力してください\n");
	scanf("%d",&i);
	
	fscanf(fp, "%s", r);
	account.money = atoi(r);
	account.money = account.money + i;
	fclose(fp);
	
	fp = fopen("iolog.txt","a");
	fprintf(fp, "+%d	%d	%s \n",i,account.money,account.id);
	fclose(fp);
}

void output(){
	FILE *fp;
	int i;
	fp = fopen("info.txt","r+");
	printf("出金する額を入力してください\n");
	scanf("%d",&i);
	fp = fopen("iolog.txt","a");
	if(account.money < i) printf("Error:残高不足です\n");
	else{
		account.money = account.money - i;
		fprintf(fp, "-%d	%d	%s \n",i,account.money,account.id);
		fclose(fp);
	}
}

/*
void send(){
	FILE *fp;
	int i;
	fp = fopen("iolog.txt","r");
	printf("送金先の口座番号を入力してください\n");
	scanf("%d",&i);
	//check
	printf("送金する額を入力してください\n");
	scanf("%d",i);
	account.money = account.money - i;
	fprintf(fp, "-%d	%d	%s \n",i,account.money,account.id);
	fclose(fp);
}
*/

void log(){
	FILE *fp;
	int i;
	fp = fopen("iolog.txt","r");
	fscanf(fp,"%d",&i);
	printf("%s",i);
	fclose(fp);
}

void account_info(){
	FILE *fp;
	char i[20];
	fp = fopen("info.txt","r");
	fscanf(fp, "%s", account.id);
	fscanf(fp, "%s", account.pass);
	fscanf(fp, "%s", account.sei);
	fscanf(fp, "%s", account.mei);
	fscanf(fp, "%s", i);
	account.sex = atoi(i);
	fscanf(fp, "%s", i);
	account.birthday = atoi(i);
	fscanf(fp, "%s", i);
	
	fscanf(fp, "%s", i);
	account.money = atoi(i);
	
	printf("登録情報\n");
	printf("	口座番号 : %s \n",account.id);
	printf("	姓 : %s \n",account.sei);
	printf("	名 : %s \n",account.mei);
	printf("	性別 : ");
	if (account.sex == 0) printf("男性\n");
		else printf("女性\n");
	printf("	生年月日 : %d \n",account.birthday);
	printf("	残高 : %d円 \n",account.money);
	fclose(fp);
}
