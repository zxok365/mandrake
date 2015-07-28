#include<cstdio>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdlib>

using namespace std;

#define N 2005

int base[N],need[N];

int main()
{
	int s,t,m,test=0;
	scanf("%d%d%d", &s, &t, &m);
	while(s!=0 || t!=0 || m!=0)
	{
		for(int i = 1; i <= s; i++)
			base[i] = need[i] = 0;
		for(int i = 1; i <= s; i++)
		{
			int id, p ,q;
			scanf("%d%d%d", &id ,&p ,&q);
			base[id]+=q+p;
		}
		for(int i=1;i<=t;i++)
		{
			int sid,tot;
			scanf("%d%d",&sid,&tot);
			if(tot >= m) need[sid]=1;
		}
		int ans=0;
		for(int i=1;i<=s;i++)
			ans+=need[i]+base[i];
		printf("Case %d: %d\n",++test,ans);
		
	scanf("%d%d%d", &s, &t, &m);
	}
	return 0;
}
