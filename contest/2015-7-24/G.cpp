#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>

using namespace std;

#define M 100005
#define N 10005

vector<int> seq;

struct node
{
	int x,y,next;
	bool flag;
}road[M*2];

int pre[N],low[N],dfs_clock=0,start[N];
int blo[N],col[N],tot=0;
bool used[N],ban[N];

void build(int x,int y)
{
	tot++;
	road[tot].x=x,road[tot].y=y,road[tot].next=start[x],start[x]=tot;
	road[tot].flag=false;
}

int dfs(int x,int fa)
{
	int lowu=pre[x]=++dfs_clock;
	for(int i=start[x];i;i=road[i].next)
		if(!pre[road[i].y])
		{
			int lowv=dfs(road[i].y,x);
			lowu=min(lowu,lowv);
			if(lowv>pre[x])
				road[i].flag=road[i^1].flag=true;
		}
		else
			if(pre[road[i].y]<pre[x]&&road[i].y!=fa)
				lowu=min(lowu,pre[road[i].y]);
	low[x]=lowu;
	return lowu;
}

void go(int x,int fa)
{
	used[x]=true;
	seq.push_back(x);
	for(int i=start[x];i;i=road[i].next)
	{
		int to=road[i].y;
		if(to==fa||road[i].flag||used[to]) continue;
		go(to,x);
	}
	return ;
}

void get_ans(int x,int fa)
{
	ban[x]=true;
	seq.push_back(x);
	for(int i=start[x];i;i=road[i].next)
	{
		int to=road[i].y;
		if(to==fa||ban[to]) continue;
		get_ans(to,x);
	}
}

int main()
{
	int T,test=0;
	scanf("%d",&T);
	while(T--)
	{
		test++;
		int n,m;
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++) start[i]=blo[i]=pre[i]=low[i]=0,used[i]=ban[i]=false;
		tot=1;dfs_clock=0;
		int cnt_bol=0;
		for(int i=1;i<=m;i++)
		{
			int p,q;
			scanf("%d%d",&p,&q);
			build(p,q);build(q,p);
		}
		for(int i=1;i<=n;i++)
			if(!pre[i])
				dfs(i,0);
		for(int i=1;i<=n;i++)
		{
			if(used[i]) continue;
			seq.clear();go(i,0);
			if(seq.size()>1)
				for(int j=0;j<seq.size();j++)
					ban[seq[j]]=true;
		}
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			if(ban[i]) continue;
			seq.clear();get_ans(i,0);
			ans+=(seq.size())*(seq.size()-1)/2;
		}
		printf("Case #%d: %d\n",test,ans);
	}
	return 0;
}
