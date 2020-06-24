//mosnter2

#include <iostream>
#include <queue>
//#include <algorithm>
using namespace std;
/*
    Note: min max !
*/

struct State{
    int lv,hp,_hp,dist;
    State( int lv, int hp, int _hp, int dist) : lv(lv),hp(hp),_hp(_hp),dist(dist){}
};

bool vis[20][310][410];

int dmg_level[20];
int heal_level[20];

int main()
{
    // _ for monster
    int maxl, maxhp, _hp, _mdg;
    cin >> maxl >> maxhp >> _hp >> _mdg;
    for(int i = 1; i <= maxl; i ++)
        cin >> dmg_level[i] >> heal_level[i];

    // start implementing search states
    queue<State> q;
    //push first state into it
    q.push( State(1,maxhp,_hp,0));
    vis[1][maxhp][_hp] = true;

    while(!q.empty()){
        State cur = q.front();
        if(!cur._hp) break;
        q.pop();

        // attack
        // 自己不會死掉、先把對方砍死 這邊大於等於即可 !!
        // 使用max因為判cur_hp==0 為怪獸死亡
        if(cur.hp - _mdg > 0 || dmg_level[cur.lv] >= cur._hp ){
            State next(cur.lv, cur.hp-_mdg, max(0,cur._hp-dmg_level[cur.lv]), cur.dist+1 );
            if( !vis[next.lv][next.hp][next._hp] ){
                q.push(next);
                vis[next.lv][next.hp][next._hp] = true;
            }
        }
        // heal 有效補血
        // 補血>傷害, 就算補0血也不會死掉 因為補血量可能可以==0
        // 補血之後最多補到上限 thus use min
        if(heal_level[cur.lv] -_mdg > 0 && cur.hp -_mdg > 0){
            State next(cur.lv, min(maxhp,cur.hp+heal_level[cur.lv])-_mdg, cur._hp, cur.dist+1 );
            if( !vis[next.lv][next.hp][next._hp] ){
                q.push(next);
                vis[next.lv][next.hp][next._hp] = true;
            }
        }
        // level up
        if(cur.lv < maxl && cur.hp-_mdg > 0){
            State next(cur.lv+1, cur.hp-_mdg, cur._hp, cur.dist+1 );
            if( !vis[next.lv][next.hp][next._hp] ){
                q.push(next);
                vis[next.lv][next.hp][next._hp] = true;
            }
        }
    } // end while
    if(q.empty())
        cout << -1 << endl;
    else cout << q.front().dist << endl;

    return 0;
}