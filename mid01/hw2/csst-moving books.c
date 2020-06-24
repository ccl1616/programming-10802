#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// csst moving books

int address[25] = {0};
int table[25][25] = {0};

//將指定書號的書送往指定桌子的最上層
void sendbook(int booknum, int to)
{
    int j;
    for (j = 0; table[to][j] != -1; j++){} 
    //找出目的地桌子第幾號開始有空位
    
    table[to][j] = booknum;
    table[ address[booknum] / 100 ][ address[booknum] % 100 ] = -1;
    //將空位放入書、將原本位置清空成 -1
    
    address[booknum] = to * 100 + j;
    //更改書本位置
}

//把指定的書之上的書送回其原桌子
void returnbookabove(int booknum)
{
    int table_ofbook = address[booknum] / 100;
    int index_ofbook = address[booknum] % 100;
    
    for (int i = index_ofbook + 1; table[ table_ofbook ][i] != -1; i++)
        sendbook(table[table_ofbook][i], table[table_ofbook][i]);
    //找到指定的書所在的桌子、從下一本開始依序送回其原桌
    
}

//將兩本書之上的書送回後 將a送往b所在的桌上
void moveonto(int a, int b)
{
    returnbookabove(a);
    returnbookabove(b);
    sendbook(a, address[b] / 100);
}

//將a之上的書送回後 將a送往b所在的桌上
void moveover(int a, int b)
{
    returnbookabove(a);
    sendbook(a, address[b] / 100);
}

//將b之上的書送回後 將a和a之上的書 送往b所在的桌上
void pileonto(int a, int b)
{
    returnbookabove(b);
    int table_of_a = address[a] / 100;
    for (int i = address[a] % 100 ; table[ table_of_a ][i] != -1; i++)
        sendbook(table[ table_of_a ][i], address[b] / 100);
    //從a的桌子、位置開始向上找 一本一本依序送往目的地
}

//將a和a之上的書 送往b所在的桌上
void pileover(int a, int b)
{
    int table_of_a = address[a] / 100;
    for (int i = address[a] % 100; table[ table_of_a ][i] != -1; i++)
        sendbook(table[ table_of_a ][i], address[b] / 100);
    //從a的桌子、位置開始向上找 一本一本依序送往目的地
}

int main()
{
    int n, a, b; 
    char str1[5], str2[5];
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++)
        address[i] = i * 100;
    //初始化書的地址
    
    for (int i = 0; i < n; i++)
    {
        table[i][0] = i;
        for (int j = 1; j < n; j++)
            table[i][j] = -1;
    }
    //初始化陣列
    
    while (scanf("%s", str1))
    {
        if (strcmp(str1, "exit") == 0)
            break;
        //如果新的一行第一個詞輸入為"exit"則脫離迴圈
            
        scanf("%d%s%d", &a, str2, &b);
        
        if (a == b || address[a] / 100 == address[b] / 100)
            continue;
        //如果a==b 或是a、b在同一桌 則直接略過
        
        if (strcmp(str1, "move") == 0 && strcmp(str2, "onto") == 0)
            moveonto(a, b);
            
        if (strcmp(str1, "move") == 0 && strcmp(str2, "over") == 0)
            moveover(a, b);
            
        if (strcmp(str1, "pile") == 0 && strcmp(str2, "onto") == 0)
            pileonto(a, b);
            
        if (strcmp(str1, "pile") == 0 && strcmp(str2, "over") == 0)
            pileover(a, b);
    }
    
    //輸出
    for (int i = 0; i < n; i++)
    {
        printf("%d:", i);
        for (int j = 0; table[i][j] != -1; j++)
            printf(" %d", table[i][j]);
        printf("\n");
    }
    return 0;
}