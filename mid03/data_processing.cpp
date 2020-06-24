#include <iostream>
#include <map>
#include <string>
#include <set>
using namespace std;

map<string, int> BA;
map<string, int> Count;
map<int, string> Index;


int main()
{

    string str;
    char space;
    int k = 1;
    int p = 1;

    while( cin >> str ){
        if(str == "----------") break;
        cin >> k;
        BA.insert( pair<string,int>(str,k));
        Count.insert( pair<string,int>(str,0));
        Index.insert( pair<int,string>(p,str));
        p++;
    }
    Count.insert(pair<string,int>("unlabeled",0));
    string name;
    int totalnumdata = 0;
    while(cin >> name ){
        if(name == "exit") break;
        totalnumdata++;
        cin >> str;
        
        cout << name << " ";
        auto i = BA.find(str);
        if(i != BA.end()){
            cout << i->second << endl;
            auto j = Count.find(str);
            j->second++;
        }
        else{
            cout << "unlabeled\n";
            auto j = Count.find("unlabeled");
            j->second ++;
        }
    }

    cout << "\ntotal # of data: " << totalnumdata << endl;
    for(auto i:Index){
        cout << i.second << ": ";
        auto j = Count.find(i.second);
        cout << j->second << endl;
    }
    auto num = Count.find("unlabeled");
    cout << "unlabeled: " << num->second << endl;

    BA.clear();
    Count.clear();
    Index.clear();


    return 0;
}
