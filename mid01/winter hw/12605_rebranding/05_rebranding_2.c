#include <stdio.h>
#include <string.h>
// 12605 - Rebranding v2
#define max 200005
int n,m;
char str[max];
char temp,temp2;
char array[max][2];

int main()
{
    scanf("%d %d",&n,&m);
    scanf("%s",str);
    int k = 0;
    for(int i = 0; i < m; i ++){
        int flag1 = 0;
        int flag2 = 0;
        scanf(" %c %c",&temp,&temp2);
        for(int j = 0; j < k; j ++){
            if(array[j][1] == temp){
                array[j][1] = temp2;
                flag1 = 1;
            }
            else if(array[j][1] == temp2){
                array[j][1] = temp;
                flag2 = 1;
            }
        }
        if(flag1 == 0){
            array[k][0] = temp;
            array[k][1] = temp2;
            k ++;
        }
        if(flag2 == 0){
            array[k][0] = temp2;
            array[k][1] = temp;
            k ++;
        }
    }
    /*
    for(int i = 0; i < k; i ++)
        printf("%c %c\n",array[i][0],array[i][1]);*/

    
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < k; j ++){
            if(str[i] == array[j][0]){
                str[i] = array[j][1];
                break;
            }
        }
    }
    printf("%s\n",str);
    
    return 0;
}