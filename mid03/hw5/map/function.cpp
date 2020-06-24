#include <set>
#include <iostream>
#include <string>
#include "function.h"
using namespace std;

namespace oj
{
    void insert(std::map<int,String> &ma,int key,const std::string &str)
    {
        auto ptr = ma.find(key);
        if(ptr == ma.cend())
            ma.insert( pair<int,String>(key,str) );
        else ptr->second.str = str + ptr->second.str;   //imp!!!!!
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
        set<int> temp;
        for(auto it:ma){
            if(it.first >= begin && it.first <= end)
                temp.insert(it.first);
        }
        for(auto num:temp){
            ma.erase(num);
        }
    }

	ostream& operator<<(std::ostream & out,const std::map<int,String> &ma)
    {
        for(auto pair:ma)
            out << pair.second << " ";
        return out;
    }
}
