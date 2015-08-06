#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>

#define PII pair<int, int> 
const int inf = 1 << 29;
const int MAXN = 111111;
using namespace std;

PII pre[MAXN];
int dist[MAXN];
int a[MAXN], outp[MAXN], fnd, ans = inf, h[MAXN];
void solve1(int x) {
	PII ansnow = make_pair(inf, inf);
	for (int i = 1; i <= 9; i++) {
		int ret = i % x;
		for (int j = 0; j < x; j++) h[j] = 0;
		h[ret] = 1; 
		if (ret == 0) {
			ansnow = make_pair(1, i);
			break;
		}
		int len = 1;
		for (len = 1; ret > 0; len++) {
			ret = (ret * 10 + i) % x;
			if (ret == 0) {
				ansnow = min(ansnow, make_pair(len + 1, i));
				break;
			}
			if (h[ret]) break;
			h[ret] = 1;
		}
	}
	if (ansnow.first < inf) {
		for (int i = 1; i <= ansnow.first; i++)
			putchar(ansnow.second + '0');
		puts("");
		fnd = 1;
	}
}
void bfs(int p1, int p2, int mo) {
	a[0] = p1; a[1] = p2;
	for (int i = 0; i < mo; i++) dist[i] = -1;
	for (int i = 0; i < mo; i++) pre[i] = make_pair(-1, -1);
	
	queue<int> que;
	
	if (a[0] == 0) {
		que.push(a[1] % mo);
		pre[a[1] % mo] = make_pair(-1, a[1]);
		dist[a[1] % mo] = 1;
	}
	else {
		que.push(a[0] % mo);
		que.push(a[1] % mo);
		pre[a[0] % mo] = make_pair(-1, a[0]);
		pre[a[1] % mo] = make_pair(-1, a[1]);
		dist[a[0] % mo] = dist[a[1] % mo] = 1;
	}
	
	for (;!que.empty(); que.pop()) {
		int t = que.front();
		for (int i = 0 ; i < 2; i++) {
			int tmp = (t * 10 + a[i]) % mo;
			if (pre[tmp].second == -1) {
				pre[tmp] = make_pair(t, a[i]);
				dist[tmp] = dist[t] + 1;
				que.push(tmp);
				if (tmp == 0) break; 
			}
		}
	}
	
	int t = 0;
	int cnt = 0;
	
	if (pre[t].second == -1) return;
	while (pre[t].first != -1) {
		a[++cnt] = pre[t].second;
		t = pre[t].first;
	}
	a[++cnt] = pre[t].second;
	reverse(a + 1, a + cnt + 1);
	if (cnt > ans) {
		return;
	}
	if (cnt < ans) {
		ans = cnt;
		for (int i = 1; i <= cnt; i++)
			outp[i] = a[i];
		return;
	}
	for (int i = 1; i <= cnt; i++) {
		if (outp[i] != a[i]) {
			if (outp[i] < a[i]) {
				return;
			} else {
				break;
			}
		}
	}
	
	for (int i = 1; i <= cnt; i++)
		outp[i] = a[i];
}
void solve2(int x) {
	ans = inf;
	for (int i = 0; i <= 9; i++)
		for (int j = i + 1; j <= 9; j++)
			bfs(i, j, x);
}
int n;
int main() {
	while (scanf("%d",&n) && n > 0) {
		fnd = 0;
		solve1(n);
		if (fnd) continue;
		solve2(n);
		for (int i = 1; i <= ans; i++)
			putchar(outp[i] + '0');
		puts("");
	}
	return 0;
}
