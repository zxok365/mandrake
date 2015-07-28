#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;
const int MAXN = 1024 * 10 + 10;
const int max_state = (1 << 16) - 1;
int used[10], a[10], b[10];
int total[max_state + 10];
vector<int> f[MAXN];

void check() {
	int sum = 0;
	int state = 0;
	for (int i = 1; i <= 4; i++) {
		state += 1 << (b[i] - 1);
		sum += a[b[i]] * i;
	}
	f[sum].push_back(state);
}

void dfs(int dep) {
	if (dep > 4) check();
	else {
		for (int i = 1; i <= 16; i++)
			if (!used[i]) {
				b[dep] = i;
				used[i] = 1;
				dfs(dep + 1);
				used[i] = 0;
			}
	}
}
void get_eight() { 
	for (int num = 10; num < MAXN; num++)
		if (f[num].size()) {
			for (int i = 0; i < (int)f[num].size(); i++)
				for (int j = i + 1; j < (int)f[num].size(); j++) {
					if (f[num][i] & f[num][j]) continue;
					total[f[num][i]^f[num][j]] ++;
				}
		}
}
void get_ans() {
	int ans = 0;
	for (int i = 0 ; i <= max_state; i++)
		ans += total[i] * total[max_state ^ i];		
	ans /= 2;
	printf("%d\n", ans);
}	

void clear() {
	for (int i = 0; i <= max_state; i++) total[i] = 0;
	for (int i = 0; i < MAXN; i++) f[i].clear();
	for (int i = 1; i <= 8; i++) used[i] = 0;
}

int main() {
	while (scanf("%d", &a[1]) && a[1] > 0) {
		static int tst = 0;
		printf("Case %d: ",++tst);
		clear();
		for (int i = 2; i <= 16; i++) scanf("%d", &a[i]);
		dfs(1);
		//cout << "ok" <<endl;
		get_eight();
		get_ans();
	}
	
	return 0;
}
