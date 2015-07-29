#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

typedef long long LL;

#define N 20

int p[N], a[N];
int pi_1[N], pin[N], S_1[N], Sn[N], n, k[N];
int digit[N], CC;
#define MOD 1000000007

int times(int x, int y)
{
	return ((LL)x * (LL)y)%MOD;
}

int pow(int x, int y)
{
	int ans = 1;
	for(;y;y >>= 1, x = times(x, x))
		if(y & 1)
			ans = times(ans, x);
	return ans;
}

void out()
{
	int suml = 1, sumr = 1, timesl = 1, timesr = 1;
	for(int i = 1; i <= n; i++)
	{
		if(k[i])
			suml = times(suml, pin[i]), sumr = times(sumr, Sn[i]), timesr = times(timesr, (a[i] + 1) % MOD);
		else
			suml = times(suml, S_1[i]), sumr = times(sumr, pin[i]), timesl = times(timesl, a[i]);
	//	printf("%d %d %d %d\n",suml ,sumr, timesl ,timesr);
	
	}
	CC=(CC + (times(suml, timesr) + times(sumr, timesl)) % MOD) % MOD;
}

void dfs(int x)
{
	if(x > n) { out(); return ;}
	k[x] = 1; dfs(x+1);
	k[x] = 0; dfs(x+1);
	return ;
}

void work()
{
	CC = 0;
	scanf("%d",&n);
	for(int i = 1; i <= n; i++)
		scanf("%d%d", &p[i], &a[i]),pi_1[i] = pin[i] = Sn[i] = S_1[i] = 1;
	int Max = 1;
	for(int i = 1; i <= n; i++)
	{
		for(int j = 1; j <= a[i]; j++)
		{
			if(j != a[i])
				pi_1[i] = times(pi_1[i], p[i]), S_1[i] = (S_1[i] + pi_1[i]) % MOD;
			pin[i] = times(pin[i], p[i]);
			Sn[i] = (Sn[i] + pin[i]) % MOD;
		}
		Max = times(Max, pin[i]);
	}
	dfs(1);
//	printf("%d\n", CC);
	CC = (CC + times(2, Max)) % MOD;
	CC = times(CC, pow(2, MOD-2));
	printf("%d\n", CC);
}

int main()
{
	int test;
	scanf("%d", &test);
	for(int i = 1; i <= test; i++)
	{
		printf("Case %d: ",i);
		work();
	}
	return 0;
}
