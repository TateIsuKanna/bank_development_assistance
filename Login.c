#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<termios.h>

#include"bank.h"
#include"Login.h"
#include"common.h"

enum LOGIN_STATE Login_check=NOT_LOGGEDIN;

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
            puts("---------------------------------------");
            puts("ログイン失敗");
            puts("---------------------------------------");
            puts("-口座番号（７桁）を入力してください-");
            scanf("%s",id2);
            puts("---------------------------------------");
            puts("-パスワードを入力してください-");
            puts("※ パスワードは隠し状態です。");
            system("stty -echo"); //入力内容隠し状態
            scanf("%s",pass2);
            system("stty echo"); //隠し状態解除
            puts("");
            if(strcmp(m_id2,id2)==0){
                if(strcmp(m_pass2,pass2)==0){
                    puts("---------------------------------------");
                    puts("good!");
                    Login_check=LOGGEDIN_AS_MASTER;
                }else{
                    puts("---------------------------------------");
                    puts("ログイン失敗");

                }
            }
        }
    }
}

void Info(int koza_index)
{
    puts("---------------------------------------");
    printf("ID:%10s\n",all_koza_data[koza_index].id);
    printf("パスワード:%10s\n",all_koza_data[koza_index].pass);
    printf("姓:%10s\n",all_koza_data[koza_index].sei);
    printf("名:%10s\n",all_koza_data[koza_index].mei);
    printf("性別:%10d\n",all_koza_data[koza_index].sex);
    printf("誕生日:%10d\n",all_koza_data[koza_index].birthday);
    printf("残高:%10d\n",all_koza_data[koza_index].money);
}

void Login() //ログイン情報入力
{
    puts("---------------------------------------");
    puts("-口座番号（７桁）を入力してください-");
    char* id;
    scanf("%ms",&id);
    puts("---------------------------------------");
    puts("-パスワードを入力してください-");
    puts("※ パスワードは隠し状態です。");
    system("stty -echo"); //入力内容隠し状態
    char* pass;
    scanf("%ms",&pass);
    system("stty echo"); //隠し状態解除
    printf("\n");
    puts("---------------------------------------");
    printf("ID:%s,PASS:%s\n",id,pass);  //確認用
    master_login(id,pass);
    int koza_index=search_koza_index(id);
    free(id);
    if(koza_index==-1 || strcmp(all_koza_data[koza_index].pass,pass)!=0) {
        puts("---------------------------------------");
        puts("ログイン失敗");
        free(pass);
        return;
    }
    free(pass);

    puts("---------------------------------------");
    puts("ログイン成功");
    Login_check=LOGGEDIN_AS_NORMAL_USER;
    current_koza_index=koza_index;


    Info(current_koza_index);
    common_main(current_koza_index);
}

void Logo(){
    puts("  ----------       -------     -             -------     ");
    puts("           -      -      -     -            -      -     ");
    puts("      -    -     -      -      -           -      -      ");
    puts("      -   -     -      -       ------     -      -       ");
    puts("      -               -        -                -        ");
    puts("      -              -         -               -         ");
    puts("     -              -          -              -          ");
    puts("     -            -           -             -            ");
    puts("                          ★                             ");
    puts("     -    - -                                            ");
    puts("  -------- - -               ---------        -          ");
    puts("      -         -----                -   ----------      ");
    puts("      -                   -          -   -        -      ");
    puts("  --------               -           -   -        -      ");
    puts("       -               --            -           -       ");
    puts("       -            ---              -          -        ");
    puts("       -        ----         ---------         -         ");

}
