#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
const int inf = 1e9;
const int N = 1111;

using namespace std;

char s[N];
int change(char x) {
	return min(x - 'A', 'Z' - x + 1);
}
void solve() {
	scanf("%s", s + 1);
	int len = strlen(s + 1);
	int sum = 0;
	
	for (int i = 1; i <= len; i++) {
		sum += change(s[i]);
	}
	
	int ans = sum + len - 1;
	
	for (int i = 1; i <= len; i++) {
		int tmp = sum;
		int fnd = 0;
		for (int j = i + 1; j<= len; j++)
			if (s[j] != 'A') {
				fnd = j;
				break;
			}
		if (fnd) {
			tmp += (i - 1) * 2 + len - fnd + 1;
		}
		else tmp += i - 1;
		ans = min(tmp, ans);
	}
	
	vector<int> pos;
	for (int i = 1; i <= len; i++) {
		if (s[i] != 'A') pos.push_back(i);
	}
	
	if (pos.size() >= 2) 
	for (int i = 0; i < (int)pos.size() - 1; i++) {
		int tmp = sum;
		tmp += (len - pos[i + 1] + 1) * 2 + pos[i] - 1;
		ans = min(tmp, ans);
	}
	
	printf("%d\n", ans);
}
int main() {
	int T;
	scanf("%d", &T);
	for (int tt = 1; tt <= T; tt++) {
		solve();
	}
	return 0;
}
