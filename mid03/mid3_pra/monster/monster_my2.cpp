// monster
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <cstdbool>
using namespace std;

struct State{
    int my_level, my_hp, monster_hp;
    int step;
    State(int l, int h, int mh, int step) : my_level(l),my_hp(h),monster_hp(mh),step(step){}
};

int atk[20];
int heal[20];
bool vis[20][330][430];

int main()
{

    int L, HP, MHP, MDMG;
    cin >> L >> HP >> MHP >> MDMG;
    for(int i = 1; i <= L; i ++){
        cin >> atk[i];
        cin >> heal[i];
    }
    queue<State> q;
    q.push(State(1,HP,MHP,0)); //push initial state into queue
    vis[1][HP][MHP] = true;
    // start bfs
    while( !q.empty() ){
        State cur = q.front();
        if( cur.monster_hp <= 0)
            break;
        q.pop();

        // attack
        if(cur.my_hp - MDMG > 0 || atk[cur.my_level] >= cur.monster_hp){
            State s(cur.my_level, cur.my_hp - MDMG, cur.monster_hp-atk[cur.my_level], cur.step+1);
            if( !vis[s.my_level][s.my_hp][s.monster_hp] ){
                vis[s.my_level][s.my_hp][s.monster_hp] = true;
                q.push(s);
            }
        }
        // heal
        if( cur.my_hp - MDMG > 0 && heal[cur.my_level] - MDMG > 0){
            State s(cur.my_level, min(HP, cur.my_hp + heal[cur.my_level])-MDMG, cur.monster_hp,cur.step+1 );
            if( !vis[s.my_level][s.my_hp][s.monster_hp] ){
                vis[s.my_level][s.my_hp][s.monster_hp] = true;
                q.push(s);
            }
        }
        // level up
        if(  cur.my_hp-MDMG > 0 && cur.my_level < L ){
            State s(cur.my_level+1, cur.my_hp-MDMG, cur.monster_hp,cur.step+1 );
            if( !vis[s.my_level][s.my_hp][s.monster_hp] ){
                vis[s.my_level][s.my_hp][s.monster_hp] = true;
                q.push(s);
            }
        }

    }
    // you win, the win state is in queue
    if( !q.empty()){
        State s = q.front();
        cout << s.step << endl;
    }
    // you lose
    else cout << "-1\n";

    return 0;
}