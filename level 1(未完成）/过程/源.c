#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char validAccounts[27][20] = {
    "A", "B", "C",
    "D", "E", "F", "G", "H", "I",
    "J", "K", "L", "M", "N", "O",
    "P", "Q", "R", "S", "T", "U",
    "V", "W", "X", "Y", "Z", "Librarian"
};

int isValidAccount(char* account) {
    for (int i = 0; i < 27 ; i++) {
        if (strcmp(validAccounts[i], account) == 0) {
            return 1;
        }
    }
    return 0;
}

int login() {
    char account[20];
    do{
        printf("请输入账号：");
        scanf_s("%s", account,(unsigned)sizeof(account));
        if (isValidAccount(account)) {
            printf("登陆成功，欢迎您，%s\n", account);
            break;
        }
        else {
            printf("Error");
        }
    } while (1);
    return 0;
}
int main() {
    login();
    char command[20];
    do {
        printf("你想做什么?\n");
        printf("\n请输入:\n");
        scanf_s("%s", command, (unsigned)sizeof(command));
        printf("抱歉，该功能还未完成！！！");
    } while (strcmp(command, "Quit" )!=0);
    return 0;
}