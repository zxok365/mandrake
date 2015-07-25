#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;

#define N 100005
#define M 27

typedef long long LL;

int n, k,y[N],a[N];
int bh[N],Min[N][M],Max[N][M];
int ans[N];

int lowbit(int x)
{
	return x&(-x);
}

int get_Max(int x,int y)
{
	int len=bh[y-x+1];
	return max(Max[x][len],Max[y-(1<<len)+1][len]);
}

int get_Min(int x,int y)
{
	int len=bh[y-x+1];
	return min(Min[x][len],Min[y-(1<<len)+1][len]);
}

void work()
{
	scanf("%d%d",&n,&k);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(int i=1;i<=n;i++)
		for(int j=0;j<=bh[n];j++)
			Min[i][j]=0x3f3f3f3f,Max[i][j]=-1;
	for(int i=1;i<=n;i++) Min[i][0]=Max[i][0]=a[i];
	for(int i=1;i<=bh[n];i++)
		for(int j=1;j<=n;j++)
			Min[j][i]=min(Min[j][i-1],Min[min(n,j+(1<<i-1))][i-1]),
			Max[j][i]=max(Max[j][i-1],Max[min(n,j+(1<<i-1))][i-1]);
	for(int i=1;i<=n;i++)
	{
		int l=i,r=n;
		while(l<=r)
		{
			int mid=l+r>>1;
			if(get_Max(i,mid)<a[i]+k&&get_Min(i,mid)>a[i]-k)
			{
				l=mid+1;
				y[i]=mid;
			}
			else
				r=mid-1;
		}
	}
	
	for(int i=1;i<=n;i++)
		for(int j=0;j<=bh[n];j++)
			Min[i][j]=0x3f3f3f3f;
	for(int i=1;i<=n;i++)
		Min[i][0]=y[i];
	for(int i=1;i<=bh[n];i++)
		for(int j=1;j<=n;j++)
			Min[j][i]=min(Min[j][i-1],Min[min(n,j+(1<<i-1))][i-1]);
	LL CC=0;
	for(int i=1;i<=n;i++)
	{
		int l=i,r=n;
		while(l<=r)
		{
			int mid=l+r>>1;
			if(get_Min(i,mid)>=mid)
			{
				ans[i]=mid;
				l=mid+1;
			}
			else
				r=mid-1;
		}
		CC+=(long long)(ans[i]-i+1);
	}
	cout<<CC<<endl;
}

int main()
{
	int test = 0;
	scanf("%d", &test);
	for(int i=2;i<=100000;i++)
		bh[i]=bh[i-1]+(i==lowbit(i));
	for(int i = 1; i <= test; i++)
		work();
	return 0;
}
/*
0 0 0 0 
-6
1 4 5 6 5 0 0 8 10 10 
-28
*/


/*
3 1 2 4 
1 1 2 4 
1 1 2 4 
1 1 2 4 

3 1 2 4 
3 2 4 4 
4 4 4 4 
4 4 4 4 


0 3 4 5 2 1 6 7 8 9 
0 3 4 2 1 1 6 7 8 9 
0 2 1 1 1 1 6 7 8 9 
0 1 1 1 1 1 6 7 8 9 
0 1 1 1 1 1 6 7 8 9 

0 3 4 5 2 1 6 7 8 9 
3 4 5 5 2 6 7 8 9 9 
5 5 5 6 7 8 9 9 9 9 
7 8 9 9 9 9 9 9 9 9 
9 9 9 9 9 9 9 9 9 9 

*/


