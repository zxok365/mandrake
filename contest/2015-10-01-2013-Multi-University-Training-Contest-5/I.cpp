#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>

using namespace std;

const int N = 100005;
const int MOD = 1000000007;

int ans[N];

void dfs(int x) {
	if(ans[x] != -1) return ;
	ans[x] = 0;
	int flag = -1;
	for(int k = 1; k * (3 * k - 1) / 2 <= x; k++) {
		flag *= -1;
		dfs(x - k * (3 * k - 1) / 2);
		ans[x] = (1LL * ans[x] + flag * ans[x - k * (3 * k - 1) / 2] + MOD) % MOD;
	}
	flag = -1;
	for(int k = 1; k * (3 * k + 1) / 2 <= x; k++) {
		flag *= -1;
		dfs(x - k * (3 * k + 1) / 2);
		ans[x] = (1LL * ans[x] + flag * ans[x - k * (3 * k + 1) / 2] + MOD) % MOD;
	}
	return ;
}

void work() {
	int n;
	scanf("%d", &n);
	dfs(n);
	printf("%d\n", ans[n]);
	return ;
}

int main() {
	int T;
	scanf("%d", &T);
	ans[0] = 1;
	for(int i = 1; i <= 100000; i++)
		ans[i] = -1;
	for(int i = 1; i <= T; i++)
		work();
	return 0;
}
