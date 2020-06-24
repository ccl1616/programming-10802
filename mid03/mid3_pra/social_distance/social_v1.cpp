// 12817
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <climits>
using namespace std;
/*
    Note0: struct Seg, and use it
    Note1: student.resize(m+1,-1); allocating array size & content
    Note2: mycomp
    Note3: need  vector<int> student; & set<int> taken_seat; no do the record
    Note4: 43~45 initialize
    Note5: 60~63 檢查左右兩邊距離, 左右兩邊都要compare with dis and update
    Note6: 80,81 to refer to its left&right neighbor
*/

struct Seg{
    int left,right;
    Seg(int l, int r):left(l),right(r){} //this is a constructor!!
};

struct mycomp{
    bool operator() (const Seg &lhs, const Seg &rhs)const{
        int _llen = (lhs.right-lhs.left)/2;
        int _rlen = (rhs.right-rhs.left)/2;
        if(_llen != _rlen)
            return _llen > _rlen; //longer is better
        else return lhs.left < rhs.left; // smaller index is better
    }
};

int main()
{
    int n,m,s; // n seats, m students, s for distance
    int dis; // record now min dis
    set<Seg,mycomp> ss; // ss for seg_set
    vector<int> student; //student[id] = seat_pos, record the student pos
    set<int> taken_seat;
    cin >> n >> m >> s;
    
    student.resize(m+1,-1); //the array need to be resized before using
    dis = n+1; //set distance to n+1, which is not possible, which represent INF
    ss.insert( Seg(0,n+1));
    taken_seat.insert(0);
    taken_seat.insert(n+1);

    string cmd;
    int id;
    for(int i = 1; i <= 2*m; i ++){
        cin >> cmd >> id;
        if(cmd == "i"){
            // find the best seg in ss
            auto k = ss.begin();
            int left = k->left;
            int right = k->right;

            // find the best pos in this seg
            int pos = (left+right)/2;

            // 檢查左右兩邊距離 !!
            if(left != 0)
                dis = min( (pos-left), dis);
            if(right != n+1)
                dis = min( (right-pos),dis);

            // update ss
            ss.insert( Seg(left,pos));
            ss.insert( Seg(pos,right));
            ss.erase(k);

            // record student
            student[id] = pos;
            // record seat
            taken_seat.insert(pos);
        }
        else if(cmd == "o"){
            // update ss
            int pos = student[id];
            auto k = taken_seat.find(pos);
            auto l = k, r = k;
            int left = *(--l); //!! find it's left and right elements in a set
            int right = *(++r);
            ss.erase(Seg(left,pos));
            ss.erase(Seg(pos,right));
            ss.insert(Seg(left,right));

            // record student&seat
            student[id] = -1;
            taken_seat.erase(pos);
        }
    }

    if(dis >= s) cout << "YES\n";
    else cout << "NO\n";

    if(dis == n+1) cout << "INF\n";
    else cout << dis << endl;
    return 0;
}


