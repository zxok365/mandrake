#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>

using namespace std;

#define MOD 997
#define N 105
#define M 1005

pair<int, int> a[N];

int comb[MOD + 10][MOD + 10];
int f[N];

int times(int x, int y)
{
	return x * y % MOD;
}

pair<int, int> operator - (pair<int, int> x, pair<int, int> y)
{
	return make_pair(x.first - y.first, x.second - y.second);
}

int del(int x, int y)
{
	x -= y;
	if(x < 0) x += MOD;
	return x;
}

int get_ans(int x, int y)
{
	if(x < MOD && y < MOD) 
		return comb[x][y];
	return comb[x % MOD][y % MOD] * get_ans(x / MOD, y / MOD) % MOD;
}	

int C(int x, int y)
{
	x += y;
	if(x < 0 || y < 0) return 0;
	return get_ans(x, y);
}

void work()
{
	int h, w;
	scanf("%d%d", &h, &w);
	int n;
	scanf("%d", &n);
	int cnt = 0;
	for(int i = 1; i <= n; i++)
	{
		int x, y;
		scanf("%d %d", &x, &y);
		for(int j = max(1, x - 1); j <= min(h, x + 1); j++)
			for(int l = max(1, y - 1); l <= min(w, y + 1); l++)
				a[++cnt] = make_pair(j, l);
	}
	n = cnt;
	sort(a + 1, a + 1 + n);
//	puts("");
//	for(int i = 1; i <= n; i++)
//		printf("%d %d\n", a[i].first, a[i].second);
	int ans = C(h - 1, w - 1);
	for(int i = 1; i <= n; i++)
	{
		f[i] = C(a[i].first - 1, a[i].second - 1);
		for(int j = 1; j < i; j++)
		{
			pair<int, int> tmp = a[i] - a[j];
			f[i] = del(f[i], times(f[j], C(tmp.first, tmp.second)));
		}
		pair<int, int> tmp = make_pair(h, w) - a[i];
		ans = del(ans, times(f[i], C(tmp.first, tmp.second)));
	}
	printf("%d\n", ans);
}

int main()
{
	comb[0][0] = 1;
	for(int i = 1; i < MOD; i++)
	{
		comb[i][0] = 1;
		for(int j = 1; j <= i; j++)
			comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
	}
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++)
		printf("Case #%d: ", i), work();
	return 0;
}
