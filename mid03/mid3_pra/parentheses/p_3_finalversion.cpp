#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <cstdbool>
#include <stack>
using namespace std;
map <char,char> dictionary = 
{
    { '{','}'},
    { '(',')' },
    { '[',']' },
    { '<','>'}
};

// parenthesis
int main()
{
    string str;
    int N;
    cin >> N;
    getchar();
    for(int i = 1;i <= N; i ++){
        bool valid = true;
        getline(cin,str);
        stack<char> q;
        for(auto c:str){
            if(c == '{' || c == '(' || c == '[' || c == '<')
                q.push(c);
            else{
                if(q.empty()) {
                    valid = false;
                    break;
                }

                char temp = q.top();
                q.pop();
                if( dictionary[temp] != c){
                    valid = false;
                    break;
                }
            }
        }
        if(!q.empty()) valid = false;

        if (valid) cout << "Case " << i << ": Yes\n";
        else cout << "Case " << i << ": No\n";
    }
}