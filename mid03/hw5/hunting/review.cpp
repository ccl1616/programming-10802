#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// G[i] saves the neighbor towns of town i
vector<int> diamondTowns;
vector<int> G[100005];
int Dist[100005];

struct node {
    int id;
    int dist;
    node(int id, int l) {
        this->id = id;
        this->dist = l;
    }
};

int main() {
    // # of towns, # of roads, # of diamond towns
    int N, M, K;
    cin >> N >> M >> K;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    for (int i = 0; i < K; i++) {
        int x;
        cin >> x;
        diamondTowns.push_back(x);
    }
    fill(Dist, Dist+100005, -1);

    queue<node> Q;
    // put all daimondtwons into Queue
    for(auto i:diamondTowns){
        Q.push( node(i,0));
    }
    // start BFS from eveeyr diamonds towns
    while(!Q.empty()){
        node now = Q.front();
        Q.pop();
        // if not yet visited
        if(Dist[now.id] == -1){
            Dist[now.id] = now.dist;
            for(auto i:G[now.id]){
                Q.push( node(i,now.dist+1) );
            }
        }
    }
    
    // Output
    for (int i = 1; i <= N; i++) {
        cout << Dist[i] << '\n';
    }
    return 0;
}