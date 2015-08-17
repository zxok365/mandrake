#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1000005;

pair<int, int> t[N];

int n, Max[55];

int main()
{
	scanf("%d", &n);
	int cnt = 0;
	for(int i = 1; i <= n; i++)
	{
		int num;
		scanf("%d", &num);
		for(int j = 1; j <= num; j++)
		{
			int p;
			scanf("%d", &p);
			t[++cnt] = make_pair(p, i);
		}
	}
	sort(t + 1, t + 1 + cnt);
	for(int i = 1; i <= n; i++)
		Max[i] = -0x3f3f3f3f;
	for(int i = 1; i <= cnt; i++)
	{
		int c = t[i].first;
		int tmp = Max[t[i].second];
		Max[t[i].second] = -0x3f3f3f3f;
		int a = -0x3f3f3f3f, ida, b = -0x3f3f3f3f, idb; 
		for(int j = 1; j <= n; j++)
		{
			if(Max[j] >= a)
			{
				b = a, idb = ida;
				a = Max[j]; ida = j;
			}
			else
				if(Max[j] >= b)
					b = Max[j], idb = j;
		}
		if(a + b > c)
		{
			printf("%d %d %d %d %d %d\n", ida, a, idb, b, t[i].second, c);	
			return 0;
		}
		Max[t[i].second] = max(tmp, t[i].first);
	}
	puts("NIE");
	return 0;
}			 
