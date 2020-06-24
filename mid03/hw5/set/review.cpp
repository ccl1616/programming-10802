#include <iostream>
#include <algorithm> //for "reverse"
#include <vector>
#include <set>
#include <string>
#include <string.h>
/*
notes: 
    (1) overload mycomp
    (2) reverse(temp.begin(),temp.end()); is in <algorithm>, will automatically reverse the vector
*/

using namespace std;

int val(vector<int> VEC)
{
    int key = 0;
    int size = VEC.size();
    for(auto i:VEC){
        key += i*size;
        size--;
    }
    return key;
}

// !!
struct mycomp{
    bool operator() (const vector<int> &lhs, const vector<int> &rhs) const
    {
        return val(lhs) < val(rhs); 
        // if true, then lhs would infront of rhs, lhs-rhs (left side is head)
        // else swap
    }
};

vector<int> input_vec()
{
    vector<int> VEC;
    int i;
    while(cin >> i && i != 0){
        VEC.push_back(i);
    }
    return VEC;
}

void print_vec(vector<int> input)
{
    for(auto i:input)
        cout << i << " ";
}

set<vector<int>,mycomp> SET;
int main()
{
    char cmd[100] = {};
    while(cin >> cmd){
        if( !strcmp(cmd,"insert")){
            // read in 
            vector<int> temp = input_vec();
            int temp_key = val(temp);
            for(auto vec:SET){
                if(val(vec) == temp_key){
                    cout << "exist\n";
                    SET.erase(vec);
                    reverse(temp.begin(),temp.end()); 
                    break;
                }
            }
            SET.insert(temp);
        }
        else if(!strcmp(cmd,"output")){
            for(auto v:SET){
                print_vec(v);
                cout << endl;
            }
        }
        else if(!strcmp(cmd,"range_out")){
            int from = val( input_vec() );
            int to = val( input_vec() );
            for(auto v:SET){
                if( val(v) > to )
                    break;
                if( val(v) >= from && val(v) <= to){
                    print_vec(v);
                    cout << endl;
                }
            }
        }
    }
    return 0;
}
