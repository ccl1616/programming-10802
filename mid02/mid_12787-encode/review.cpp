#include <iostream>
#include <sstream>
#include <string>
using namespace std;
#include "function.h"

void Base64Codec::encode()
{
    stringstream ss;
    int binary_arr[1000000] = {};
    //put char to 8bit binary
    int strlen = code_str.size();
    
    for(int i = 0; i < strlen; i ++){
        int temp = (int)code_str[i];
        //put decimal into 8 bit binary
        int ptr = 7;
        while(ptr >= 0){
            binary_arr[i*8 +ptr] = temp%2; //*8 !!
            temp /= 2;
            ptr --;
        }
    }

    //deal with its left overs
    int six_set = 0;
    int equal = 0;
    if(strlen*8 %6 == 0 )
        six_set = strlen*8 /6;
    else{
        six_set = strlen*8/6 +1;
        equal = 6 - strlen*8%6;
        equal /= 2;
    }

    //put them into char by encodeCharater
    for(int i = 0; i < six_set; i ++){
        int temp = 0;
        int ptr = 5;
        int base = 1;
        while(ptr >= 0){
            temp += binary_arr[i*6 +ptr] * base; //*6 !!
            base *= 2;
            ptr --;
        }
        ss << encodeCharacter(temp);
    }
    while(equal--){
        ss << "=";
    }
    code_str = ss.str();
}