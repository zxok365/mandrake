#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

char s[111];

priority_queue<pair<int, int> > sell, buy;

void work()
{
	while(!sell.empty())
		sell.pop();
	while(!buy.empty())
		buy.pop();
	int n;
	scanf("%d", &n);int last = -1;
	for(int i = 1; i <= n; i++)
	{
		int cost, num;
		scanf("%s", s + 1);
		int type = 0;
		if(s[1] == 'b')
			type = 1;
		else
			type = 2;
		scanf("%d", &num);
		scanf("%s", s + 1);
		scanf("%s", s + 1);
		scanf("%d", &cost);
		if(type == 1)
			buy.push(make_pair(cost, num));
		else	
			sell.push(make_pair(-cost, num));
		while(!buy.empty() && !sell.empty())
		{
			pair<int, int> tmpb, tmps;
			tmpb = buy.top(); buy.pop();
			tmps = sell.top(); sell.pop();
			tmps.first *= -1;
			if(tmpb.first < tmps.first)
			{
				tmps.first *= -1;
				buy.push(tmpb), sell.push(tmps);
				break;
			}	
			int CC = min(tmpb.second, tmps.second);
			tmpb.second -= CC, tmps.second -= CC;
			last = tmps.first;
			if(tmpb.second) buy.push(tmpb);
			if(tmps.second) tmps.first *= -1, sell.push(tmps);
		}
		int ans1, ans2;
		
		if(sell.empty())
			ans1 = -1;
		else
			ans1 = -sell.top().first;
		
		if(buy.empty())
			ans2 = -1;
		else
			ans2 = buy.top().first;
		
		if(ans1 == -1)
			printf("- ");
		else
			printf("%d ", ans1);
		
		if(ans2 == -1)
			printf("- ");
		else
			printf("%d ", ans2);
		
		if(last == -1)
			printf("-");
		else
			printf("%d", last);
		puts("");
	}
}
		
int main()
{
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++)
		work();
	return 0;
}
