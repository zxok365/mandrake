#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>

using namespace std;

#define N 105
#define MP(x,y) make_pair(x,y)
#define LL long long

pair<int , pair<int,int> >tmp[N*N];

int dx[5]={0,1,-1,0,0};
int a[N][N],dy[5]={0,0,0,1,-1};
LL f[N][N];

int main()
{
	int n,m,T,test=0;
	scanf("%d",&T);
	while(T--)
	{
		LL ans=0;
		test++;
		scanf("%d%d",&n,&m);
		int cnt=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
				scanf("%d",&a[i][j]),tmp[++cnt]=MP(a[i][j],MP(i,j)),f[i][j]=0;
		sort(tmp+1,tmp+1+cnt);
		reverse(tmp+1,tmp+1+cnt);
		for(int i=1;i<=cnt;i++)
		{
			pair<int,int> now=tmp[i].second;
			int flag=0;
			for(int j=1;j<=4;j++)
			{
				int ux=now.first+dx[j],uy=now.second+dy[j];
				if(ux==0||uy==0||ux>n||uy>m) { continue;}
				if(a[ux][uy]<=a[now.first][now.second]) {continue;}
				f[now.first][now.second]+=f[ux][uy];
			}
		//	printf("%d %d %d\n",now.first,now.second,flag);
			if(f[now.first][now.second]==0) f[now.first][now.second]=1;
		//	printf("%d\n",flag);
			
			for(int j=1;j<=4;j++)
			{
				int ux=now.first+dx[j],uy=now.second+dy[j];
				if(ux==0||uy==0||ux>n||uy>m) { continue;}
				if(a[ux][uy]<a[now.first][now.second])flag++; 
			}
		 	if(!flag) ans+=f[now.first][now.second];
		}
	//	for(int i=1;i<=n;i++,puts(""))
	//		for(int j=1;j<=m;j++)
	//				printf("%lld ",f[i][j]);
		printf("Case #%d: %lld\n",test,ans);
	}
	return 0;
}
