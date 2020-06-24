// 12264
#include <iostream>
#include <queue>
#include <list>
#include <string>
using namespace std;

/*
    Note1: the usage of queue<int> Country[3];
    Note2: because you cannot scan through the line if the line if made up of queue
            , so using list for line would be a must
            the usage of list, 
            listname.push_back(data);
            listname.pop_front();
            access element: listname.front(); .back();
    Note3: after dequeue, if this country is empty, pop it
        deque: pop person, then pop country if this country is now empty
*/

// npk
queue<int> Country[3];
list<int> Line; // 0,1,2

void enqueue(int id)
{
    int temp = id%3;
    Country[temp].push(id);
    for(auto i:Line){
        if(i == temp)
            return;
    }
    Line.push_back(temp);
}

void dequeue()
{
    int i = Line.front();
    cout << Country[i].front() << endl;
    Country[i].pop();

    // !!
    if( Country[i].empty() )
        Line.pop_front();
    return;
}

int main()
{
    int n;
    cin >> n;
    string cmd;
    int id;
    while(n--){
        cin >> cmd;
        if(cmd == "DEQUEUE"){
            dequeue();
        }
        else if(cmd == "ENQUEUE"){
            cin >> id;
            enqueue(id);
        }
    }
    return 0;
}