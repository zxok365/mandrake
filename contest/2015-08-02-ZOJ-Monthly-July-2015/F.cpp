#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>

using namespace std;

#define N 10000010

int n, m;
int num[N], a[111111];
bool U_prime[N];
int cnt = 0;

struct node
{
	int l, r, Max, sum;
}tree[400444];


void update(int root)
{
	tree[root].Max = max(tree[root << 1].Max, tree[root << 1 | 1].Max);
	tree[root].sum = tree[root << 1].sum + tree[root << 1 | 1].sum;
	return ;
}

void build(int root, int x, int y)
{
	tree[root].l = x, tree[root].r = y;
	if(x == y)
	{
		tree[root].Max = a[x];
		tree[root].sum = num[a[x]];
		return ;
	}
	int mid = x + y >> 1;
	build(root << 1, x, mid);build(root << 1 | 1, mid + 1, y);
	update(root);
}

void update(int root, int x, int y)
{
	if(tree[root].l == tree[root].r)
	{
		tree[root].Max = y;
		tree[root].sum = num[y];
		return ;
	}
	int mid = tree[root].l + tree[root].r >> 1;
	if(x <= mid)
		update(root << 1, x, y);
	else
		update(root << 1 | 1, x, y);
	update(root);
}

int Query(int root, int x, int y)
{
	if(tree[root].l == x && tree[root].r == y)
		return tree[root].sum;
	int mid = tree[root].l + tree[root].r >> 1;
	if(y <= mid)
		return Query(root << 1, x, y);
	else
		if(x > mid)
			return Query(root << 1 | 1, x, y);
		else
			return Query(root << 1, x, mid) + Query(root << 1 | 1, mid + 1, y);
}

void update(int root, int x, int y, int key)
{
	if(tree[root].l == x && tree[root].r == y && tree[root].Max < key)
		return ;
	if(tree[root].l == tree[root].r)
	{
		tree[root].Max %= key;
		tree[root].sum = num[tree[root].Max];
		return ;
	}
	int mid = tree[root].l + tree[root].r >> 1;
	if(y <= mid)
		update(root << 1, x, y, key);
	else
		if(x > mid)
			update(root << 1 | 1, x, y, key);
		else
			update(root << 1, x, mid, key) , update(root << 1 | 1, mid + 1, y, key);	
	update(root);
}

int main()
{
	for(int i = 2; i <= N - 5; i++)
	{
		if(!U_prime[i]) num[i] = 1;
		else
			continue;
		for(int j = 2 * i; j <= N - 5; j += i)
			U_prime[j] = true;
	}
	int now = 2;
	for(; now <= N - 5; now *= 2)
		num[now] = 1;
	num[6] = num[0] = num[1] = 1;
	while(scanf("%d", &n) == 1)
	{
		for(int i = 1; i <= n; i++)
			scanf("%d", &a[i]);
		build(1, 1, n);
		int m;
		scanf("%d", &m);
		for(int i = 1; i <= m; i++)
		{
			int type;
			scanf("%d", &type);
			if(type == 1)
			{
				int x, y;
				scanf("%d%d", &x, &y);
				printf("%d\n", Query(1, x, y));
			}
			if(type == 2)
			{
				int x, y, r;
				scanf("%d%d%d", &x, &y, &r);
				update(1, x, y, r);
			}
			if(type ==3)
			{
				int x, r;
				scanf("%d%d", &x, &r);
				update(1, x, r);
			}
		}
	}
	return 0;
}
