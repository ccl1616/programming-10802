// 11485 - Use std::set
// AC version
// take care of 82 & 129

#include <iostream>
#include <set>
#include <algorithm>
#include <bitset>
#include <vector>
#include <cstring>
#include <string>
#include <string.h>
#include <cstdbool>
using namespace std;
void FindVector(int key);

set< vector<int> > SET;
set<int> KEY;
vector<int> VEC; //temp use

vector<int> inputvector()
{
    vector<int> RET;
    RET.push_back(0);
    int i;
    int size = 0;
    int sum = 0;
    while(cin >> i && i != 0){
        RET.push_back(i);
        size++;
    }
    for(int i = 1 ; i <= size ; i ++)
        sum += RET[i] * (size-i+1);
    RET[0] = sum;   // 把key存在array[0], 要刪比較好找

    auto x = KEY.find(sum);
    if (x != KEY.cend()) {
    //  這個key已經出現過了 要把舊的換掉
        cout << "exist\n";
        FindVector(sum);
        vector<int> RET2;
        RET2.push_back(sum);
        i = 1;
        int j = size;
        while(i <= size){
            RET2.push_back( RET[j--] );
            i++;
        }
        // 要算新的sum 並且塞進去
        sum = 0;
        for(int i = 1 ; i <= size ; i ++)
            sum += RET2[i] * (size-i+1);
        RET2[0] = sum; 
        KEY.insert(sum);

        return RET2;
    }
    else{
        KEY.insert(sum);
        return RET;
    }
}

// find the "key" vector, erase vector, erase this key from the set
void FindVector(int key)
{
    for(auto it = SET.begin(); it != SET.end(); ) {
        if( (*it)[0] == key){
            SET.erase(it);
            KEY.erase(key);
            return;
        }
    }
    cout << "not find\n";
    return ;
}

void PrintAll()
{
    for(auto S:SET){
        VEC = S;
        int i = 0;
        for(auto V:VEC){
            
            if(i == 0){
                i++;
                continue;
            }
            else{
                cout << V << " ";
                i++;
            }
        }
        cout << endl;
    }
}

// for range out, fast count the key of it
int CountKey()
{
    vector<int> RET;
    RET.push_back(0);
    int i;
    int size = 0;
    int sum = 0;
    while(cin >> i && i != 0){
        RET.push_back(i);
        size++;
    }
    for(int i = 1 ; i <= size ; i ++)
        sum += RET[i] * (size-i+1);
    return sum;
}

void RangeOut()
{
    int sum1 = 0;
    int sum2 = 0;

    sum1 = CountKey();
    sum2 = CountKey();

    int max = sum1>sum2 ?sum1:sum2;
    int min = sum1<sum2 ?sum1:sum2;
    //cout << "min:" << min << " " << "max:" << max << endl;
    
    for(auto S:SET){
        VEC = S;
        int flag = 1;
        int i = 0;
        for(auto V:VEC){
            if(i == 0){
                if(V > max || V < min ){
                    flag = 0;
                    break;
                }
                else i ++;
            }
            else if(V == VEC[1]){
                cout << V;
                i ++;
            }
            else {
                cout << " " << V;
                i ++;
            }
        }
        if(flag)
            cout << endl;
    }
}

int main()
{
    char cmd[100] = {};
    while(cin >> cmd){
        if(!strcmp(cmd,"insert")){
            vector<int> RET;
            RET = inputvector();
            SET.insert( RET );
        }
        else if(!strcmp(cmd,"range_out")){
            RangeOut();
        }
        else if(!strcmp(cmd,"output")){
            PrintAll();
        }
    }
    return 0;
}