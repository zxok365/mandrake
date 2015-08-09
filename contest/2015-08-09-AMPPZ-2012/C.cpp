#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>

using namespace std;

#define N 1000005

int f[N][2];
int num[N][2], a[N];

int main()
{
	int n, k;
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= k; i++)
	{
		int st = i;
		while(st <= n)
			num[i][a[st] & 1]++, st += k;
	}
	for(int i = 0; i <= n; i++)
		f[i][0] = f[i][1] = 0x3f3f3f3f;
	f[0][0] = 0;
	for(int i = 1; i <= k; i++)
	{
		for(int j = 0; j <= 1; j++)
		{
			f[i][j] = min(f[i][j], f[i - 1][j ^ 1] + num[i][0]);
			f[i][j] = min(f[i][j], f[i - 1][j] + num[i][1]);
		}
	}
	printf("%d\n", f[k][0]);
	return 0;
}				
