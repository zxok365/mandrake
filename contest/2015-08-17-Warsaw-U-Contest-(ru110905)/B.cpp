#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int N = 505;

int n, m, r, t, k, tot = 0, start[N], visit[N * N], gxx = 0;
int match[N];

vector<pair<int, pair<int, int> > > ans;

struct node
{
	int x, y, next;
}road[N * N];


void build(int x, int y)
{
	road[++tot].x = x, road[tot].y = y; road[tot].next = start[x], start[x] = tot;
	return ;
}

int team[N * N];

int get(int x)
{
	return (x - 1) % n + 1;
}

bool dfs(int x)
{
	for(int i = start[get(x)]; i; i = road[i].next)
	{
		int to = road[i].y;
		if(visit[to] != gxx)
		{
			visit[to] = gxx;
			if(match[to] == -1 || dfs(match[to]))
			{
				match[to] = x;
				return true;
			}
		}
	}
	return false;
}

int get_num(int x)
{
	return (x - 1) / n;
}

int main()
{
	scanf("%d%d%d%d%d", &n, &m, &r, &t, &k);
	for(int i = 1; i <= k; i++)
	{
		int p, q;
		scanf("%d%d", &p, &q);
		build(p, q);
	}
	for(int i = 1; i <= m; i++)
		match[i] = -1;
	int head = 0, tail = 0;
	for(int i = 1; i <= n; i++)
		if(r <= t)
			team[++tail] = i;
	int sum = 0;
	while(head <= tail)
	{
		int u = team[++head];
		gxx++;
		bool tmp = dfs(u);
		if(!tmp) continue;;
		sum++;
		int num = get_num(u) + 1;
		if((num + 1) * r > t) continue;
		team[++tail] = u + n;
	}
	int ans1 = sum, ans2 = 0;
	for(int i = 1; i <= m; i++)
		if(match[i] != -1)
		{
			ans2 += (get_num(match[i]) + 1) * r;
			ans.push_back(make_pair(get(match[i]), make_pair(i, get_num(match[i]) * r)));
		}
	printf("%d %d\n", ans1, ans2);
	for(int i = 0; i < ans.size(); i++)
		printf("%d %d %d\n", ans[i].first, ans[i].second.first, ans[i].second.second);
	return 0;
}
