#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const long long MO = 1e9 + 9;
const int N = 522;

pair<int, int> player[N * 2];
long long f[2][N][N];
int n, m;

int main() {
	scanf("%d%d", &n, &m);
	
	if ((n + m) % 2) {
		puts("0");
		return 0;
	}
	
	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		player[i] = make_pair(x, 1);
	}
	
	for (int i = 1; i <= n; i++) {
		int x;
		scanf("%d", &x);
		player[i + n] = make_pair(x, 2);
	}
	
	sort(player + 1, player + 2 * n + 1);
	
	int now = 0;
	f[now][0][0] = 1;
	
	int cnt1 = 0, cnt2 = 0;
	for (int i = 0; i < 2 * n; i++) {
		if (player[i].second == 1) cnt1 ++;
		if (player[i].second == 2) cnt2 ++;
		
		for (int j = 0; j <= cnt1 + 1; ++j) {
			for (int k = 0; k <= cnt2 + 1; ++k) {
				f[now ^ 1][j][k] = 0;
			}
		}		
		
		for (int j = 0; j <= cnt1; j++)
			for(int k = 0; k <= cnt2; k++) 
				if (f[now][j][k]) {
					(f[now ^ 1][j][k] += f[now][j][k]) %= MO;
					
					if (player[i + 1].second == 1) {
						if (cnt2 - j - k > 0) {
							(f[now ^ 1][j + 1][k] += f[now][j][k] * (cnt2 - j - k) % MO) %= MO;
						}
					}
					else {
						if (cnt1 - j - k > 0) {
							(f[now ^ 1][j][k + 1] += f[now][j][k] * (cnt1 - j - k) % MO) %= MO;
						}
					}
				}
		now ^= 1;
	}
	
	long long &result = f[now][(n + m) / 2][(n - m) / 2];
	
	result %= MO;
	result += MO;
	result %= MO;
	
	printf("%d\n", (int)result);
	return 0;
}

