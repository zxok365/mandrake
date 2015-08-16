#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>

using namespace std;

#define N 20005

vector<int> ans;

int f[N], fa[N], oldfa[N], num[N];

char c[N];

struct node
{
	int x, y;
	int type;
}ask[N];

int find(int x)
{
	if(x == f[x]) return f[x];
	f[x] = find(f[x]);
	return f[x];
}

void merge(int x, int y)
{
	x = find(x), y = find(y);
	if(x == y) return ;
	f[y] = x;
	return ;
}


void work()
{
	int n, k;
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)
		f[i] = i, num[i] = 0;
	ans.clear();
	for(int i = 1; i <= n; i++)
		scanf("%d", &fa[i]), oldfa[i] = fa[i];
	for(int i = 1; i <= k;i++)
	{
		scanf("%s", c + 1);
		if(c[1] == 'Q')
			ask[i].type = 1, scanf("%d %d", &ask[i].x, &ask[i].y);
		if(c[1] == 'C')
			ask[i].type = 2, scanf("%d", &ask[i].x),num[ask[i].x]++, fa[ask[i].x] = 0;
	}
	for(int i = 1; i <= n; i++)
		if(fa[i])
			merge(i, fa[i]);
	for(int i = k; i >= 1; i--)
	{
		if(ask[i].type == 1)
		{
			ask[i].x = find(ask[i].x);
			ask[i].y = find(ask[i].y);
			if(ask[i].x - ask[i].y == 0)
				ans.push_back(1);
			else
				ans.push_back(0);
		}
		else
		{
			num[ask[i].x] --;
			if(!num[ask[i].x] && oldfa[ask[i].x])
				merge(oldfa[ask[i].x], ask[i].x);
		}
	}
	reverse(ans.begin(), ans.end());
	for(int i = 0; i < ans.size(); i++)
		if(ans[i])
			puts("YES");
		else
			puts("NO");
	return ;
}	

int main()
{
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++)
		printf("Case #%d:\n", i),work();
	return 0;
}

