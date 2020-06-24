#include <stdio.h>
int vld(int row);
int n, m, lane[11], qr[11], ans, qed, red;

void rec(int row){
    if(row == n+m) {ans++; return;}    
    // 如果走到這一步，代表是可行解
    
    for(int i=0; i<n+m; i++){
        lane[row] = i;

        // 如果有queen能放，就放queen
        if(qed<n){
            qr[row] = 1;    // 這個row放的是queen
            qed++;          // 使用queen的數量++
            if(vld(row)) rec(row+1);
            qr[row] = 0;    // 退出迴圈之後，重設這格的棋子種類
            qed--;          // 把皇后回收
            
            // 如果有rook可以放，就放到同一格試試
            if(red<m && vld(row)){
                red++;
                rec(row+1);
                red--;
            }
        }
        
        //如果沒有queen，就放rook
        else{
            if(red<m && vld(row)){
                red++;
                rec(row+1);
                red--;
            }
        }
        
        // 這一格得所有可能性都跑完了，換試試同一行的下一格
        lane[row] = -1;
    }
}

int vld(int row){
    for(int i=0; i<row; i++){
        
        // 如果這個棋子"或是"之前的所有棋子，其中一個是皇后，
        // 就用皇后的走法判斷(直橫斜)
        if(qr[i] || qr[row]){
            if(lane[i] == lane[row]          ||
               lane[i]-(row-i) == lane[row]  ||
               lane[i]+(row-i) == lane[row]) return 0;
        }
        
        // 當要比較的兩個棋子都是rook時，就只要判斷直的
        // (因為棋子不會在同一行)
        else
        if(lane[i] == lane[row]) return 0;
    }
    return 1;
}

int main(){
    while( scanf("%d%d", &n, &m)!=EOF ){
        ans = 0, qed = 0, red = 0;
        rec(0);
        printf("%d\n", ans);
    }
}