#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<cstdlib>

using namespace std;

#define N 104

char c[N];
int bh[288];
int t[N];

int corner[9][4]={
{0,0,0,0},
{0,16,20,22},
{0,11,19,21},
{0,2,10,24},
{0,1,5,23},
{0,12,13,17},
{0,14,15,18},
{0,6,7,3},
{0,8,4,9}
};

int face[7][5]={
{0,0,0,0,0},
{0,1,2,3,4},
{0,7,8,13,14},
{0,5,6,11,12},
{0,9,10,15,16},
{0,17,18,19,20},
{0,21,22,23,24}
};

int color[N],now[9][4],test=0;
int U_cnt=0,bel[N],flag[N];
int seq[N],hack[25][25][25],num[7];

void work()
{
	++test;U_cnt++;
	printf("Case #%d: ",test);
	int cnt=0;
	bh['w']=1; bh['y']=2; bh['o']=3; bh['r']=4; bh['g']=5; bh['b']=6;
	for(int i=1;i<=6;i++) num[i]=0;
	for(int i=1;i<=8;i++)
	{
		gets(c+1);
		int len=strlen(c+1);
		for(int j=1;j<=len;j++)
			if(c[j]>='a'&&c[j]<='z')
				t[++cnt]=bh[c[j]],num[bh[c[j]]]++;	
	}
	int CC=0;	
	memset(flag,0,sizeof(flag));
	flag[1]=flag[4]=flag[6]=flag[10]=flag[11]=flag[15]=flag[17]=flag[20]=1;
	flag[2]=flag[3]=flag[5]=flag[9]=flag[12]=flag[16]=flag[18]=flag[19]=-1;
	for(int i=1;i<=24;i++)
	{
		if(t[i]<=4) continue;
		CC+=flag[i];
	}
	if(!(CC%3)) puts("YES");
	else puts("NO");
	gets(c+1);
	return ;
}

int main()
{
	int test=0;
	scanf("%d\n",&test);
	for(int i=1;i<=6;i++)
		for(int j=1;j<=4;j++)
			bel[face[i][j]]=i;
	for(int i=1;i<=test;i++)
		work();
	return 0;
}
