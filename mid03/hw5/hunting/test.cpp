// by teacher

#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// G[i] is the neighbor towns of town i
vector<int> diamondTowns; //the IDs of the diamond towns 
vector<int> G[100005]; //G[i] is vector,containing all neighbor towns of town i 
int Dist[100005]; //Dist[i] means the shortest distance to get diamond from town i 
int visited[100005];

struct node {
    int id;
    int dist;
    node(int id, int l) {
        this->id = id;
        this->dist = l;
    }
};

int main() {
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
    
    //put all diamondtown into queue
    for (auto i: diamondTowns) {
        Q.push(node(i, 0));
    }

    while (!Q.empty()) {
        // deal with everyone in queue
        node cur = Q.front();
        Q.pop();
        if (Dist[cur.id] == -1) {
            Dist[cur.id] = cur.dist; //從這裡走起
            for (auto i: G[cur.id]) {
                Q.push(node(i, cur.dist+1)); //鄰居每次都跟我差一步
            }
        }
    }

    // Output
    for (int i = 1; i <= N; i++) {
        cout << Dist[i] << '\n';
    }
    return 0;
}