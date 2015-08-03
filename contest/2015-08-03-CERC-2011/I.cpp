#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>

using namespace std;

#define N 1000004

int seq[N], cnt = 0;
int bel[N], a[N], Tmp[N];

struct node
{
	int l, r;
	pair<int, int> Max;
}tree[N << 2];

pair<int, int> person[N];

void build(int root, int l, int r)
{
	tree[root].l = l, tree[root]. r = r;
	if(l == r)
	{
		tree[root].Max = person[l];
		return ;
	}
	int mid = l + r >> 1;
	build(root << 1, l, mid), build(root << 1 | 1, mid + 1, r);
	tree[root].Max = max(tree[root << 1].Max, tree[root << 1 | 1].Max);
	return ;
}

pair<int, int> Query(int root, int l, int r)
{
	if(tree[root].l == l && tree[root].r == r)
		return tree[root].Max;
	int mid = tree[root].l + tree[root].r >> 1;
	if(r <= mid)
		return Query(root << 1, l, r);
	else
		if(l > mid)
			return Query(root << 1 | 1, l ,r);
		else
			return max(Query(root << 1, l, mid), Query(root << 1 | 1, mid + 1, r));
}

int main()
{
	int m, q;
	scanf("%d %d", &m, &q);
	while(m != 0 || q != 0)
	{
		for(int i = 1; i <= m; i++)
			scanf("%d", &a[i]);
		for(int i = 1; i <= m; i++)
			Tmp[i] = a[i];
		int cnt = 0;
		for(int i = 1; i <= m; i++)
			seq[++cnt] = a[i];
		sort(seq + 1, seq + cnt + 1);
		cnt = unique(seq + 1, seq + cnt + 1) - seq - 1;
		for(int i = 1; i <= m; i++)
			a[i] = lower_bound(seq + 1, seq + cnt + 1, a[i]) - seq;
		for(int i = 1; i <= m; i++)
			bel[i] = -1;
		for(int i = 1; i <= m; i++)
		{
			int pre = 0;
			if(bel[a[i]] != -1) pre = bel[a[i]];
			bel[a[i]] = i;
			person[i] = make_pair(pre, i);
//			printf("%d %d\n", pre, i);
		}
		build(1, 1, m);
		for(int i = 1; i <= q; i++)
		{
			int l, r;
			scanf("%d %d", &l, &r);
			pair<int, int> tmp = Query(1, l, r);
			if(tmp.first >= l)
				printf("%d\n", Tmp[tmp.second] );
			else
				puts("OK");
		}
		puts("");
		scanf("%d %d", &m, &q);
	}
	return 0;
}
