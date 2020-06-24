#include <iostream>
#include <string>
#include <queue>
#include "function.h"

using namespace std;

class CDSystem{
public:
    CDSystem(int type = 0 ){
        this->Bag = new MultiSet_Tree();
    };
    ~CDSystem(){
        delete this->Bag;
    }
    void AddBall(const Color& ball){
        this->Bag->Insert(ball);
    }
    void RemoveBall(const Color& ball){
        this->Bag->Delete(ball);
    }
    int HowMany(const Color& ball) const{
        return this->Bag->Search(ball);
    }
    void PrintSet() const{
        this->Bag->PrintSet();
    }
private:
    MultiSet* Bag;
};

ostream& operator<<(ostream& os, const Color& ball){
    os << "(" << ball.r << ", " << ball.g << ", " << ball.b << ")";
    return os;
}

void MultiSet_Tree::PrintSet() const{
    queue<pair<Node *, int>> q;
    q.emplace(this->root, 0);
    while (!q.empty()){
        Node *cur = q.front().first;
        int level = q.front().second;
        q.pop();
        if (cur == NULL)
            continue;
        cout << "(" << cur->key << ", " << cur->value << ", " << level << ") ";
        q.emplace(cur->left, level + 1);
        q.emplace(cur->right, level + 1);
    }
    cout << endl;
}

int main(int argc, char* argv[]){
    CDSystem* Monitor;

    int T;
    cin >> T;
    for(int t=1; t<=T; t++){
        cout << "Case #" << t << ":\n";
        Monitor = new CDSystem();
        int N;
        cin >> N;
        
        while( N-- ){
            string op;
            int r, g, b;
            cin >> op;
            if( op == "PrintSet" ){
                Monitor->PrintSet();
            }
            else{
                cin >> r >> g >> b;
                Color ball(r,g,b);
                if( op == "+" ){
                    Monitor->AddBall( ball );
                }
                else if( op == "-"){
                    Monitor->RemoveBall(ball);
                }
                else{
                    cout << Monitor->HowMany(ball) << endl;
                }
            }
        }

        delete Monitor;
    }
    return 0;
}