#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>
#include<climits>

using namespace std;

namespace MF{

const int N = 305, M = 30005;

struct Edgelist{
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

bool relabel()
{
	vector<int> queue;
	for(int i = 0; i < n; i++)
		curr[i] = e.last[i], dist[i] = -1;
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

int dfs(int x, int answer)
{
	if(x == target) return answer;
	int delta = answer;
	for(int &i = curr[x]; ~i; i = e.succ[i])
	{
		int y = e.other[i];
		if(e.flow[i] && dist[x] == dist[y] + 1)
		{
			int number = dfs(y, min(e.flow[i], delta));
			e.flow[i] -= number;
			e.flow[i ^ 1] += number;
			delta -= number;
		}
		if(delta == 0)
			break;
	}
	return answer - delta;
}

int solve()
{
	int answer = 0;
	while(relabel())
		answer += dfs(source, INT_MAX);
	return answer;
}
}

int n, a[105];
char map[105][105];
bool go[105];

bool check(int x)
{
	MF::n = 2 * n + 2;
	MF::e.clear(MF::n);
	MF::source = 0;
	MF::target = MF::n - 1;
	for(int i = 1; i <= n; i++)
		if(a[i])
			MF::add(MF::source, i, a[i]);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			if(map[i][j] == 'Y' && a[i] > 0 && a[j] > 0)
				MF::add(i, j + n, 0x3f3f3f3f);
	
	for(int i = 1; i <= n; i++)
		MF::add(i, i + n, 0x3f3f3f3f);
		
	int need = 0;
	for(int i = 1; i <= n; i++)
		if(a[i])
		{
			if(go[i])
				MF::add(i + n, MF::target, x), need += x;
			else
				MF::add(i + n, MF::target, 1), need += 1;
		}
	int t = MF::solve();
//	printf("%d %d\n", t, need);
	if(t == need)
		return true;
	else
		return false;
}

void work()
{
	int sum = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]), sum += a[i], go[i] = false;
	for(int i = 1; i <= n; i++)
		scanf("%s", map[i] + 1);
	for(int i = 1; i <= n; i++)
	{
		if(a[i]) continue;
		for(int j = 1; j <= n; j++)
			if(map[i][j] == 'Y' && a[j])
				go[j] = true;
	}
	int ans = 0, left = 1, right = sum;
	//printf("%d\n", check(4));
	while(left <= right)
	{
		int mid = left + right >> 1;
		if(check(mid))
			ans = mid, left = mid + 1;
		else
			right = mid - 1;
	}
	printf("%d\n", ans);
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
