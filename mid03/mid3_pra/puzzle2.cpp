// puzzle2
#include <iostream>
#include <cmath>
#include <string>
#include <queue>
using namespace std;
#define MAXMOV 80

int ans_row[20] = {-1, 0,0,0,0, 1,1,1,1, 2,2,2,2, 3,3,3,3};
int ans_col[20] = {-1, 0,1,2,3, 0,1,2,3, 0,1,2,3, 0,1,2,3};

class State{
    public:
    int pz[4][4];
    int predir;
    int ex,ey;
    int g,h; //F = g+h
    State(int input[4][4]){
        for(int i = 0; i < 4; i ++){
            for(int j = 0; j < 4; j ++)
                pz[i][j] = input[i][j];
        }
        predir = -1;
        ex = ey = -1;
        g = h = 0;
        setHeuristic();
    }
    State(const State& in){
        for(int i = 0; i < 4; i ++){
            for(int j = 0; j < 4; j ++)
                pz[i][j] = in.pz[i][j];
        }
        ex = in.ex;
        ey = in.ey;
        predir = in.predir;
        g = in.g;
        h = in.h;
    }
    void setHeuristic()
    {
        int temph = 0;
        // manhatton
        for(int i = 0; i < 4; i ++){
            for(int j = 0; j < 4; j ++){
                if(!pz[i][j]) continue; //!
                temph += abs( i-ans_row[pz[i][j]] ) + abs( j-ans_col[pz[i][j]] );

                // at goal row
                if(i == ans_row[pz[i][j]]){
                    for(int k = j; k < 4; k ++ ){
                        if(!pz[i][k]) continue;
                        if( pz[i][k] < pz[i][j] && i == ans_row[pz[i][k]])
                            temph += 2;
                    }
                }
                // at goal col
                if(j == ans_col[pz[i][j]]){
                    for(int k = i; k < 4; k ++){
                        if(!pz[k][j]) continue;
                        if( pz[k][j] < pz[i][j] && j == ans_col[pz[k][j]]  )
                            temph += 2;
                    }
                }
                
            }
        }
        this->h = temph;
    }
    void update(int dir, int x, int y){
        predir = dir;
        swap(pz[ex][ey],pz[x][y]);
        ex = x;
        ey = y;
        g++;
        setHeuristic();
    }
    bool operator < (const State& rhs)const{
        return g+h > rhs.g + rhs.h;
    }
};

int main()
{
    int tempx, tempy;
    int in[4][4];
    // input
    for(int i = 0; i < 4; i ++){
        for(int j = 0; j < 4; j ++){
            cin >> in[i][j];
            if(in[i][j] == 0){
                tempx = i;
                tempy = j;
            }
        }
    }
    
    State s(in);
    s.ex = tempx;
    s.ey = tempy;

    priority_queue <State> q;
    q.push(s);
    
    int dirx[4] = {1,-1,0,0};
    int diry[4] = {0,0,1,-1};

    while( !q.empty()){
        State cur = q.top();
        if(cur.h == 0){
            cout << cur.g << endl;
            break;
        }
        q.pop();
        if(cur.g + cur.h > MAXMOV) 
            continue;

        for(int i = 0; i < 4; i ++){
            int newx = cur.ex + dirx[i];
            int newy = cur.ey + diry[i];

            if(newx < 0 || newy < 0 || newx > 3 || newy > 3)
                continue;
            
            if( (cur.predir == 0 && i == 1)||(cur.predir == 1 && i == 0)||(cur.predir == 2 && i == 3)||(cur.predir == 3 && i == 2) )
                continue;
            State next = cur;
            next.update(i,newx,newy);
            q.push(next);
        }
    }
    if(q.empty())
        cout << -1 << endl;
    return 0;
}