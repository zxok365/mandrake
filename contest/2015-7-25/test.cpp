#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<ctime>

using namespace std;

int main()
{freopen("C.in","w",stdout);
	srand(time(0));
	int n=100000;
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
		printf("%d ",rand()%10);
	puts("");
	for(int i=2;i<=n;i++)
	{
		int p=rand()%(i-1)+1;
		printf("%d %d\n",p,i);
	}
	printf("%d\n",n);
	for(int i=1;i<=n;i++)
		printf("%d ",rand()%2);
	puts("");
	for(int i=2;i<=n;i++)
	{
		int p=rand()%(i-1)+1;
		printf("%d %d\n",p,i);
	}
	return 0;
}
