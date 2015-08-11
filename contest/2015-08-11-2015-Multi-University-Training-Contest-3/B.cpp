#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

#define N 1000005

int num[N];
bool U_prime[N];
int f[N][9], now[9];
int mygcd[10][10];
int main()
{
	num[1] = 0;
	for(int i = 2; i <= N - 5; i++)
	{
		if(!U_prime[i]) num[i] = 1;
		else continue;
		for(int j = i + i; j <= N - 5; j += i)
			num[j]++, U_prime[j] = true;
	}
	for(int i = 2; i <= N - 5; i++)
	{
		for(int j = 1; j <= 7; j++)
			f[i][j] = f[i - 1][j];
		f[i][num[i]]++;
	}
	for(int i = 1; i <= 8; i++)
		for(int j = 1; j <= 8; j++)
			mygcd[i][j] = __gcd(i, j);
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		int ans = 0;
		for(int j = 1; j <= 7; j++)
			now[j] = f[r][j] - f[l - 1][j];
		for(int j = 1; j <= 7; j++)
			if(now[j] >= 2)
				ans = max(ans, j);
		for(int j = 1; j <= 7; j++)
			for(int k = j + 1; k <= 7; k++)
				if(now[j] && now[k])
					ans = max(ans, mygcd[j][k]);
		printf("%d\n", ans);
	} 
	return 0;
}
