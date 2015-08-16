#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>

using namespace std;

const int N = 505;
const int MOD = 1000000007;
int jc[N], comb[505][505];

typedef long long LL;

int times(int x, int y)
{
	return 1LL * x * y % MOD;
}

int A(int x, int y)
{
	if(x < 0 || y < 0) return 0;
	return times(comb[x][y], jc[y]);
}

int C(int x, int y)
{
	if(x < y) return 0;
	if(x < 0 || y < 0) return 0;
	return comb[x][y];
}

void work()
{
	int n, k, p;
	scanf("%d%d%d", &n, &k, &p);
	p = n + 1 - p;
	int CC = 0;
	for(int i = 0; i <= k - 1; i++)
	{
		int ressmall = p - 1 - i;
		int resbig = n - p - (k - 1 - i);
		if(ressmall < 0 || resbig < 0) continue;
		if(ressmall == 0)
		{
			CC = (CC + times(times(C(p - 1, i), C(n - p, k - i - 1)), jc[k - 1])) % MOD;
			continue;
		}
		for(int now = k + 1; now <= n; now++)
			for(int num = 1; num <= min(ressmall, now - k); num++)
			{
			//	printf("C(%d, %d) * C(%d, %d) %d\n", p - 1, i, n - p, k - i - 1, k - 1);
				int part1 = times(times(C(p - 1, i), C(n - p, k - i - 1)), jc[k - 1]); 
			//	printf("%d\n", part1);
				int part2 = times(C(resbig, (now - k - num)), C(ressmall, num));
				int part3 = jc[n - now];
				CC = (CC + times(times(part1, part2), part3)) % MOD;
			}
	}
	printf("%d\n", CC);		 	
}
	
int main()
{
	int T;
	comb[0][0] = 1;
	for(int i = 1; i <= 500; i++)
	{
		comb[i][0] = 1;
		for(int j = 1; j <= i; j++)
			comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
	}
	jc[0] = 1;
	for(int i = 1; i <= 500; i++)
		jc[i] = times(jc[i - 1], i);
	scanf("%d", &T);
	for(int i = 1; i <= T; i++)
		printf("Case #%d: ",i), work();
	return 0;
}
	
