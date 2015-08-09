#include <cstdio>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<iostream>

using namespace std;

#define N 1005

typedef long long LL;

int w[N][N], c[N][N];
LL Max[N], f[N][N];

vector<pair<int, pair<int, int> > >seq;

int main(void) 
{
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			scanf("%d", &w[i][j]), seq.push_back(make_pair(w[i][j], make_pair(i, j)));
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			scanf("%d", &c[i][j]);
	sort(seq.begin(), seq.end());
	for(int i = 1; i <= 4; i++)
		Max[i] = -1000000;
	int ed = 0;
	for(int i = 0; i < seq.size(); i = ed)
	{
		ed = i;
		for(;seq[ed].first == seq[i].first && ed < seq.size(); ed++)
		{
			if(seq[ed].first == 0) continue;
			int x = seq[ed].second.first, y = seq[ed].second.second;
			if(Max[1] != -1000000) 
				f[x][y] = max(f[x][y], 1LL*(-x) + -y + c[x][y] + Max[1]);
			if(Max[2] != -1000000)
				f[x][y] = max(f[x][y], 1LL*(-x) + y + c[x][y] + Max[2]);
			if(Max[3] != -1000000)
				f[x][y] = max(f[x][y], 1LL * x + -y + c[x][y] + Max[3]);
			if(Max[4] != -1000000)
				f[x][y] = max(f[x][y], 1LL * x + y + c[x][y] + Max[4]);
			if(Max[1] == -1000000)
				f[x][y] = 1LL * c[x][y];
		}
		ed = i;
		for(;seq[ed].first == seq[i].first && ed < seq.size(); ed++)
		{
			if(seq[ed].first == 0) continue;
			int x = seq[ed].second.first, y = seq[ed].second.second;
			Max[1] = max(Max[1], 1LL * x + y + f[x][y]);
			Max[2] = max(Max[2], 1LL * x - y + f[x][y]);
			Max[3] = max(Max[3], 1LL * (-x) + y + f[x][y]);
			Max[4] = max(Max[4], 1LL * (-x) - y + f[x][y]);			
		}
	}
	LL CC = 0;
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= m; j++)
			CC = max(CC, f[i][j]);
	cout << CC << endl;
	return 0;
}
