#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int num[4], now[4];

char c[205];

int main()
{
	int n, a, b;
	scanf("%d%d%d", &n, &a, &b);
	if(a + b > n)
	{
		puts("-1");
		return 0;
	}
	num[0] = a, num[1] = b, num[2] = n - a - b;
	scanf("%s", c + 1);
	int len = strlen(c + 1),ans = 0;
	for(int i = 1; i <= len ;i++)
		now[c[i] - '0'] ++;
	for(int i = 1; i <= len; i++)
	{
		if(num[c[i]-'0'] < now[c[i] - '0'])
		{
			int id=0;
			for(int j = 0; j <= 2; j++)
				if(num[j] > now[j])
					id = j;
			ans ++;
			now[c[i] - '0']--; now[id] ++;
			c[i] = id + '0';
		}
	}
	printf("%d\n",ans);
	puts(c+1);
	return 0;
}
