#include <stdio.h>
// 12611 - The Same Calendar
// found the year that have same weekday
// be careful of the leap years

// by def of leap year
// 1 means that year has 364+1 days == common year
// 2 means that year has 364+2 days == leap tear
// 364 = 7*52
// return 1,2 : the redundant days of each year

int check(int year)
{
    if(year % 4 == 0){
        if(year % 100 == 0){
            if(year % 400 == 0)
                return 2;
            else return 1;
        }
        else return 2;
    }
    else return 1;
}

int main()
{
    int t,input;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&input);

        int flag,count;
        // check whether input is leap or not
        flag = check(input); 
        // add the extra days on input year
        count = flag; 
        int i;
        for(i = input+1; i < __INT32_MAX__; i ++){
            count += check(i);
            if(count % 7 == 0 && check(i+1) == flag )
                break;
        }
        printf("%d\n",i+1);
    }
    return 0;
}