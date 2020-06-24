#include<stdio.h>
#include <string.h>
//12604 - N-Queens M-Rooks Problem v2

int valid(int row);
void place(int row);
int map[10]; // at most 9*9 chess board
int q[10];
int ans,size;
int n,m;
int qd,rd; // for checking the q&r 's be putted number

int valid(int row){
    for(int i = 0; i < row; i ++){
        if(q[i] || q[row] ){
            if(map[i] == map[row] || map[i] == map[row]+row-i || map[i] == map[row]-row+i)
                return 0;
        }
        else if(map[i] == map[row])
            return 0;
    }
    return 1;
}

void place(int row)
{
    if(row == size) {
        ans ++;
    }
    for(int i = 0; i < size; i ++){
        map[row] = i;
        if(qd < n){
            qd ++;
            q[row] = 1;
            if(valid(row))
                place(row+1);
            q[row] = 0;
            qd --;

            if(rd < m && valid(row)){
                rd ++;
                place(row+1);
                rd --;
            }
        }
        else if(rd < m && valid(row)){
            rd ++;
            place(row+1);
            rd --;
        }
        map[row] = -1;
    }
    return;
}

int main()
{
    while( scanf("%d %d",&n,&m)!= EOF ){
        memset(map,0,sizeof(map));
        memset(q,0,sizeof(q));
        size = n+m;
        qd = rd = ans = 0;
        place(0);
        printf("%d\n",ans);
    }
    return 0;
}

