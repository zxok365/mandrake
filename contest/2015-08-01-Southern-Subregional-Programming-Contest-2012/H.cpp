#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

#define N 40005

vector<int> bel[N];
int n, k;

int check(int x)
{
	vector<int> seq;
	for(int i = 1; i <= 40000; i++)
		if(bel[i].size() >= x)
		{
			int CC = 0;
			for(int j = 0; j < x; j++)
				CC += bel[i][j];
			seq.push_back(CC);
		}
	if(seq.size() < k) return -1;
	sort(seq.begin(),seq.end());
	reverse(seq.begin(),seq.end());
	int ans = 0;
	for(int i = 0; i < k;i++)
		ans += seq[i];
	return ans;
}

int main()
{
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++)
	{
		int p, q;
		scanf("%d%d", &p, &q);
		bel[p].push_back(q);
	}
	for(int i = 1; i <= 40000; i++)
		sort(bel[i].begin(), bel[i].end()),
		reverse(bel[i].begin(), bel[i].end());
	int left = 0,right = n;
	pair<int,int> ans = make_pair(0, 0);
	while(left <= right)
	{
		int mid = left + right >> 1;
		int t = check(mid);
		if(t == -1) 
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
			ans = make_pair(mid, t);
		}
	}
	printf("%d %d\n", ans.first, ans.second);
	return 0;
}
	
