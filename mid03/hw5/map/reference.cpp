#include "function.h"
#include <iostream>
#include <set>

namespace oj{
    void insert(std::map<int,String> &ma,int key,const std::string &str)
    {
        // insert if this key hasn't exist
        auto prev = ma.find(key);
        std::string RET;
        if(prev != ma.end()){
            // means this key is already exist
            // prev now is the pair (with key)
            RET = str + prev->second.str; // .str !
            ma.erase(prev);
        }
        else RET = str;
        
        // the pair format should follow the definition in main.cpp line32
        ma.insert( std::pair<int,String> (key,String(RET) ) ); 
        //ma[key] = RET; this cannot work
    }

    void output(const std::map<int,String> &ma,int begin,int end)
    {
        // output those string whose key is in [begin,end]
        for(auto &pair: ma){
            // 這邊end begin 不可以相反
            // >end 一定不在範圍
            if(pair.first > end)
                break;
            if(pair.first >= begin)
                std::cout << pair.second << " ";
        }
    }
    void erase(std::map<int,String> &ma,int begin,int end)
    {
        // this is not working
        /*
        for(auto pair: ma){
            if(pair.first >= begin && pair.first <= end )
                ma.erase(pair.first);
        }
        */

        // put the key which we wanted to erase, into a set
        // ma.erase(key), would erase the key&content by key, in the map
        
        std::set<int> eraseKeys;
        for (auto &i:ma){
            if(i.first >= begin && i.first <= end)
                eraseKeys.insert(i.first);
        }

        for(auto key:eraseKeys){
            ma.erase(key);
        }
        
        
    }

    std::ostream& operator<<(std::ostream &out,const std::map<int,String> &ma)
    {
        for(auto &pair:ma){
            out << pair.second << " "; 
        }
        return out;
    }
}
