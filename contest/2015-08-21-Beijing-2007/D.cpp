#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <iostream>

const int N = 111;

using namespace std;

bool update(pair<int, int> p1, pair<int, int> &p2) {
	int a = p1.second, b = p1.first, c = p2.second, d = p2.first;
	if (b * c < a * d) {
		p2 = p1;
		return 1;
	}
	if (b * c == a * d) {
		if (a > c) {
			p2 = p1;
			return 1;
		}
	}
	return 0;
}
string text[N], result[N];
int n;
void solve(void) {
	int m, k;
	cin >> m >> k;
	for (int i = 0; i < n; ++i) {
		cin >> text[i] >> result[i];
	}
	
	map<string ,int> h[N];
	map<string, int> occur;
	map<string, int> yes;
	vector <string> vec;
	vec.clear();
	
	for (int i = 0; i < n; ++i) h[i].clear();
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j + k - 1 < (int)text[i].size(); ++j) {
			string str = text[i].substr(j, k);
			if (occur.find(str) != occur.end()) vec.push_back(str);
			if (!h[i][str]) {
				h[i][str] = 1;
				occur[str]++;
				if (result[i][0] == 'Y') {
					yes[str]++;
				}
			}
		}
	}
	
	sort(vec.begin(), vec.end());
	pair<int, int> now = make_pair(1, 1);
	string ans = "No solution";
	for (int i = 0; i < (int)vec.size(); i++) {
		if (occur[vec[i]] < m) continue;
		int p = yes[vec[i]] , q =occur[vec[i]];
		if (update(make_pair(p, q), now)) {
			ans = vec[i];
		}
	}
	
	cout << ans << endl;
}

int main(void) {
	ios::sync_with_stdio(false);
	for (; cin >> n && n; ) {
		static int test = 0;
		cout <<"Case " << ++test << ": ";
		solve();
	}
} 
