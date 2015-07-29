#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>

using namespace std;

#define N 222
#define M 222222

int	map[N][N];
int r[N][N], c[N][N];
int n, m, cntc, cntr;

vector<int> adj[M];
int matchx[M],matchy[M];
int visit[M],times = 0;

void add(int x, int y)
{
	adj[x].push_back(y);
	return ;
}

bool dfs(int x)
{
	for(int i = 0; i < (int) adj[x].size(); i++)
	{
		int y = adj[x][i];
		if(visit[y] != times)
		{
			visit[y] = times;
			if(!matchy[y] || dfs(matchy[y]))
			{
				matchy[y]=x;
				return true;
			}
		}
	}
	return false;
}

void work()
{
	cntc = cntr = 0;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			map[i][j] = 0;
	int Q1,Q2;
	scanf("%d", &Q1);
	for(int i = 1; i <= Q1; i++)
	{
		int p, q;
		scanf("%d%d", &p, &q);
		map[p][q] = 2;
	}
	scanf("%d", &Q2);
	for(int i = 1; i <= Q2; i++)
	{
		int p, q;
		scanf("%d%d", &p, &q);
		map[p][q] = 1;
	}
	cntc = cntr = 0;
	for(int i = 1; i <= n; i++)
	{
		cntc++;
		for(int j = 1; j <= m; j++)
			if(map[i][j] == 1)
				cntc++;
			else
				c[i][j] = cntc;
	}
	for(int i = 1; i <= m; i++)
	{
		cntr++;
		for(int j = 1; j <= n; j++)
			if(map[j][i] == 1)
				cntr++;
			else
				r[j][i] = cntr;
	}		
	for(int i = 1; i <= cntc; i++) adj[i].clear();
	for(int i = 1; i <= max(cntc, cntr); i++)
		matchy[i] = matchx[i] = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			if(map[i][j] == 2)
				add(c[i][j], r[i][j]);
	int ans = 0;
	for(int i = 1; i <= cntc; i++)
	{
		times++;
		ans += dfs(i);
	}
	printf("%d\n",ans);
	return ;
}

int main()
{
	int test=0;
	scanf("%d", &test);
	for(int i = 1; i <= test; i++)
		work();
	return 0;
}

/*1 1 1 1 1 1 
2 0 3 0 4 4 
5 5 5 5 5 5 
6 0 7 0 8 8 
1 2 5 6 9 10 
1 0 5 0 9 10 
1 3 5 7 9 10 
1 0 5 0 9 10 
*/
