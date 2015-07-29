#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cmath>

using namespace std;

#define N 105

char s1[N], s2[N];
int num1[N], num2[N];
int num[N][N],n;

void work()
{
	scanf("%s", s1 + 1);
	scanf("%s", s2 + 1);
	int n = strlen(s1 + 1);
	memset(num, 0, sizeof(num));
	for(int i = 1; i <= n; i++)
		if(s1[i] == '?')
			num1[i] = 3;
		else
			num1[i] = s1[i] - '0';
	for(int i = 1; i <= n; i++)
		if(s2[i] == '?')
			num2[i] = 3;
		else
			num2[i] = s2[i] - '0';
	for(int i = 1; i <= n; i++)
		num[num1[i]][num2[i]]++;
	int Min=min(num[0][1], num[1][0]);
	if(Min == num[0][1])
	{
		num[1][0] -= num[0][1];
		if(num[3][1] < num[1][0])
		{ puts("-1"); return ;}
		printf("%d\n",Min + num[1][0] + num[3][0] + num[3][1]);
	}
	else
	{
		num[0][1] -= num[1][0];
		printf("%d\n",Min + num[0][1] + num[3][0] + num[3][1]);
	}
	return ;
}

int main()
{
	int test;
	scanf("%d", &test);
	for(int i = 1; i <= test; i++)
		printf("Case %d: ",i),work();
	return 0;
}
