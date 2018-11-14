#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<termios.h>
#include<unistd.h>
#include<ctype.h>


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

#pragma warning(disable:4996)
char re_pass[20];

void add_account(int k);
int Login_check;
void Logo(), Login(), Search(char id[20], char pass[20]), master_login(char id[20], char pass[20]), Pass();
void input(), output(), send(), iolog(), account_info(), common_main(), change_file(), sent_change(struct koza sent);
void master_view(), master_detail(), master_freeze(), master_menu();

int main() {
	int choice, i;
	char c;
	FILE *fp;
	i = 0;

	Logo();
	fp = fopen("info.txt", "r");
	for (;;) {
		c = fgetc(fp);
		if (c == EOF)break;
		else if (c == 10)i++;
	}
	fclose(fp);

	for (;;) {
		printf("--------MENU--------\n");
		printf("1.口座新規登録\n");
		printf("2.ログイン\n");
		printf("3.終了\n");
		printf("--------------------\n");
		printf("何をしますか。\n");
		printf("->");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			add_account(i);
			i++;
			break;
		case 2:
			//menu;
			Login_check = 0;
			Login();
			break;
		case 3:		exit(1);
			break;
		default:	printf("対応していない値です。\n\n");
		}
	}
	return 0;
}

void add_account(int k) {
	char fmt[16];
	struct termios term;
	struct termios save;
	char storage[100];
	char tmp;
	int month, day;

	printf("口座を作成します。\n");

	//姓名入力
	printf("姓を入力してください。\n");
	printf("->");
	scanf("%s", account.sei);


	printf("名を入力してください。\n");
	printf("->");
	scanf("%s", account.mei);


	//性別入力
pass2:
	printf("性別を入力してください。(0:man,1:woman)\n");
	printf("->");
	scanf("%s", storage);
	if (strlen(storage) != 1) {
		printf("0,1以外が入力されました。\n");
		goto pass2;
	}
	else if (storage[0] == '0' || storage[0] == '1') {
		account.sex = atoi(storage);
	}
	else {
		printf("0,1以外が入力されました。\n");
		goto pass2;
	}

	//生年月日入力
birth:
	printf("生年月日(8桁)を入力してください。(例:19990323)\n");
	printf("->");
	scanf("%d", &account.birthday);
	month = account.birthday % 10000;
	day = account.birthday % 100;
	month = (month - day) / 100;
	if (account.birthday>99991231 || account.birthday<101 || month>12 || month<1 || day>31 || day<1 || month == 2 && day>28 || month == 4 && day>30 || month == 6 && day>30 || month == 9 && day>30 || month == 11 && day>30) {
		printf("存在しない生年月日です。\n");
		goto birth;
	}

	//パスワード入力
pass1:
	tcgetattr(STDIN_FILENO, &term);
	save = term;
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	tmp = fgetc(stdin);
	printf("パスワードを入力してください。\n");
	printf("->");
	for (int j = 0; j < 19; j++) {
	unsigned char uchr;
	tmp = fgetc(stdin);
	if (tmp < 0 || iscntrl(tmp)) {
	fprintf(stderr, "\n");
	break;
	}
	//uchr = (char)tmp;
	account.pass[j] = tmp;
	fprintf(stderr, "*");
	}

	printf("もう一度パスワードを入力してください。\n");
	printf("->");
	for (int j = 0; j < sizeof(account.pass_check) - 1; j++) {
	tmp = fgetc(stdin);
	if (tmp < 0 || iscntrl(tmp)) {
	fprintf(stderr, "\n");
	break;
	}
	account.pass_check[j] = tmp;
	fprintf(stderr, "*");
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &save);
	scanf("%s", account.pass_check);

	//パスワードの正誤判定
	if (strcmp(account.pass, account.pass_check) != 0) {
		printf("パスワードが違います。Enterを押してください\n");
		memset(account.pass, '\0', 20);
		memset(account.pass_check, '\0', 20);
		goto pass1;
	}

	printf("口座が作成されました。\n");
	sprintf(account.id, "%07d", k);
	printf("口座番号は%07dです。\n", k);
	printf("MENU画面に戻ります。\n\n");

	account.freeze = 0;
	account.money = 0;

	FILE *fp;
	fp = fopen("info.txt", "a");
	fprintf(fp, "%s %s %s %s %d %d %d %d\n", account.id, account.pass, account.sei, account.mei, account.sex, account.birthday, account.freeze, account.money);
	fclose(fp);
}

void Pass()
{
	struct termios term;
	struct termios save;
	char tmp;
	int i;
	tcgetattr(STDIN_FILENO, &term);
	save = term;
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	tmp = fgetc(stdin);
	for (i = 0; i <= 20; i++) {
	re_pass[i] = 0;
	}
	printf("パスワードを入力してください。\n");
	printf("->");
	for (int j = 0; j < 19; j++) {
		unsigned char uchr;
		tmp = fgetc(stdin);
		if (tmp < 0 || iscntrl(tmp)) {
		fprintf(stderr, "\n");
		break;
		}
		//uchr = (char)tmp;
		re_pass[j] = tmp;
		fprintf(stderr, "*");
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &save);
}

void master_login(char id[20], char pass[20])
{
	char id2[20];
	char pass2[20];
	char m_id[] = ("-------");
	char m_pass[] = ("Iam");
	char m_id2[] = ("master");
	char m_pass2[] = ("-------");
	int i;

	if (strcmp(m_id, id) == 0) {
		if (strcmp(m_pass, pass) == 0)
		{
			printf("---------------------------------------\n");
			printf("ログイン失敗\n");
			printf("---------------------------------------\n");
			printf("-口座番号（７桁）を入力してください\n");
			printf("->");
			scanf("%s", id2);
			printf("---------------------------------------\n");
			//printf("-パスワードを入力してください-\n");
			//printf("※ パスワードは隠し状態です。\n");
			//printf("->");
			//system("stty -echo"); //入力内容隠し状態
			//scanf("%s",pass2);
			//system("stty echo"); //隠し状態解除
			Pass();
			for (int i = 0; i <= strlen(re_pass); i++) {
				pass2[i] = re_pass[i];
			}
			if (strcmp(m_id2, id2) == 0)
				if (strcmp(m_pass2, pass2) == 0)
				{
					printf("---------------------------------------\n");
					//printf("good!\n");
					Login_check = 2;
				}
				else {
					//printf("ID:%s,PASS:%s\n", id2, pass2);
					//printf("---------------------------------------\n");
					//printf("ログイン失敗\n");

				}
		}
	}

}
void Search(char id[20], char pass[20])
{
	char n_id[20];
	char n_pass[20];
	char n_through[20];
	int i, j;
	FILE *fp;
	fp = fopen("info.txt", "r");
	for (i = 0; i <= 1000; i++) {
		fscanf(fp, "%s", n_id);
		fscanf(fp, "%s", n_pass);
		if (strcmp(n_id, id) != 0) {
			//printf("id error\n");
		}
		else {
			if (strcmp(n_pass, pass) != 0) {
				//printf("pass error\n");
			}
			else {
				//printf("---------------------------------------\n");
				fscanf(fp, "%s", account.sei);
				fscanf(fp, "%s", account.mei);
				fscanf(fp, "%d", &account.sex);
				fscanf(fp, "%d", &account.birthday);
				fscanf(fp, "%d", &account.freeze);
				fscanf(fp, "%d", &account.money);
				Login_check = 1;
				if (account.freeze == 0) {
					printf("ログイン成功\n");
					printf("---------------------------------------\n");
				}
				else {
					printf("凍結されています\n");
					printf("---------------------------------------\n");
				}
				//ログインしたアカウントのデータを読み込む
				break;
			}
		}
		for (j = 1; j <= 6; j++) {
			fscanf(fp, "%s", n_through);
		}
	}
	if (Login_check == 0) {
		//printf("---------------------------------------\n");
		printf("ログイン失敗\n");
	}
}

void Login() //ログイン情報入力
{
	char id[20];
	char pass[20];
	int i;
	printf("---------------------------------------\n");
	printf("-口座番号（７桁）を入力してください\n");
	printf("->");
	scanf("%s", id);
	printf("---------------------------------------\n");
	//printf("-パスワードを入力してください-\n");
	//printf("->");
	//printf("※ パスワードは隠し状態です。\n");
	//system("stty -echo"); //入力内容隠し状態
	//scanf("%s",pass);
	//system("stty echo"); //隠し状態解除
	Pass();
	for (i = 0; i <= strlen(re_pass); i++) {
		pass[i] = re_pass[i];
	}
	printf("---------------------------------------\n");
	//printf("ID:%s,PASS:%s\n", id, pass);  //確認用
	for (i = 0; i <= 20; i++) {
		account.id[i] = id[i];
		account.pass[i] = pass[i];
	}
	master_login(id, pass);
	Search(id, pass);
	if (Login_check == 1)
	{
		if (account.freeze == 0) common_main();
	}
}

void Logo() {
	printf("  ----------       -------     -             -------     \n");
	printf("           -      -      -     -            -      -     \n");
	printf("      -    -     -      -      -           -      -      \n");
	printf("      -   -     -      -       ------     -      -       \n");
	printf("      -               -        -                -        \n");
	printf("      -              -         -               -         \n");
	printf("     -              -          -              -          \n");
	printf("     -            -           -             -            \n");
	printf("                          ★                             \n");
	printf("     -    - -                                            \n");
	printf("  -------- - -               ---------        -          \n");
	printf("      -         -----                -   ----------      \n");
	printf("      -                   -          -   -        -      \n");
	printf("  --------               -           -   -        -      \n");
	printf("       -               --            -           -       \n");
	printf("       -            ---              -          -        \n");
	printf("       -        ----         ---------         -         \n");

}

void common_main() {
	int flag;
	flag = 0;
	for (;;) {
		printf("1.入金 2.出金 3.送金 4.ログの表示 5.アカウント情報 6.終了\n");
		printf("->");
		int command;
		if (scanf("%d", &command) != 1) {
			printf("Error:1～6の数字を入力してください\n");
			scanf("%*s");
		}
		else {
			switch (command) {
			case 1:
				input();
				change_file();
				break;
			case 2:
				output();
				change_file();
				break;
			case 3:
				send();
				change_file();
				break;
			case 4:
				iolog();
				break;
			case 5:
				account_info();
				break;
			case 6:
				flag = 1;
				break;
			default:
				printf("Error:1～6の数字を入力してください\n");
			}
		}
		if (flag == 1)break;
	}
}

void input() {
	printf("入金する額を入力してください\n");
	printf("->");
	int amount;
	if (scanf("%d", &amount) != 1) {
		printf("Error:数字を入力してください\n");
		scanf("%*s");
	}
	else {
		account.money += amount;
		FILE *fp = fopen("iolog.txt", "a");
		fprintf(fp, "+%d	%d	%s\n", amount, account.money, account.id);
		fclose(fp);
	}
}

void output() {
	printf("出金する額を入力してください\n");
	printf("->");
	int amount;
	if (scanf("%d", &amount) != 1) {
		printf("Error:数字を入力してください\n");
		scanf("%*s");
	}
	else {
		FILE *fp = fopen("iolog.txt", "a");
		if (account.money < amount) printf("Error:残高不足です\n");
		else {
			account.money -= amount;
			fprintf(fp, "-%d	%d	%s\n", amount, account.money, account.id);
			fclose(fp);
		}
	}
}

void send() {
	FILE *fp;
	int p;
	char r[20], c;
	struct koza sent;

	printf("送金先の口座番号を入力してください\n");
	printf("->");
	int amount, dst_id;
	char k[8];
	scanf("%s", k);
	dst_id = atoi(k);

	fp = fopen("info.txt", "r");
	for (p = 0; p != atoi(k); p++) {//指定された口座番号分改行する
		for (;;) {
			c = fgetc(fp);
			if (c == '\n' || c == EOF)break;
		}
	}
	c = fgetc(fp);
	fseek(fp, -1, 1);
	if (c == EOF)printf("その口座は存在しません。\n");
	else {//情報を取り出す
		fscanf(fp, "%s", sent.id);
		fscanf(fp, "%s", sent.pass);
		fscanf(fp, "%s", sent.sei);
		fscanf(fp, "%s", sent.mei);
		fscanf(fp, "%s", r);
		sent.sex = atoi(r);
		fscanf(fp, "%s", r);
		sent.birthday = atoi(r);
		fscanf(fp, "%s", r);
		sent.freeze = atoi(r);
		fscanf(fp, "%s", r);
		sent.money = atoi(r);
	}
	fclose(fp);

	if (c == EOF) {

	}
	else if (sent.freeze) {//修正の必要あり
		printf("Error:凍結されている口座です\n");
	}
	else {
		printf("送金する額を入力してください\n");
		printf("->");
		if (scanf("%d", &amount) != 1) {
			printf("Error:数字を入力してください\n");
			scanf("%*s");
		}
		else {
			if (account.money < amount) printf("Error:残高不足です\n");
			else {
				account.money -= amount;
				sent.money += amount;//修正の必要あり
				FILE *fp = fopen("iolog.txt", "a");
				fprintf(fp, "-%d	%d	%s \n+%d	%d	%s \n", amount, account.money, account.id, amount, sent.money, sent.id);//修正の必要あり
				fclose(fp);
				sent_change(sent);
			}
		}
	}
}

void iolog() {
	FILE *fp = fopen("iolog.txt", "r");
	char a[10], c[8];
	int b;
	while (fscanf(fp, "%s	%d	%s", a, &b, c) != EOF) {					//とりあえず全部読み取り
		if (strcmp(c, account.id) == 0) printf("%s	%d \n", a, b); 		//口座番号が一致すればprintf 
	}
	fclose(fp);
}

void account_info() {
	printf("登録情報\n");
	printf("	口座番号 : %s \n", account.id);
	printf("	姓 : %s \n", account.sei);
	printf("	名 : %s \n", account.mei);
	printf("	性別 : ");
	if (account.sex) printf("女性\n");
	else printf("男性\n");
	printf("	生年月日 : %07d \n", account.birthday);
	printf("	残高 : %d円 \n", account.money);
}

void change_file() {
	FILE *fp, *fi;
	char c;
	int p;

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
		}
	}
	fprintf(fp, "%s %s %s %s %d %d %d %d\n", account.id, account.pass, account.sei, account.mei, account.sex, account.birthday, account.freeze, account.money);
	for (;;) {
		c = fgetc(fi);
		if (c == '\n' || c == EOF)break;
	}
	for (;;) {//残りすべて複写
		c = fgetc(fi);
		if (c == EOF)break;
		fprintf(fp, "%c", c);
	}
	fclose(fp);
	fclose(fi);
	fi = fopen("cache.txt", "w");
	fclose(fi);
}

void sent_change(struct koza sent) {
	FILE *fp, *fi;
	char c;
	int p;

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

	for (p = 0; p != atoi(sent.id); p++) {//指定された口座番号まで複写
		for (;;) {
			c = fgetc(fi);
			fprintf(fp, "%c", c);
			if (c == '\n' || c == EOF)break;
		}
	}
	fprintf(fp, "%s %s %s %s %d %d %d %d\n", sent.id, sent.pass, sent.sei, sent.mei, sent.sex, sent.birthday, sent.freeze, sent.money);
	for (;;) {
		c = fgetc(fi);
		if (c == '\n' || c == EOF)break;
	}
	for (;;) {//残りすべて複写
		c = fgetc(fi);
		if (c == EOF)break;
		fprintf(fp, "%c", c);
	}
	fclose(fp);
	fclose(fi);
	fi = fopen("cache.txt", "w");
	fclose(fi);
}

void master_menu() {
	char  r[20];
	int flag;

	flag = 0;
	for (;;) {
		printf("----menu----\n何をしますか？\n");
		printf("1:全口座一覧\n2:口座の詳細情報閲覧\n3:口座の凍結・凍結解除\n4:終了\n");
		printf("->");
		scanf("%s", r);
		printf("-----------------------------\n");
		if (strlen(r) == 1) {
			switch (r[0] - 48) {
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
				flag = 1;
				break;
			default:
				printf("入力された内容が不適切です。再入力してください。\n");
				break;
			}
		}
		else {
			printf("入力された内容が不適切です。再入力してください。\n");
		}
		printf("-----------------------------\n");
		if (flag == 1)break;
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
		printf("生年月日：%07d\n", account.birthday);
		printf("凍結状態：");
		if (account.freeze == 0)printf("凍結されていません\n");
		else printf("凍結されています\n");
		printf("預金額：%d円\n", account.money);
	}
	fclose(fp);
}

void master_freeze() {
	char r[20], c;
	int p, change;
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
			}
		}
		for (p = 0; p <= 5; p++) {//凍結情報まで複写
			fscanf(fi, "%s", r);
			fprintf(fp, "%s ", r);
		}
		if (change == 1) {//凍結情報の書き換え
			fprintf(fp, "1");
		}
		else if (change == 0) {
			fprintf(fp, "0");
		}
		fscanf(fi, "%s", r);//凍結情報の読み飛ばし
		for (;;) {//残りすべて複写
			c = fgetc(fi);
			if (c == EOF)break;
			fprintf(fp, "%c", c);
		}
		fclose(fp);
		fclose(fi);
	}
}
