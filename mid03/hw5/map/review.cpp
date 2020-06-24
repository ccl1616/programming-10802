#include <iostream>
#include<cstddef>
#include<map>
#include<string>
#include <set>
#include "function.h"
using namespace std;

namespace oj
{
    void insert(std::map<int,String> &ma,int key,const std::string &str)
    {
        auto i = ma.find(key); //this returns pointer
        if(i == ma.end())
            ma.insert( pair<int,String>(key,str) );
        else i->second.str = str + i->second.str;
    }

    void output(const std::map<int,String> &ma,int begin,int end)
    {
        for(auto ptr:ma){
            if(ptr.first >= begin && ptr.first <= end)
                cout << ptr.second << " ";
        }
    }
	void erase(std::map<int,String> &ma,int begin,int end)
    {
        set<int> SET;
        for(auto i:ma){
            if(i.first >= begin && i.first <= end)
                SET.insert(i.first);
        }
        for(auto i:SET)
            ma.erase(i);
    }

	std::ostream& operator<<(std::ostream &out,const std::map<int,String> &ma)
    {
        for(auto pair:ma){
            out << pair.second << " ";
        }
        return out;
    }

}