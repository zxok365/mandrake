#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cstdlib>

using namespace std;

#define M (1 << 13)
#define N 15

typedef long long LL;

int n, m, v[N];
pair<int, LL> f[M + 5][N][N];
bool map[N][N];

pair<int, LL> add(pair<int, LL> x, pair<int, LL> y)
{
	if(y.first < x.first) return x;
	if(y.first > x.first) return y;
	return make_pair(x.first, x.second + y.second);
}

bool check(int x, int y, int z)
{
	if(x == 0 || y == 0 || z == 0) return false;
	if(map[x][y] && map[y][z] && map[x][z]) 
		return true;
	else
		return false;
}

bool check(int x, int y)
{
	if(x == 0 || y == 0) return false;
	if(map[x][y]) return true;
	else
		return false;
}	

void work()
{
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		scanf("%d", &v[i]);	
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			map[i][j] = false;
	for(int i = 1; i <= m; i++)
	{
		int p, q;
		scanf("%d%d", &p, &q);
		map[p][q] = map[q][p] = true;
	}
	int Max = 1 << n;
	for(int i = 0; i < Max; i++)
		for(int j = 0; j <= n ;j++)
			for(int k = 0; k <= n; k++)
				f[i][j][k] = make_pair(-1, 0);
	f[0][0][0] = make_pair(0, 1);
	for(int i = 1; i <= n; i++)
		map[0][i] = 1;
	for(int i = 0; i < Max; i++)
		for(int nx1 = 0; nx1 <= n; nx1++)
			for(int nx2 = 0; nx2 <= n; nx2++)
			{
				if(f[i][nx1][nx2].first == -1) continue;
				for(int to = 1; to <= n; to ++)
				{
					if(map[nx2][to] == 0) continue;
					if(((1 << (to - 1)) ^ i) <= i)  continue;
					pair<int, LL>  tmp = f[i][nx1][nx2];
					if(check(nx1, nx2, to))
						tmp.first += v[nx1] * v[nx2] * v[to];
					if(check(nx2, to))
						tmp.first += v[nx2] * v[to];
					tmp.first += v[to];
					f[i ^ (1 << (to - 1))][nx2][to] = add(f[i ^ (1 << (to - 1))][nx2][to], tmp);
				}
			}
	pair<int, LL> ans = make_pair(0, 0);
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= n; j++)
			ans = add(ans, f[Max - 1][i][j]);
	if(n == 1) ans.second ++;
	ans.second /= 2;
	printf("%d ", ans.first);
	cout << ans.second << endl;
	return ;
}

int main()
{
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++)
		work();
	return 0;
}
