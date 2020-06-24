#include <stdio.h>
// // 12605 - Rebranding v3
#define max 200005
char str[max];
char map[26];
int id[26];

void swap_int(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
void swap_char(char *a,char *b)
{
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void show()
{
    printf("\n");
    for(int i = 0; i < 26; i ++)
        printf("%c",map[i]);
    printf("\n");
}

int main()
{
    
    for(int i = 0; i < 26; i ++){
        id[i] = i;
        map[i] = 'a'+i;
    }

    int len,t;
    scanf("%d %d",&len,&t);
    scanf(" %s",str);

    for(int i = 0; i < t; i ++){
        char x,y;
        scanf(" %c %c",&x,&y);
        swap_char(&map[id[x-'a']],&map[id[y-'a']]);
        swap_int(&id[x-'a'],&id[y-'a']);
        // show();
    }
    for(int i = 0; i < len; i ++)
        printf("%c",map[ str[i]-'a' ]);
    printf("\n");

    return 0;
}