#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN = 60;
const int MAXW = 600;
const int inf = 1<<30;
int T,n,hlmt,wlmt;
int pos[MAXN],h[MAXN];
int f[MAXN][MAXW];
int main(){
	scanf("%d", &T);
	for (int tt=1;tt<=T;tt++){
		scanf("%d%d%d",&n,&hlmt,&wlmt);
		
		int maxn=0,maxh=0;
		for (int i=1;i<=n;i++){
			scanf("%d%d",&pos[i],&h[i]);
			if (pos[i]>maxn) maxn=pos[i];
			if (h[i]>maxh) maxh=h[i];
		}
		
		for (int i=1;i<=n;i++)
			for (int j=i+1;j<=n;j++)
				if (pos[i]>pos[j])
				{
					swap(pos[i],pos[j]);
					swap(h[i],h[j]);
				}
		
		for (int i=1;i<=n;i++)
			for (int j=1;j<=maxn;j++)
				f[i][j]=inf;

		for (int i=1;i<=n;i++) 
			if (h[i]<=hlmt) 
			{
				for (int j=1;j<=maxn;j++)
					f[i][j]=abs(j-pos[i])*h[i];
			}
		
		for (int i=2;i<=n;i++)
		{
			if (h[i]>h[i-1]+hlmt) continue;
			if (h[i]!=maxh)
				for (int j=1;j<=maxn;j++)
					{
						for (int k=1;k<j;k++)
							if (j-k<=wlmt) f[i][j]=min(f[i][j],f[i-1][k]+abs(j-pos[i])*h[i]);
					}
			else
				for (int k=max(1,pos[i]-wlmt);k<pos[i];k++)
					f[i][pos[i]]=min(f[i][pos[i]],f[i-1][k]);
		}
		
		int ans=inf;
		for (int i=1;i<=n;i++)
			if (h[i]==maxh) ans=min(ans,f[i][pos[i]]);
		
		for (int i=1;i<=n;i++)
			for (int j=1;j<=maxn;j++)
				f[i][j]=inf;
		
		
		for (int i=1;i<=n;i++)
			if (h[i]<=hlmt) 
			{
				for (int j=1;j<=maxn;j++)
					f[i][j]=abs(pos[i]-j)*h[i];
			}
		for (int i=n-1;i>=1;i--)
		{
			if (h[i]>h[i+1]+hlmt) continue;
			if (h[i]!=maxh)
			{
				
				for (int j=1;j<=maxn;j++)
					for (int k=j+1;k<=maxn;k++)
						if (k-j<=wlmt) f[i][j]=min(f[i][j],f[i+1][k]+abs(j-pos[i])*h[i]);
			}
			else
				for (int k=min(maxn,pos[i]+wlmt);k>pos[i];k--)
					f[i][pos[i]]=min(f[i][pos[i]],f[i+1][k]);
		}	
		
		for (int i=1;i<=n;i++)
			if (h[i]==maxh) ans=min(ans,f[i][pos[i]]);
		
		
		if (ans==inf){
			printf("Case #%d: %d\n",tt,-1);
		}
		else{
			printf("Case #%d: %d\n",tt,ans);
		}
	}
	return 0;
}
