#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

const int N = 100005;

pair<pair<int, int>, int> a[N];
priority_queue<pair<int, int> > Q;
int ans[N];
bool used[N];

void work() {
	int n; 
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i].first.first);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i].first.second);
	for(int i = 1; i <= n; i++)
		a[i].second = i;
	sort(a + 1, a + 1 + n);
	int now = 0, st = 1;
	while(!Q.empty())
		Q.pop();
	while(1) {
		for(; st <= n && a[st].first.first <= now; st++)
			Q.push(make_pair(-a[st].first.second, a[st].second));
		int CC = -1;
		while(!Q.empty()) {
			pair<int,int> t = Q.top(); Q.pop();
			if(-t.first < now) continue;
			//printf("!!!%d %d\n", -t.first);
			CC = t.second;
			break;
		}
		if(CC == -1) break;
		ans[++now] = CC;
	}
	for(int i = 1; i <= n; i++)
		used[i] = false;
	for(int i = 1; i <= now; i++)
		used[ans[i]] = true;
	printf("%d\n", now);
	for(int i = 1; i <= n; i++)
		if(!used[i])
			ans[++now] = i;
	for(int i = 1; i <= n; i++)
		printf("%d%s", ans[i], (i == n) ? "\n" : " ");
	return ;
}

int main() { 
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++)
		work();
	return 0;
}
