// 12266
#include <iostream>
#include <map>
#include <string>
using namespace std;

/*
    Note1: the usage of "stringname.sub(begin char pos, sunstring length)"
    Note2: initializing map's way
*/

map<string,string> dictionary = 
{
    {"Wa","Waninoko"},
    {"Mi","Milotic"},
    {"Ma","Magikarp"},
    {"Va","Vaporeon"},
    {"Sh","Sharpedo"},
    {"Tapu","Tapu Fini"},
    {"Em","Empoleon"},
    {"La","Lapras"},
    {"Pi","Pikachu"},
    {"Pe","Pikachu"},
    {"Me","Mega Gyarados"}
};

int main()
{
    int n;
    cin >> n;
    while(n--){
        string name,school;
        cin >> name >> school;
        string sub = name.substr(0,4);
        auto poke = dictionary.find(sub);
        if(poke != dictionary.end()){ 
            // we find the Tapu guy
            cout << name << " " << "the" << " " << school << " " << poke->second << endl;
            continue;
        }
        sub = name.substr(0,2);
        poke = dictionary.find(sub);
        if(poke != dictionary.end())
            cout << name << " the" << " " << school << " " << poke->second << endl;
        else 
            cout << name << " is looking for a Chinese tutor, too!\n";
    }
    return 0;
}