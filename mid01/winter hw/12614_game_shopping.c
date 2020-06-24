#include <stdio.h>
// 12614 - Game Shopping 

int n; // number of games
int m; // number of coins

int game[1005];
int coin[1005];

int main()
{
    int temp = 0;
    int ans = 0 ;
    scanf("%d %d",&n,&m);

    for(int i = 0; i < n; i ++)
        scanf("%d",&game[i]);

    for(int i = 0; i < m; i ++){
        scanf("%d",&coin[i]);
    }
    int i = 0;
    temp = coin[0];
    for(int i = 0; i < n && ans <= m; i ++){
        if(ans >= m)
            break;
        if(temp >= game[i]){
            ans ++;
            temp = coin[ans];
        }
    }

    printf("%d\n",ans);
    return 0;
}
