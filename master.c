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

void master_view(), master_detail(), master_freeze();
int master_menu();

int main() {
	int choices;
	for (;;) {
		choices = master_menu();
		printf("-----------------------------\n");
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
			printf("入力された内容が不適切です。再入力してください。\n");
			break;
		}
		printf("-----------------------------\n");
	}
	return 0;
}


int master_menu() {
	char  r[20];

	printf("----menu----\n何をしますか？\n");
	printf("1:全口座一覧\n2:口座の詳細情報閲覧\n3:口座の凍結・凍結解除\n4:終了\n");
	printf("->");
	scanf("%s", r);
	if (strlen(r) == 1) {
		return r[0] - 48;
	}
	else {
		return 0;
	}
}

void master_view() {
	char c;
	FILE *fp;

	fp = fopen("info.txt", "r");

	printf("口座番号と登録者名を表示します。\n");
	for (;;) {
		fscanf(fp, "%s", account.id);
		fscanf(fp, "%s", account.pass);
		fscanf(fp, "%s", account.sei);
		fscanf(fp, "%s", account.mei);
		c = fgetc(fp);
		for (;;) {//次の行まで移動
			if (c == '\n')break;
			c = fgetc(fp);
		}
		printf("%s %s %s \n", account.id, account.sei, account.mei);
		c = fgetc(fp);
		if (c == EOF)break;//ファイル終端なら終了
		else fseek(fp, -1, 1);//そうでないならファイルポインタを戻す
	}
	fclose(fp);
}

void master_detail() {
	int p, flag;
	char r[20], c;
	FILE *fp;

	fp = fopen("info.txt", "r");
	printf("詳細を確認したい口座番号を入力してください。\n");
	for (;;) {
		printf("->");
		scanf("%s", r);
		flag = 0;
		for (p = 0; p != strlen(r); p++) {//入力されたものがすべて数字か確認
			if (r[p] < '0' || r[p] > '9') flag = 1;
		}
		if (flag == 0)break;
		else if (flag == 1)printf("入力された内容が不適切です。再入力してください。\n");
	}
	for (p = 0; p != atoi(r); p++) {//指定された口座番号分改行する
		for (;;) {
			c = fgetc(fp);
			if (c == '\n' || c == EOF)break;
		}
	}
	c = fgetc(fp);
	fseek(fp, -1, 1);
	if (c == EOF)printf("その口座は存在しません。\n");
	else {//情報を取り出す
		fscanf(fp, "%s", account.id);
		fscanf(fp, "%s", account.pass);
		fscanf(fp, "%s", account.sei);
		fscanf(fp, "%s", account.mei);
		fscanf(fp, "%s", r);
		account.sex = atoi(r);
		fscanf(fp, "%s", r);
		account.birthday = atoi(r);
		fscanf(fp, "%s", r);
		account.freeze = atoi(r);
		fscanf(fp, "%s", r);
		account.money = atoi(r);

		//情報出力
		printf("口座番号：%s\n", account.id);
		printf("姓：%s\n", account.sei);
		printf("名：%s\n", account.mei);
		printf("性別：");
		if (account.sex == 0)printf("男性\n");
		else printf("女性\n");
		printf("生年月日：%d\n", account.birthday);
		printf("凍結状態：");
		if (account.freeze == 0)printf("凍結されていません\n");
		else printf("凍結されています\n");
		printf("預金額：%d円\n", account.money);
	}
	fclose(fp);
}

void master_freeze() {
	char r[20], c;
	int p, i, change;
	FILE *fp, *fi;

	change = 2;//2:変更なし
	fp = fopen("info.txt", "r");
	printf("凍結、もしくは凍結解除する口座の口座番号を入力してください。\n");
	printf("->");
	scanf("%s", r);
	for (p = 0; p != atoi(r); p++) {//指定された口座番号分改行する
		for (;;) {
			c = fgetc(fp);
			if (c == '\n' || c == EOF)break;
		}
	}
	c = fgetc(fp);
	fseek(fp, -1, 1);
	if (c == EOF)printf("その口座は存在しません。\n");
	else {//情報を取り出し
		fscanf(fp, "%s", account.id);
		for (p = 0; p < 5; p++) {//凍結情報まで読み飛ばし
			fscanf(fp, "%s", r);
		}
		fscanf(fp, "%s", r);//凍結状態の読み込み
		account.freeze = atoi(r);
		if (account.freeze == 0) {
			printf("この口座は現在凍結されていません。\n");
			printf("凍結しますか？(1:はい0:いいえ)\n");
			printf("->");
			scanf("%s", r);
			if (r[0] == '1'&&strlen(r) == 1) {
				printf("口座番号%sの口座を凍結しました。\n", account.id);
				change = 1;//1：凍結
			}
			else if (r[0] == '0'&&strlen(r) == 1) {
				printf("口座番号%sの口座を凍結せず戻ります。\n", account.id);
			}
			else {
				printf("入力された内容が不適切のため操作を中断し戻ります。\n");
			}
		}
		else if (account.freeze == 1) {
			printf("この口座は現在凍結されています。\n");
			printf("凍結解除しますか？(1:はい0:いいえ)\n");
			printf("->");
			scanf("%s", r);
			if (r[0] == '1'&&strlen(r) == 1) {
				printf("口座番号%sの口座を凍結解除しました。\n", account.id);
				change = 0;//0：凍結解除
			}
			else if (r[0] == '0'&&strlen(r) == 1) {
				printf("口座番号%sの口座を凍結解除せず戻ります。\n", account.id);
			}
			else {
				printf("入力された内容が不適切のため操作を中断し戻ります。\n");
			}
		}
		else {
			printf("データファイルが破損している可能性があります。\n");
		}
	}
	fclose(fp);

	if (change != 2) {
		fp = fopen("info.txt", "r");
		fi = fopen("cache.txt", "w");
		for (;;) {
			c = fgetc(fp);
			if (c == EOF)break;
			fprintf(fi, "%c", c);
		}
		fclose(fp);
		fclose(fi);

		fp = fopen("info.txt", "w");
		fi = fopen("cache.txt", "r");

		for (p = 0; p != atoi(account.id); p++) {//指定された口座番号まで複写
			for (;;) {
				c = fgetc(fi);
				fprintf(fp, "%c", c);
				if (c == '\n' || c == EOF)break;
				printf("%c", c);
			}
		}
		for (p = 0; p <= 5; p++) {//凍結情報まで複写
			fscanf(fi, "%s", r);
			fprintf(fp, "%s ", r);
			printf("%s ", r);
		}
		if (change == 1) {//凍結情報の書き換え
			fprintf(fp, "1");
		}
		else if (change == 0) {
			fprintf(fp, "0");
		}
		printf("%d ", change);
		fscanf(fi, "%s", r);//凍結情報の読み飛ばし
		for (;;) {//残りすべて複写
			c = fgetc(fi);
			if (c == EOF)break;
			fprintf(fp, "%c", c);
			printf("%c", c);
		}
		fclose(fp);
		fclose(fi);
	}
}