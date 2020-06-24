#include <stdio.h>
#include <math.h>
// 12615 - Knight Search
char a[102][102];
char str[11] = "ICPCASIASG";
int ans;
int n;

void check(int x,int y,int step)
{
    if(step == 10){
        ans = 1;
        return;
    }
    // knight moving mode
    for(int i = -2; i <= 2 && !ans ; i ++){
        for(int j = -2; j <= 2 && !ans ; j ++){
            // if not knight moving or out of bound, continue
            if(pow(i,2)+pow(j,2) != 5 || x+i >= n || y+j >= n || x+i <0 || y+j <0)
                continue;
            // if match, next recursion
            if(a[x+i][y+j] == str[step])
                check(x+i,y+j,step+1);
        }
    }
    return;
}

int main()
{
    scanf("%d",&n);
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++){
            scanf(" %c",&a[i][j]);
        }
    }

    // must set to zero, or else segfault
    int count=0,x=0,y=0;
    // once the ans=1, break and printf
    // else run through all cells
    while(count < n*n && !ans){
        x = count/n;
        y = count%n;
        if(a[x][y] == str[0])
            check(x,y,1);
        count ++;
    }
    printf("%s\n", ans ?"YES":"NO");
    
    return 0;
}