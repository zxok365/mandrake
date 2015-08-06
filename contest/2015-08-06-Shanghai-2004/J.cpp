#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<sstream>
#include<climits>
#include<vector>


using namespace std;

namespace mf{

const int N = 1500, M = 1010000;

struct EdgeList{
	int size; 
	int last[N];
	int succ[M], other[M], flow[M];
	void clear(int n)
	{
		size = 0;
		fill(last, last + n, -1);
	}
	void add(int x, int y, int c)
	{
		succ[size] = last[x];
		last[x] = size;
		other[size] = y;
		flow[size++] = c;
	}
}e;

int n, source, target;
int dist[N], curr[N];

void add(int x, int y, int c)
{
	//printf("%d %d %d\n", x, y, c);
	e.add(x, y, c);
	e.add(y, x, 0);
}

bool bfs()
{
	vector<int> queue;
	for(int i = 0; i < n; i++)
	{
		curr[i] = e.last[i];
		dist[i] = -1;
	}
	queue.push_back(target);
	dist[target] = 0;
	for(int head = 0; head < (int) queue.size(); ++head)
	{
		int x = queue[head];
		for(int i = e.last[x]; ~i; i = e.succ[i])
		{
			int y = e.other[i];
			if(e.flow[i ^ 1] && dist[y] == -1)
			{
				dist[y] = dist[x] + 1;
				queue.push_back(y);
			}
		}
	}
	return ~dist[source];
}

int dfs(int x, int ans)
{
	if(x == target) return ans;
	int delta = ans; 
	for(int &i = curr[x]; ~i; i = e.succ[i])
	{
		int y = e.other[i];
		if(e.flow[i] && dist[x] == dist[y] + 1)
		{
			int num = dfs(y, min(e.flow[i], delta));
			e.flow[i] -= num;
			e.flow[i ^ 1] += num;
			if((delta -= num) == 0)
				break;
		}
	}
	return ans - delta;
}

int solve()
{
	int ans = 0;
	for(; bfs(); ans += dfs(source, INT_MAX));
	return ans;
}

void clear()
{
	e.clear(n);
}
}

int n, m, cnt = 0;
pair<int, int> t[500004];

char buffer[11111];

bool check(int x)
{
	mf::n = n + m + 2;
	mf::clear();
	mf::source = 0;
	mf::target = n + m + 1;
	for(int i = 1; i <= m; i++)
		mf::add(0, i, x);
	for(int i = 1; i <= cnt; i++)
		mf::add(t[i].second, t[i].first + m, 1);
	for(int i = 1; i <= n; i++)
		mf::add(i + m, mf::target, 1);
	int t = mf::solve();
	return t == n;
}

int main()
{
	scanf("%d%d", &n, &m);
	while(n != 0 || m != 0)
	{
		gets(buffer);
		cnt = 0;
		for(int i = 1; i <= n; i++) {
			static char buffer[11111];
			gets(buffer);
			stringstream os(buffer);
			os >> buffer;
			for (int num; os >> num; t[++cnt] = make_pair(i, num  + 1));
		}
		int left = 1, right = n;
		int ans = 0;
		while(left <= right)
		{
			int mid = left + right >> 1;
			if(check(mid))
				ans = mid, right = mid - 1;
			else
				left = mid + 1;
		}
		printf("%d\n", ans);
		scanf("%d%d", &n, &m);
	}
	return 0;
}/*0 1 2
0 2 2
1 3 1
2 3 1
2 4 1
2 5 1
4 6 1
5 6 1
6 6 1
0
*/ 
