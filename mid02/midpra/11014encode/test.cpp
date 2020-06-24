#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include "function.h"
using namespace std;

void RleCodec::encode()
{
    char prev = '\0';
    int cnt = 0;
    stringstream ss;
    for(auto c:code_str){
        if(c != prev){
            if(cnt > 0){
                if(cnt == 1)
                    ss << prev;
                else if(cnt == 2)
                    ss << prev << prev;
                else ss << cnt << prev;
            }
            cnt = 1;
            prev = c;
        }
        else cnt++;
    }
    if(cnt == 1)
        ss << prev;
    else if(cnt == 2)
        ss << prev << prev;
    else ss << cnt << prev;

    code_str = ss.str();
    encoded = true;
}

void RleCodec::decode()
{
    stringstream ss;
    string intstr;
    for(auto c:code_str){
        if(isdigit(c)){
            intstr.push_back(c);
        }
        else{
            int cnt = 0;
            stringstream is{intstr};
            is >> cnt;
            if(cnt == 0)
                ss << c;
            else {
                for(int i = 0; i < cnt; i ++)
                    ss << c;
            }
            intstr.clear();
        }
    }
    code_str = ss.str();
    encoded = false;
}