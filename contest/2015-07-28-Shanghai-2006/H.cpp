#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<vector>


using namespace std;

#define LIMIT 1000
#define MP make_pair


char type[1000];

int seq[400005];

struct node
{
	int l,r;
	pair<int,int>Min;
}tree[2002000];

int work1(int x)
{
	int Min=0x3f3f3f3f,Minid=0;
	for(int i=seq[0];i>=1;i--)
	{
		if(seq[i]%x==0) return i;
		int t=seq[i]%x;
		if(t<Min)
			Min=t,Minid=i;
	}
	return Minid;
}

void build(int root,int x,int y)
{
	tree[root].l=x,tree[root].r=y;
	tree[root].Min=MP(0x3f3f3f3f,0x3f3f3f3f);
	if(x==y) return ;
	int mid=x+y>>1;
	build(root<<1,x,mid),build(root<<1|1,mid+1,y);
}

void insert(int root,int x,int y)
{	
	if(tree[root].l==tree[root].r)
	{
		tree[root].Min=MP(tree[root].l,-y);
		return ;
	}
	int mid=tree[root].l+tree[root].r>>1;
	if(x>mid) insert(root<<1|1,x,y);
	else insert(root<<1,x,y);
	tree[root].Min=min(tree[root<<1|1].Min,tree[root<<1].Min);
}

pair<int,int> Query(int root,int l,int r)
{
	if(tree[root].l==l && tree[root].r==r)
		return tree[root].Min;
	int mid=(tree[root].l+tree[root].r)>>1;
	if(l > mid) return Query(root<<1|1,l,r);
	else if(r <= mid) return Query(root<<1,l,r);
	else return min(Query(root<<1,l,mid),Query(root<<1|1,mid+1,r));
}	

int work2(int x)
{
	pair<int,int> ans=MP(0x3f3f3f3f,0x3f3f3f3f);
	int l=1,r=x-1;
	while(1)
	{
		r=min(r,500000);
		pair<int,int>tmp=Query(1,l,r);
		tmp.first-=l;
		if(l==1) tmp.first++;
		ans=min(ans,tmp);
		l=r+1,r=l+x-1;
		if(l>500000) break;
	}
	return -ans.second;
}

int main()
{
	int n;
	scanf("%d",&n);
	int test=0;
	while(n)
	{
		if(test>0) puts("");
		printf("Case %d:\n",++test);
		build(1,1,500000);
		int now=0,x;
		seq[0]=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%s",type+1);
			scanf("%d",&x);
			if(type[1]=='A')
			{
				if(now==0)
				{puts("-1"); continue;}
				if(x<LIMIT)
					printf("%d\n",work1(x));
				else
					printf("%d\n",work2(x));
			}
			else
			{
				++now;seq[++seq[0]]=x;
				insert(1,x,now);
			}
		}
		scanf("%d",&n);
	}
	return 0;
}
