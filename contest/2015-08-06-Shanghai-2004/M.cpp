#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cstdlib>

using namespace std;

#define N 75536

int n;
int w[N], h[N];
int S[N], ans[N];
pair<int, int> stack[N];

void work(int x)
{
	for(int i = 1; i <= n; i++)
		S[i] = S[i - 1] + w[i];
	int top = 0;
	for(int i = 1; i <= n; i++)
	{
		int next = i;
		while(top)
		{
			if(h[i] <= stack[top].first) top --;
			else break;
		}
		next = stack[top].second;
		stack[++top] = make_pair(h[i], i);
		if(x == 0)
			ans[i] += (S[i - 1] - S[next]) * h[i];
		else
			ans[n - i + 1] += (S[i - 1] - S[next]) * h[i];
	}
	return ;
}

int main()
{
	scanf("%d", &n);
	while(n != -1)
	{
		for(int i = 1; i <= n; i++)
			scanf("%d%d", &w[i], &h[i]);
		for(int i = 1; i <= n; i++)
			ans[i] = 0;
		work(0);
		reverse(w + 1, w + 1 + n);
		reverse(h + 1, h + 1 + n);
		work(1);
		int CC = 0;
		reverse(w + 1, w + 1 + n);
		reverse(h + 1, h + 1 + n);
		for(int i = 1; i <= n; i++)
			CC = max(CC, w[i] * h[i] + ans[i]);
		printf("%d\n", CC);
		scanf("%d", &n);
	}
	return 0;
}
