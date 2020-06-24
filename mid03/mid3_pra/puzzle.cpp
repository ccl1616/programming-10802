#include <iostream>
#include <queue>
#include <cmath> // for abs
using namespace std;
/*
    Notes:
    1. puzzle part
    - pre_dir to record previous moved direction, avoid left-right || up-down move
    - 113~116, find empty tile while input, and save the information into class

    2. find state
    - Ａ* algorithm: f = g+h, g=initial->current steps, h=heuristic
    - here, heuristic = manhatton + linear conflict*2 ! (62~78 be careful for finding linear conflict pairs!)
    - update function
    - reload comparision rules

    3. else
    - update(), operator< (dealing with priority queue's priority)
    - 149~152 避免把剛剛做的那部再挪回來
    - MAXMOV avoid TLE
*/


#define MAXMOV 80 // avoid TLE , 148
const int goal_row[] = {-1, 0,0,0,0, 1,1,1,1, 2,2,2,2, 3,3,3};
const int goal_col[] = {-1, 0,1,2,3, 0,1,2,3, 0,1,2,3, 0,1,2};

class State{
    public:
        int pz[4][4];
        int empty_x, empty_y;
        int g,h; //f = g+h, g=initial->current, h=heuristic
        int pre_dir;

        State(int in[4][4]){
            for(int i = 0; i < 4; i ++){
                for(int j = 0; j < 4; j ++){
                    pz[i][j] = in[i][j];
                }
            }
            g = 0;
            empty_x = -1;
            empty_y = -1;
            pre_dir = -1;
            SetHeuristic(); // set here!
        }

        // copy constructor
        State(const State& rhs){
            for(int i = 0; i < 4; i ++){
                for(int j = 0; j < 4; j ++){
                    pz[i][j] = rhs.pz[i][j];
                }
            }
            this->empty_x = rhs.empty_x;
            this->empty_y = rhs.empty_y;
            this->g = rhs.g;
            this->h = rhs.h;
            this->pre_dir = rhs.pre_dir;
        }

        void SetHeuristic()
        {
            int temp_h = 0;
            for(int i = 0; i < 4; i ++){
                for(int j = 0; j < 4; j ++){
                    if(!pz[i][j]) continue;

                    // manhatton
                    int goalr = goal_row[ pz[i][j]];
                    int goalc = goal_col[ pz[i][j]];
                    temp_h += abs(i - goalr ) + abs(j - goalc );

                    // Linear Conflict
                    // i'm at goal row
                    if(i == goalr){
                        for(int k = j; k < 4; k ++){
                            if(!pz[i][k]) continue;
                            if(pz[i][j] > pz[i][k] && goalr == goal_row[pz[i][k]])
                                temp_h += 2;
                        }
                    }
                    // i'm at goal col
                    if(j == goalc){
                        for(int k = i; k < 4; k ++){
                            if(!pz[k][j]) continue;
                            if(pz[i][j] > pz[k][j] && goalc == goal_col[pz[k][j]])
                                temp_h += 2;
                        }
                    }

                }
            }
            this->h = temp_h;
        } //end void

        void update(int i, int newx, int newy)
        {
            pre_dir = i;
            swap(pz[newx][newy],pz[empty_x][empty_y]);
            empty_x = newx;
            empty_y = newy;
            g++;
            SetHeuristic();
        }

        /*overloaded operator
        (To sort elements in priority queue)*/
        // 編列state的priority, priority大的會在queue front
        // state priority < state priority
        // the one with bigger F would have smaller priority
        bool operator < ( const State& rhs)const
        {
            return g+h > rhs.g+rhs.h;
        }
};

int main()
{
    int temp_ex, temp_ey;
    int pz[4][4];
    for(int i = 0; i < 4; i ++){
        for(int j = 0; j < 4 ; j ++){
            cin >> pz[i][j];
            if(!pz[i][j]){
                temp_ex = i;
                temp_ey = j;
            }
        }
    }
    State s(pz);
    s.empty_x = temp_ex;
    s.empty_y = temp_ey;

    priority_queue<State> q;
    q.push(s);

    const int dirx[4] = {1,-1,0,0};
    const int diry[4] = {0,0,1,-1};

    // kinnda like BFS
    while( !q.empty()){
        auto curstate = q.top();
        if(curstate.h == 0){
            cout << curstate.g << endl;
            break;
        }
        q.pop();
        
        // avoid TLE
        if(curstate.h + curstate.g > MAXMOV)
            continue;

        for(int i = 0; i < 4; i ++){
            int newx = curstate.empty_x + dirx[i];
            int newy = curstate.empty_y + diry[i];

            if(newx < 0 || newx > 3 || newy < 0 || newy > 3)
                continue;
            
            // avoid return last step _version1, too smart
            /*
            if( i == (curstate.pre_dir^1) )
                continue;*/
            // avoid return last step _version2, my version
            if( (curstate.pre_dir==0 && i == 1) || (curstate.pre_dir==1 && i == 0) || (curstate.pre_dir == 2 && i == 3) || (curstate.pre_dir==3 && i == 2) )
                continue;

            // !
            State nextstate = curstate;
            nextstate.update(i,newx,newy);
            q.push(nextstate);
        }
    }
    if(q.empty())
        cout << -1 << endl;

    return 0;
}