#include<stdio.h>
#include <string.h>
//12604 - N-Queens M-Rooks Problem v1
// 2/4 wa+tle
int valid_queen(int row, int col);
int valid_rook(int row, int col);
void place(int row);
int map[10]; // at most 9*9 chess board
int q[10];
int ans,size;
int n,m;
int qd,rd;

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

void place(int row)
{
    // int n = size;
    if(row == size) {
        ans ++;
    }
    for(int i = 0; i < size; i ++){
        map[row] = i;
        if(qd < n){
            qd ++;
            q[row] = 1;
            if(valid_queen(row,i))
                place(row+1);
            q[row] = 0;
            qd --;

            if(rd < m && valid_rook(row,i)){
                rd ++;
                place(row+1);
                rd --;
            }
        }
        else if(rd < m && valid_rook(row,i)){
            rd ++;
            place(row+1);
            rd --;
        }
        map[row] = -1;
    }


    /*
    if(qd < n){
        for(int j = 0; j < n; j ++){
            map[row] = j;

            if(valid_queen(row,j)){
                qd ++;
                q[row] = j;
                place(row + 1, size);
            }
            else if(valid_rook(row,j)){
                place
            }
        }
    }
    
    else if(rd < m){
        for(int k = 0; k < m; k ++){
            if(valid_rook(row,k) ){
                rd ++;
                map[row] = k;
                place(row+1, size);
            }
        }
    }*/
    return;
}

int valid_queen(int row, int col)
{
    int i;
    for(i = 0; i <= row - 1; i++){
        if(map[i] == col || map[i] == col - row + i || map[i] == col + row - i)
            return 0;
    }
    return 1;
}

int valid_rook(int row, int col)
{
    int i;
    for(i = 0; i <= row - 1; i++){
        if(map[i] == col )
            return 0;
    }
    return 1;
}

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

