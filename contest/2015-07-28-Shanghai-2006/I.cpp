#include<cstdio>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>

using namespace std;

#define MOD 10000

int main()
{
	int p, k;
	scanf("%d %d", &p, &k);
	int test=0;
	while(p!=0 || k != 0)
	{
		int CC=1;
		while(k)
		{
			CC=(CC * (k % p + 1))%MOD;
			k /= p;
		}
		printf("Case %d: %04d\n", ++test, CC);
		scanf("%d %d", &p, &k);
	}
	return 0;
}
