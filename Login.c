#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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

int Login_check;

void master_login(char id[20],char pass[20])
{
	char id2[20];
	char pass2[20];
	char m_id[]=("------");
	char m_pass[]=("kouda-ryukou");
	char m_id2[]=("master");
	char m_pass2[]=("1234567890");

	if(strcmp(m_id,id)==0){
		if(strcmp(m_pass,pass)==0)
		{
			printf("---------------------------------------\n");
			printf("ログイン失敗\n");
			printf("---------------------------------------\n");
			printf("-口座番号（７桁）を入力してください-\n");
			scanf("%s",id2);
			printf("---------------------------------------\n");
			printf("-パスワードを入力してください-\n");
			printf("※ パスワードは隠し状態です。\n");
			system("stty -echo"); //入力内容隠し状態
			scanf("%s",pass2);
			system("stty echo"); //隠し状態解除
			printf("\n");
			if(strcmp(m_id2,id2)==0)
			if(strcmp(m_pass2,pass2)==0)
			{
				printf("---------------------------------------\n");
				printf("good!\n");
				Login_check=2;
			}else{
				printf("---------------------------------------\n");
				printf("ログイン失敗\n");

			}
		}
	}

}
void Search(char id[20],char pass[20])
{
	char n_id[20];
	char n_pass[20];
	char n_through[20];
	int i,j;
	FILE *fp;
	fp=fopen("info.txt","r");
	for(i=0;i<=1000;i++){
		fscanf(fp,"%s",n_id);
		fscanf(fp,"%s",n_pass);
		if(strcmp(n_id,id)!=0){
			//printf("id error\n");
		}else{
			if(strcmp(n_pass,pass)!=0){
				//printf("pass error\n");
			}else{
				printf("---------------------------------------\n");
				printf("ログイン成功\n");
				fscanf(fp,"%s",account.sei);
				fscanf(fp,"%s",account.mei);
				fscanf(fp,"%d",&account.sex);
				fscanf(fp,"%d",&account.birthday);
				fscanf(fp,"%d",&account.freeze);
				fscanf(fp,"%d",&account.money);
				Login_check=1;
				//ログインしたアカウントのデータを読み込む
				break;
			}
		}
		for(j=1;j<=6;j++){
			fscanf(fp,"%s",n_through);
		}
	}
	if(Login_check==0){
		printf("---------------------------------------\n");
		printf("ログイン失敗\n");
	}
}

void Info()
{
	printf("---------------------------------------\n");
	printf("ID:%10s\n",account.id);
	printf("パスワード:%10s\n",account.pass);
	printf("姓:%10s\n",account.sei);
	printf("名:%10s\n",account.mei);
	printf("性別:%10d\n",account.sex);
	printf("誕生日:%10d\n",account.birthday);
	printf("残高:%10d\n",account.money);
}

void Login() //ログイン情報入力
{
	char id[20];
	char pass[20];
	int i;
	printf("---------------------------------------\n");
	printf("-口座番号（７桁）を入力してください-\n");
	scanf("%s",id);
	printf("---------------------------------------\n");
	printf("-パスワードを入力してください-\n");
	printf("※ パスワードは隠し状態です。\n");
	system("stty -echo"); //入力内容隠し状態
	scanf("%s",pass);
	system("stty echo"); //隠し状態解除
	printf("\n");
	printf("---------------------------------------\n");
	printf("ID:%s,PASS:%s\n",id,pass);  //確認用
	master_login(id,pass);
	Search(id,pass);
	for(i=0;i<=20;i++){
		account.id[i]=id[i];
		account.pass[i]=pass[i];
	}
	if(Login_check==1){Info();}
}

void Logo(){
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

int main()
{
	Logo();
	while(1){
		//menu;
		Login_check=0;
		Login();
	}
}

