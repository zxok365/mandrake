#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cmath>
#include<vector>

using namespace std;

#define M 10005
#define N 105

vector<int> adj[N];
vector<int> ans;

struct node
{
	int x, y, next;
	bool flag;
}road[M];

int tot = 0, bel[N], dfn[N], low[N], block = 0;
int num_ro[M], num_po[N], sum1 = 0, sum2 = 0, yes_sum = 0, start[N], id;

bool used[N];

void build(int x, int y)
{
	tot++;
	road[tot].x = x, road[tot].y = y, road[tot].next = start[x], start[x] = tot;
	road[tot].flag = false;
}

void Tarjin(int x, int fa)
{
	dfn[x] = low[x] = ++id;
	for(int i = start[x]; i; i = road[i].next)
		if((i ^ 1) != fa)
		{
			int q = road[i].y;
			if(!dfn[q])
				Tarjin(q, i);
			low[x] = min(low[x], low[q]);
			if(dfn[x] < low[q])
				road[i].flag = road[i ^ 1].flag = true;
		}
}

void dfs(int x)
{
	used[x] = true;
	bel[x] = block;num_po[block]++;
	for(int i = start[x]; i; i = road[i].next)
	{
		if(road[i].flag) continue;
		int to = road[i].y;
		if(used[to]) continue;
		dfs(to);
	}
	return ;
}

void get(int x)
{
	ans.push_back(x);
	used[x] = true;
	yes_sum += (num_ro[x] == (num_po[x] * (num_po[x] - 1) / 2));
	if(adj[x].size() == 1) sum1++;
	if(adj[x].size() == 2) sum2++;
	for(int i = 0; i < adj[x].size(); i++)
	{
		int to = adj[x][i];
		if(used[to]) continue;
		get(to);
	}
	return ;
}

void work()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		start[i] = dfn[i] = used[i] = block = num_ro[i] = num_po[i] = 0;
	tot = 1; id = 0;
	for(int i = 1; i <= m; i++)
	{
		int p, q;
		scanf("%d%d", &p, &q);
		build(p, q);build(q, p);
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i])
			Tarjin(i, 0);
	for(int i = 1; i <= n; i++)
		if(!used[i])
			block++, dfs(i);
	for(int i = 1; i <= block; i++)
		adj[i].clear();
	for(int i = 2; i <= tot; i += 2)
	{
		int x = bel[road[i].x], y = bel[road[i].y];
		if(x == y)
			num_ro[x]++;
		else
			adj[x].push_back(y),
			adj[y].push_back(x);
	}
	for(int i = 1; i <= block; i++)
		used[i] = false;
	int CC = 0;
	for(int i = 1; i <= block; i++)
	{
		if(used[i]) continue;
		ans.clear(); 
		sum1 = sum2 = yes_sum = 0;
		get(i);
		if(ans.size() == 1 || yes_sum != ans.size() || ans.size() >= 5) continue;
		if(sum1 + sum2 != ans.size()) continue;
		if(sum1 < 2) continue;
		if(ans.size() == 2) 
		{
			int gx = 1;
			if(num_po[ans[0]] != num_po[ans[1]])
				gx = 0;
			CC += gx;
		}
		if(ans.size() == 3) continue;
		if(ans.size() == 4)
		{
			int gx = 1;
			for(int i = 0; i < ans.size(); i++)
				if(num_po[ans[i]] > 1)
					gx = 0;
			CC += gx;
		}
	}
	printf("%d\n", CC);		
}

int main()
{
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++)
		printf("Case #%d: ", i), work();
	return 0;
}
