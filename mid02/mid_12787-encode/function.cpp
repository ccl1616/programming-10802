#include <iostream>
#include "function.h"
using namespace std;
#include <sstream>
#include <string>

void Base64Codec::encode()
{
    // this array should be this big!! else runtime error!
    int binarynum[1000000] = {};
    int pos = 0; // this would be the number of character

    for(auto c : code_str){
        // put char to ascii num
        int temp = (int)c;
        
        // put ascii to binary
        for(int i = 7; i >= 0; i --){
            binarynum[pos*8 +i] = temp % 2; //*8 !!
            temp /= 2;
        }
        pos ++;
    }

    int add = 0;
    // 6 bits a team, deal with left overs
    if(pos * 8 % 6 != 0){
        add = (6 - (pos*8)%6)/2;
        pos = (pos*8)/6 + 1;
    }
    else pos = (pos*8)/6;
    
    // convert them
    stringstream os;
    int i = 0;
    for(int i = 0; i < pos; i ++){
        int base = 1;
        int t = 5;
        int temp = 0;
        while(t >= 0){
            temp += binarynum[i*6 + t]* base;
            base *= 2;
            t--;
        }
        char cc;
        cc = encodeCharacter(temp);
        os << cc;
    }

    /*
    int base = 1, idxx = 0,trans = 0;
    while(pos--){
        int i = 5;
        while(i >= 0){
            trans += binarynum[idxx*6 + i]*base;
            base *= 2;
            i--;
        }
        char ccc;
        ccc = encodeCharacter(trans);
        os << ccc;
        idxx++;
        trans = 0;
        base = 1;
    }
    */
    // add = if there should
    while(add--)
        os << '=';
    code_str = os.str();
    encoded = true;
}