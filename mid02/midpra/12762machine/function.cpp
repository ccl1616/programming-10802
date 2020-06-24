#include "function.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cstdbool>
#include <iostream>
#include <sstream>  
#include <stdio.h>
#include <climits>

using namespace std;
#define MAX 10000
int upbound = MAX;
int lowerbound = 0;

Engineer::Engineer(){ 
    init();
}

Engineer::~Engineer(){
}

void Engineer::init(){
    count = 0;
    for(int i = 0; i < 200; i ++){
        value_history[i] = 0;
        action_history[i] = 0;
        answer_history[i] = false;
    }
    upbound = MAX;
    lowerbound = 0;
}

void Engineer::GetAnswer(bool ans)
{
    answer_history[count] = ans;
}

void Engineer::MakeQuery(char* query_str){
    // greater less guess 
    if(count == 0){
        count ++;
        strcpy(query_str,"less 10000");
        value_history[count] = MAX;
        action_history[count] = 1;
    }
    else{
        //cout << "before:"<< lowerbound << " " << upbound << endl;
        int i = count;
        if(answer_history[i]){
            // num is > value, lowerbond = value+1
            if(action_history[i] == 0){
                if(value_history[i] >= lowerbound)
                    lowerbound = value_history[i]+1;
            }
            // num is < value, upperbond = value-1
            else if(action_history[i] == 1){
                if(value_history[i] <= upbound)
                    upbound = value_history[i]-1;
            }
        }
        else{
            // num isnot > value, num is <= value
            if(action_history[i] == 0){
                if(value_history[i] < upbound)
                    upbound = value_history[i];
            }
            // num isnot < value, num is >= value
            else if(action_history[i] == 1){
                if(value_history[i] > lowerbound)
                    lowerbound = value_history[i];
                if(count == 1){
                    //第一回合就錯 代表是>10000的數字 提高上限
                    upbound = INT32_MAX;
                }
            }
            //猜到只剩0還是錯 代表是負數 下限為最負
            else if(action_history[i] == 2 && value_history[i] == 0 && upbound == lowerbound && lowerbound == 0)
                lowerbound = -1*INT32_MAX;
        }
        
        count ++;
        char op[100];
        if(upbound == lowerbound){
            strcpy(query_str,"guess");
            action_history[count] = 2;
        }
        else if(upbound-lowerbound == 1){
            strcpy(query_str,"greater");
            action_history[count] = 0;
        }
        else {
            strcpy(query_str,"less");
            action_history[count] = 1;
        }

        int x;
        if(upbound < 0 && upbound-lowerbound == 1) //greater than lowerbond
            x = lowerbound;
        else if(upbound == lowerbound )
            x = upbound;
        else if(upbound == 1*INT32_MAX)
            x = upbound/2 + lowerbound/2 ;
        else x = (upbound+lowerbound)/2;

        char str[100];
        sprintf(str, "%d", x);
        strcat(query_str," ");
        strcat(query_str,str);

        value_history[count] = x;
        
    }

}
