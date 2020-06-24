// 11498
#include <iostream>
#include <set>
using namespace std;
/*
    Note: need to setname.clear() everytime
    or
    make new set several times
*/

int main()
{
    int N;
    while(scanf("%d",&N) && N != 0){
        //getchar(); 
        set<int> allnode;
        set<int> parnode;
        for(int i = 0; i < N; i ++){
            int a,b;
            scanf("%d %d\n",&a,&b);
            allnode.insert(a);
            allnode.insert(b);
            parnode.insert(a);
        }
        int temp;
        cin >> temp;
        //getchar();
        cout << allnode.size()-parnode.size() << endl;
    }
    
    return 0;
}