#pragma comment(linker,"/STACK:102400000,102400000")

#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

#define N 50005
#define INF 0x3f3f3f3f

int n;
int L[N], R[N], tmp[N], used[N];
int cnt = 0, gxx = 0;
pair<int, int> tree[N], f[N];
vector<int> ans_seq;

struct Node
{
	int key, id, type;
	Node() {}
	Node(int key, int id, int type) : key(key) , id(id), type(type){}
	friend bool operator < (const Node &x, const Node &y)
	{
		if(x.key == y.key)
			return x.type < y.type;
		else
			return x.key > y.key;
	}
		
}seq[N];

int lowbit(int x)
{
	return x & (-x);
}

void add(int x, pair<int, int> y)
{
	while(x <= n)
	{
		if(used[x] != gxx)
			tree[x] = make_pair(-1, 0), used[x] = gxx;
		tree[x] = max(tree[x], y);
		x += lowbit(x);
	}
	return ;
}

pair<int, int> Query(int x)
{
	pair<int, int> ans = make_pair(-1, 0);
	while(x >= 1)
	{
		if(used[x] != gxx)
			tree[x] = make_pair(-1, 0), used[x] = gxx;
		ans = max(ans, tree[x]);
		x -= lowbit(x);
	}
	return ans;
}

void solve(int l, int r)
{
	if(l == r || l > r) return ;
	int mid = l + r >> 1;
	solve(mid + 1, r);
	int cnt = 0;
	for(int i = l; i <= r; i++)
		if(i > mid)
			seq[++cnt] = Node(R[i], i, 1);
		else
			seq[++cnt] = Node(R[i], i, 2);
	sort(seq + 1, seq + 1 + cnt);
	gxx++;
	for(int i = 1; i <= cnt; i++)
	{
		if(seq[i].type == 1)
			add(L[seq[i].id], make_pair(f[seq[i].id].first + 1, -seq[i].id));
		else
			f[seq[i].id] = max(f[seq[i].id], Query(L[seq[i].id]));
	}
	solve(l, mid);
	return ;
}

void go(int x)
{
	ans_seq.push_back(x);
	if(f[x].first == 1) return ;
	go(-f[x].second);
	return ;
}
	

void work()
{
	tmp[0] = 0;
	for(int i = 1; i <= n; i++)
		f[i] = make_pair(1, -INF);
	for(int i = 1; i <= n; i++)
		scanf("%d", &L[i]), tmp[++tmp[0]] = L[i];
	sort(tmp + 1, tmp + 1 +tmp[0]);
	tmp[0] = unique(tmp + 1, tmp + 1 + tmp[0]) - tmp - 1;
	for(int i = 1; i <= n; i++)
		L[i] = lower_bound(tmp + 1, tmp + 1 + tmp[0], L[i]) - tmp;
	tmp[0] = 0;
	for(int i = 1; i <= n; i++)
		scanf("%d", &R[i]), tmp[++tmp[0]] = R[i];
	sort(tmp + 1, tmp + 1 +tmp[0]);
	tmp[0] = unique(tmp + 1, tmp + 1 + tmp[0]) - tmp - 1;
	for(int i = 1; i <= n; i++)
		R[i] = lower_bound(tmp + 1, tmp + 1 + tmp[0], R[i]) - tmp;
	solve(1, n);
	int ans = 0, Maxid = 0;
	for(int i = 1; i <= n; i++)
		if(f[i].first > ans)
			ans = f[i].first, Maxid = i;
	printf("%d\n", ans);
	ans_seq.clear();
	go(Maxid);
	for(int i = 0; i < ans_seq.size(); i++)
		printf("%d%s", ans_seq[i], i == (ans_seq.size() - 1) ? "\n" : " ");
	return ;
}

int main()
{
	while(scanf("%d", &n) == 1)
		work();
	return 0;
}
