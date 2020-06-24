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
    
    for(int town = 1; town <= N; town ++){
        queue<node> Q;
        fill(visited, visited+100005, -1);
        int ans_appear = 0;
        node ptr(town,0);
        Q.push(ptr); //起點進queue

        while(!Q.empty()){
            if(ans_appear == 1 ) break;
            // 首先提出第一個
            node now = Q.front();
            Q.pop();
            // 判這個拜訪過沒
            if(visited[now.id] == 1)
                continue;
            // 沒拜訪過的話就標記
            visited[now.id] = 1;
            // 看這個點是不是目標點
            for(auto check:diamondTowns){
                if(check == now.id){
                    Dist[town] = now.dist;
                    ans_appear = 1;
                    break;
                }
            }
            // 不是目標點的話 就把這個點的鄰居都推入Queue
            if(!ans_appear){
                for(auto i:G[now.id]){
                    node y(i,now.dist+1); //鄰居跟自己都差一步
                    Q.push(y);
                }
            }
        }
    }
    // Output
    for (int i = 1; i <= N; i++) {
        cout << Dist[i] << '\n';
    }
    return 0;
}