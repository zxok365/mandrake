// orz LZJ orz LZJ orz LZJ orz LZJ orz LZJ orz LZJ orz LZJ orz LZJ orz LZJ orz LZJ 
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cstdlib>
#include<iostream>

using namespace std;

#define N 200005

typedef long long LL;

LL f[N], a[N], tmp[N];
LL jp0[N], jp1[N], get[N];

int main()
{
	LL n;
	scanf("%I64d", &n);
	for(LL i = 1; i <= n; i++)
		scanf("%I64d", &a[i]);
	sort(a + 1, a + 1 + n);
	for(LL i = 1; i <= n; i++)
		tmp[i] = a[i];
	f[0] = 1;
	for(LL i = 0; i <= 100; i++)
	{		
		for(LL j = 1; j <= n ;j++)
			if(a[j] != 0)
				goto syf;
		break;
		syf:;
		for(LL j = 0; j <= n + 1; j++)
			get[j] = 0;
		LL sum0 = 0, sum1 = 0;
		for(LL j = 1; j <= n; j++)
			if(a[j] & 1)
				 jp1[++sum1] = a[j];
			else
				 jp0[++sum0] = a[j];
		LL tw1 = 0 , tw0 = 0;
		for(LL j = 1; j <= n + 1; j++)
		{
			LL res = (sum1 - tw1) + tw0;
			if(res % 2 == 0)
				get[tw0] += f[j - 1];
			if((n - res) % 2 == 0)
				get[sum0 + tw1] += f[j - 1];
			if(a[j] & 1)
				tw1++;
			else
			 	tw0++;
			if(a[j] == 0)
				break;
		}
		LL cnt = 0;
		for(LL j = 1; j <= sum0; j++)
			a[++cnt] = jp0[j];
		for(LL j = 1; j <= sum1; j++)
			a[++cnt] = jp1[j];
		for(LL j = 1; j <= cnt; j++)
			a[j] >>= 1;
		for(LL j = 0; j <= n + 1; j++)
			f[j] = get[j];
	}
		
	LL flag = 0;
	for(LL i = 2; i <= n; i++)
		flag ^= (tmp[i] - tmp[1]);
	if(flag == 0)
		f[0]--;
	
	printf("%I64d\n",f[0]);
	return 0;
}
