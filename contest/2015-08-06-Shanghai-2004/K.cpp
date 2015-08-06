#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cstdlib>

using namespace std;

#define INF 0x3f3f3f3f
#define N 105
int ans = INF;
int k[N],n, a[N][N];
int tmp[N][N];

void out()
{
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			tmp[i][j] = a[i][(j + k[i] - 1) % n + 1];
	int now = 0, CC = 0;
	for(int j = 1; j <= n; j++)
	{
		CC = 0;
		for(int i = 1; i <= n; i++)
			CC += tmp[i][j];
		now = max(now ,CC);
	}
	ans = min(ans, now);
	return ;
}			

void dfs(int x)
{
	if(x > n)
	{
		out();
		return ;
	}
	for(int i = 1; i <= n - 1; i++)
		k[x] = i, dfs(x + 1);
	k[x] = 0; dfs(x + 1);
	return ;
}

int main()
{
	scanf("%d",&n);
	while(n != -1)
	{
		ans = INF;
		for(int i = 1; i <= n; i++)
			for(int j = 1; j <= n; j++)
				scanf("%d", &a[i][j]);
		k[1] = 0;
		dfs(2);
		printf("%d\n", ans);
		scanf("%d",&n);
	}
	return 0;
}
