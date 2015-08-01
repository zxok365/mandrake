#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define PI pair<int,int>

priority_queue<PI> Q;

int n; 
char type[6];

int main()
{
	scanf("%d", &n);
	int x;
	for(int i = 2; i <= n; i++)
	{
		scanf("%s", type + 1);
		scanf("%d", &x);
		if(type[1] == 'd')
			Q.push(make_pair(-x, i));
		else
		{
			int need = x - 1;
			if(i == n) need = 0x3f3f3f3f;
			while(Q.size() > need) Q.pop();
		}
	}
	if(Q.size() < x)
	{ puts("-1"); return 0;}
	vector<int> ans;
	int CC = 0;
	while(!Q.empty())
	{
		pair<int,int> t=Q.top();Q.pop();
		CC += -t.first; 
		ans.push_back(t.second);
	}
	sort(ans.begin(),ans.end());
	printf("%d\n",CC);
	printf("%d\n", (int)ans.size());
	for(int i = 0; i < ans.size(); i++)
		printf("%d ", ans[i]);
	puts("");
	return 0;
}
	
