#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

#define N 1005

vector<int> edge[N];

int n, k, size[N], num[N];

void dfs(int x)
{
	size[x] = 1;
	for(int i = 0; i < edge[x].size(); i++)
		dfs(edge[x][i]), size[x] += size[edge[x][i]];
	return ;
}
 
void work(){
	for(int i = 1; i <= n; i++)
		edge[i].clear(), num[i] = size[i] = 0;
	for(int i = 1; i <= n - 1; i++)
	{
		int p, q;
		scanf("%d%d", &p, &q);
		edge[p].push_back(q);
		num[q]++;
	}
	for(int i = 1; i <= n; i++)
		if(num[i] == 0)
		{
			dfs(i);
			break;
		}
	int ans = 0;
	for(int i = 1; i <= n; i++)
		if(size[i] == k + 1)
			ans ++;
	printf("%d\n", ans);
	return ;
}

int main(){
	while(scanf("%d %d", &n, &k) == 2)
		work();
}
