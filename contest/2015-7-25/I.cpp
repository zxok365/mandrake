#include<cstdio>
#include<cmath>
#include<iostream>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<set>

using namespace std;

#define N 222222
#define M 25
#define MP(x,y) make_pair(x,y)

set<pair<int, int> >go;

struct node
{
	int x,y,key,next;
}road[N*2];

int n,Q,start[N],cnt,tot,dfn[N], vis[N];
int dis[N],father[N][M],deep[N],test=0;

void build(int x,int y,int key)
{
	++tot;
	road[tot].x=x,road[tot].y=y,road[tot].key=key;
	road[tot].next=start[x],start[x]=tot;
}

void dfs(int x,int fa)
{
	father[x][0]=fa; dfn[x]=++cnt;
	for(int i=start[x];i;i=road[i].next)
	{
		int to=road[i].y;
		if(to==fa) continue;
		dis[to]=dis[x]+road[i].key;deep[to]=deep[x]+1;
		dfs(to,x);
	}
	return ;
}

int get_lca(int x,int y)
{
	if(deep[x]<deep[y]) swap(x,y);
	for(int i=20;i>=0;i--)
		if(deep[father[x][i]]>=deep[y])
			x=father[x][i];
	if(x==y) return x;
	for(int i=20;i>=0;i--)
		if(father[x][i]!=father[y][i])
			x=father[x][i],y=father[y][i];
	return father[x][0];
}

int get_dis(int x,int y)
{	
	int fa=get_lca(x,y);
	return dis[x]+dis[y]-2*dis[fa];
}

int calc(int x,int y,int now)
{
//	printf("%d %d %d\n",x,y,now);
	return (get_dis(x,now)+get_dis(y,now)-get_dis(x,y)) >> 1;
}

pair<int, int> get(int now) {
	if ((int)go.size() == 0) {
		return make_pair(now, now);
	}
	
	set<pair<int, int> >::iterator it = go.upper_bound(make_pair(dfn[now], -1));
	if (it == go.begin() || it == go.end()) {
		return make_pair(go.begin()->second, go.rbegin()->second);
	} else {
		set<pair<int, int> >::iterator prev = it, next = it;
		prev--;
		return make_pair(prev->second, next->second);
	}
}

void work()
{
	test++;
	printf("Case #%d:\n",test);
	tot=cnt=0;
	scanf("%d%d",&n,&Q);
	for(int i=1;i<=n;i++) start[i]=0;
	for(int i=1;i<=n-1;i++)
	{
		int p,q,t;
		scanf("%d%d%d",&p,&q,&t);
		build(p,q,t),build(q,p,t);
	}
	deep[1]=dis[1]=0;
	dfs(1,0);
	for(int i=1;i<=20;i++)
		for(int j=1;j<=n;j++)
			father[j][i]=father[father[j][i-1]][i-1];
	
	go.clear();
	for (int i = 1; i <= n; ++i) {
		vis[i] = false;
	}
		
	int ret = 0;
	for (int i = 1; i <= Q; ++i) {
		int type, x;
		scanf("%d%d", &type, &x);
		
		if (type == 1) {
			if (!vis[x]) {
				vis[x] = true;
				pair<int, int> y = get(x);
				go.insert(make_pair(dfn[x], x));
				ret += calc(y.first, y.second, x);
			}
		} else {
			if (vis[x]) {
				vis[x] = false;
				go.erase(make_pair(dfn[x], x));
				pair<int, int> y = get(x);
				ret -= calc(y.first, y.second, x);
			}
		}
		printf("%d\n", ret);
	}
}

int main()
{
	int test=0;
	scanf("%d",&test);
	for(int i=1;i<=test;i++)
		work();
	return 0;
}
