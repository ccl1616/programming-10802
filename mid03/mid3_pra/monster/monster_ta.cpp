// 12306 this is ta code
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

/*
    this is ta code !!
    main idea: optimized BFS; using vis[lv][hp][mhp] to record visited states
*/

struct Status {
	int lv, hp, mhp;
	int dist;
	Status(int lv, int hp, int mhp, int dist = 0): lv(lv), hp(hp), mhp(mhp), dist(dist) {}
};

bool vis[20][310][410];

int main() {
	int lv, hp, mhp, mdmg;
	int dmg[20], hl[20]; // L <= 15
	cin >> lv >> hp >> mhp >> mdmg;
	for (int i = 1; i <= lv; i++)
		cin >> dmg[i] >> hl[i];

	queue<Status> q;
	q.push(Status(1, hp, mhp)); //push the initial state into q
	while (!q.empty()) {
		Status s = q.front();
        // check if monster die or not
		if (!s.mhp)
			break;
		q.pop();

		// level up
		if (s.lv < lv && s.hp - mdmg > 0) {
			Status t(s.lv + 1, s.hp - mdmg, s.mhp, s.dist + 1);
			if (!vis[t.lv][t.hp][t.mhp]) {
				vis[t.lv][t.hp][t.mhp] = true;
				q.push(t);
			}
		}

		// attack
		if (s.mhp - dmg[s.lv] <= 0 || s.hp - mdmg > 0) {
			Status t(s.lv, s.hp - mdmg, max(0, s.mhp - dmg[s.lv]), s.dist + 1);
			if (!vis[t.lv][t.hp][t.mhp]) {
				vis[t.lv][t.hp][t.mhp] = true;
				q.push(t);
			}
		}

		// heal
		// 前面?? 後面那句表示 heal之後在被攻擊 不會損失
		if (hp - mdmg > 0 && hl[s.lv] > mdmg) {
			// min(hp, s.hp + hl[s.lv]), cause your hp cannot > maxhp
			Status t(s.lv, min(hp, s.hp + hl[s.lv]) - mdmg, s.mhp, s.dist + 1);
			if (!vis[t.lv][t.hp][t.mhp]) {
				vis[t.lv][t.hp][t.mhp] = true;
				q.push(t);
			}
		}
	}
	if (q.empty())
		cout << -1 << endl;
	else
		cout << q.front().dist << endl;
	return 0;
}