#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<queue>
#include<map>

using namespace std;

const int N = 100005;

vector<int> adj[N];

map<unsigned long long, int> Q;

int fa[N], ans[N];
unsigned long long mi[N], hash[N];
pair<unsigned long long, int> go[N];

void bfs(int x)
{
	static int team[N];
	int head = 0, tail = 1;
	team[1] = 1;
	while(head <= tail)
	{
		int u = team[++head];
		for(int i = 0; i < adj[u].size(); i++)
			team[++tail] = adj[u][i];
	}
	vector<pair<unsigned long long, int> > value;
	for(int now = tail; now >= 1; now--)
	{
		int u = team[now];
		go[u] = make_pair(13, 1); 
		value.clear();
		for(int i = 0; i < adj[u].size(); i++)
			value.push_back(go[adj[u][i]]);
		std::sort(value.begin(), value.end());
		for (int i = 0; i < (int)value.size(); ++i) {
			go[u].first = go[u].first * mi[value[i].second] + value[i].first;
			go[u].second += value[i].second;
		}
		go[u].first = go[u].first * mi[1] + 17;
		hash[u] = go[u].first;
		go[u].second++;
	}
	return ;
}

int main()
{
	int n;
	scanf("%d", &n);
	for(int i = 2; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		adj[x].push_back(i);
	}
	mi[0] = 1;
	for(int i = 1; i <= n; i++)
		mi[i] = mi[i - 1] * 31;
	bfs(1);
	int cnt = 0;
	for(int i = 1; i <= n; i++)
	{
		if(Q.count(hash[i]))
			ans[i] = Q[hash[i]];
		else
		{
			Q[hash[i]] = ++cnt;
			ans[i] = cnt;
		}
	}
	for(int i = 1; i <= n; i++)
		printf("%d%s", ans[i], (i == n) ? "\n" : " ");
	return 0;
}
