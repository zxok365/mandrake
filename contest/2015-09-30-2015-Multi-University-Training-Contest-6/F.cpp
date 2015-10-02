#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 100005;

typedef long long LL;

int n, a[N];
int nxt[44][N];
LL S[N];
LL ans = 0;

void work() {
	ans = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++)
		S[i] = S[i - 1] + a[i];
	LL up = 0, down = 1;
	int k = 0;
	while(1) {
		if(up > S[n]) break;
		k++;
		int now = 1;
		for(int i = 1; i <= n; i++) { 
			now = max(i, now);
			while(now <= n && S[now] - S[i - 1] <= down) now++;
			nxt[k][i] = now;
		}
		up = down + 1; down = up * 2 - 1;
	}
	for(int i = 1; i <= n; i++)
		nxt[0][i] = i;
	for(int i = 1; i <= k; i++) {
		for(int j = 1; j <= n; j++) {
			ans += 1LL * (1LL * (nxt[i][j] - nxt[i - 1][j]) * j + (1LL * (nxt[i][j] - 1 + nxt[i - 1][j]) * (nxt[i][j] - nxt[i - 1][j])) / 2) * i;
		}
	}
	printf("%I64d\n", ans);
	return ;
}

int main() {
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++)
		work();
	return 0;
}
