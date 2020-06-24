// social distance 
#include <iostream>
#include <set>
#include <vector>
#include <string>
using namespace std;

struct Seg{
    int left,right;
    Seg(int l, int r):left(l),right(r){}
};

struct mycomp{
    bool operator() (const Seg& lhs, const Seg& rhs) const
    {
        int ll = (lhs.right-lhs.left)/2;
        int rl = (rhs.right-rhs.left)/2;
        if(ll != rl)
            return ll > rl; // bigger length is better
        else return lhs.left < rhs.left; // smaller seat number is better
    }
};

int main()
{
    // set to store seg
    // array to store student pos
    // set to store now occupied seats

    // need to redefine compare function of set
    set<Seg,mycomp> ss;
    vector<int> student;
    set<int> seat;

    // n seats, m students, 2m op
    // s for strict min distance
    // dis for distance
    int n, m, s, dis;
    cin >> n >> m >> s;

    // initialize
    student.resize(m+1,-1);
    dis = n+1;
    ss.insert( Seg(0,n+1) ); //!!
    seat.insert(0);
    seat.insert(n+1);

    for(int i = 1; i <= 2*m; i ++){
        string temp;
        int id;
        cin >> temp >> id;
        if( temp == "i"){
            // find best seg, which is in the begin of set
            // find best pos within given seg
            
            auto cur = ss.begin();
            int left = cur->left;
            int right = cur->right;
            int pos = (left+right)/2;

            //update dis !!
            if(left != 0)
                dis = min(pos-left,dis);
            if(right != n+1)
                dis = min(right-pos,dis);

            // spilt seg
            ss.insert(Seg(left,pos));
            ss.insert(Seg(pos,right));
            ss.erase(cur);
            
            // put student into that pos
            student[id] = pos;
            seat.insert(pos);
        }
        else {
            // find his seat
            // merge seat
            
            int pos = student[id];
            auto cur = seat.find(pos);
            auto l = cur;
            auto k = cur;
            int left_seat = *(--l);
            int right_seat = *(++k);
            ss.erase( Seg(left_seat,pos));
            ss.erase( Seg(pos,right_seat));
            ss.insert( Seg(left_seat,right_seat));
            
            // record student&seat
            student[id] = -1;
            seat.erase(pos);
        }
    }
    if(dis >= s) cout << "YES\n";
    else cout << "NO\n";

    if(dis == n+1) cout << "INF\n";
    else cout << dis << endl;

    return 0;
}