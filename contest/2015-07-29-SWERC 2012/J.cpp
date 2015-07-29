#include <iostream>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <cmath>
using namespace std;
const int MAXN = 500;
pair<pair<int, int>, int> opt[10],outp[10];
int cnt, anstot, tag, ans, flg, T;
int a[MAXN];
int used[MAXN];
void check(int dep) {
	if (a[cnt] == tag) {
		flg = 1;
		ans = tag;
		for (int i = 1; i <= dep - 1; i++)
			outp[i] = opt[i];
		anstot = dep - 1;
		return;
	}
	if (abs(a[cnt] - tag) < abs(ans - tag)) {
		ans = a[cnt];
		for (int i = 1; i <= dep - 1; i++)
			outp[i] = opt[i];
		anstot = dep - 1;
	}
}

int counter = 0;

void dfs(int dep) {
		check(dep);
		if (dep > 5) return;
		if (flg) return;
	//	cout << cnt <<endl;
		for (int i = 1; i <= cnt; i++)
			for (int j = i + 1; j <= cnt; j++)
			if (!used[i] && !used[j])
				{
//counter++;
					a[++cnt] = a[i] + a[j];
					used[i] = used[j] = 1;
					opt[dep] = make_pair(make_pair(a[i], a[j]), 1);//plus
					dfs(dep + 1);
					if (flg) return;
					used[i] = used[j] = 0;
					cnt--;
					
					a[++cnt] = a[i] * a[j];
					long long tmp = 1LL * a[i] * a[j];
					if (tmp == a[cnt]) {
						used[i] = used[j] = 1;
						opt[dep] = make_pair(make_pair(a[i], a[j]), 2);//product
						dfs(dep + 1);
						if (flg) return;
						used[i] = used[j] = 0;
					}
					cnt--;
					if (a[i] > a[j]) {
					a[++cnt] = a[i] - a[j];
					opt[dep] = make_pair(make_pair(a[i], a[j]), 3);//minus
					used[i] = used[j] = 1;
					dfs(dep + 1);
					if (flg) return;
					used[i] = used[j] = 0;
					cnt--;
					}
					if (a[j] > a[i]) {
					a[++cnt] = a[j] - a[i];
					opt[dep] = make_pair(make_pair(a[j], a[i]),3);//minus
					used[i] = used[j] = 1;
					dfs(dep + 1);
					if (flg) return;
					used[i] = used[j] = 0;
					cnt--;
					}
					// divide
					if (a[i] != 0 && a[j] % a[i] == 0) {
						a[++cnt] = a[j] / a[i];
						opt[dep] = make_pair(make_pair(a[j], a[i]),4);
						used[i] = used[j] = 1;
						dfs(dep + 1);
						if (flg) return;
						used[i] = used[j] = 0;
						cnt--;
					}
					if (a[j] != 0 && a[i] % a[j] == 0) {
						a[++cnt] = a[i] / a[j];
						opt[dep] = make_pair(make_pair(a[i], a[j]),4);
						used[i] = used[j] = 1;
						dfs(dep + 1);
						if (flg) return;
						used[i] = used[j] = 0;
						cnt--;	
					}		
				}
}

void print(pair<pair<int, int>, int> tmp) {
	int tt;
	char ch;
	if (tmp.second == 1) tt = tmp.first.first + tmp.first.second, ch = '+';
	if (tmp.second == 2) tt = tmp.first.first * tmp.first.second, ch = '*';
	if (tmp.second == 3) tt = tmp.first.first - tmp.first.second, ch = '-';
	if (tmp.second == 4) tt = tmp.first.first / tmp.first.second, ch = '/'; 
	
	printf("%d %c %d = %d\n", tmp.first.first, ch, tmp.first.second, tt);
}

int main() {
	scanf("%d", &T);
	while (T--) {
counter = 0;
		for (int i = 1; i <= 6; i++) scanf("%d", &a[i]);
		scanf("%d", &tag);
		cnt = 6;
		bool found = 0;
		ans = a[1];
		for (int i = 1; i <= 6; i++) if (a[i] == tag) {
			if (abs(a[i] - tag) < abs(ans - tag)) {
				ans = a[i];
				anstot = 0;
			}
			if (a[i] == tag) {
				ans = a[i];
				anstot = 0;
				found = 1;
				break;
			}
		}
		if (!found)	{
			flg = 0;
			for (int i = 1; i <= 300; i++) used[i] = 0;
			dfs(1);
		}
		
		printf("Target: %d\n", tag);
		if (anstot) {
			for (int i = 1; i <= anstot; i++)
				print(outp[i]);
		}
		printf("Best approx: %d\n", ans);
		puts("");
//printf("%d\n", counter);
	}
	return 0;
}
