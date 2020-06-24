// by duckie, using map

#include<iostream>
#include<algorithm>
#include<set>
#include<map>
#include<string>
#include<vector>
using namespace std;
int count_key(vector<int> vec){
    int size = vec.size();
    int key = 0;
    for(int i = 0;i < size ; i++)
        key += vec[i] * (size-i);
    return key;
}
int main(){
    map<int,vector<int>> t_set;
    for(string cmd;cin >> cmd;){
        if(cmd == "insert"){
            int key;
            vector<int> tmp;
            for(int i;cin >>i;){
                if(i == 0) break;
                tmp.push_back(i);
            }key = count_key(tmp);
            if(t_set.count(key)){
                cout<<"exist\n";
                t_set.erase(key);
                reverse(tmp.begin(),tmp.end());
                key = count_key(tmp);
            }
                t_set.insert(pair<int,vector<int>>(key,tmp));
        }else if(cmd == "range_out"){
            int key_1,key_2;
            vector<int> tmp_1,tmp_2;
            for(int i;cin >>i;){
                if(i == 0) break;
                tmp_1.push_back(i);
            }key_1 = count_key(tmp_1);
            for(int i;cin >>i;){
                if(i == 0) break;
                tmp_2.push_back(i);
            }key_2 = count_key(tmp_2);
            for(auto i = t_set.begin(); i != t_set.end(); ++i){
                auto key = (*i).first;
                auto vec = (*i).second;
                if(key >= key_1 && key <= key_2){
                    for(int k = 0;k < vec.size();k++)
                        cout<<vec[k]<<' ';
                    cout<<endl;
                }
            }
        }else if(cmd == "output"){
            auto it = t_set.begin();
            for(auto i = t_set.begin(); i != t_set.end(); ++i){
            const auto &j = (*i).second;
            for(int k = 0;k < j.size();k++)
                cout<<j[k]<<' ';
            cout<<endl;
            }
        }else cout<<"undefined operate"<<endl;
    }
}