// 10861
#include <iostream>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <stack>
using namespace std;
/*
    Note1: becareful of the printout format
        "Case : i Yes\n" , there's a space between num and Yes
    Note2: getchar(); after input N, need to get a enter
    !! : use getline to get string @29: cause (a line which contains the newline character only) may 
        be contained in the input and it should be considered as a valid
*/

map<char,char> parens = { {'{','}'}, { '(',')'}, { '<','>'}, { '[',']' } };
set<char> ref_left = { '{','(','<','['};
set<char> ref_right = { '}',')','>',']'};

int main()
{
    int N;
    cin >> N;
    string str;
    getchar(); //!!
    for(int i = 1; i <= N; i ++){
        int ans = -1;
        stack<char> S;
        getline(cin,str);
/*
        cin >> str;
        getchar();
*/
        // watch through every char
        for(auto c:str){
            if(ref_left.find(c) != ref_left.end()){
                // this is a left
                S.push(c);
            }
            else if( ref_right.find(c) != ref_right.end()){
                if( S.empty() ){
                    ans = 0;
                    break;
                }
                else if (parens[S.top()] != c ){
                    ans = 0;
                    break;
                }
                else S.pop();
            }
        } //end for
        cout << "Case " << i << ":";
        if( !S.empty() || ans==0 )
            cout << " No\n";
        else cout << " Yes\n";
    } //end while
    return 0;
}
