#include <cstdio>
#include <algorithm>

const int N = 41;

int n, volume, maximum;
int price[N], counter[N];
int best[2][N][64005];

void update(int &x, int y) {
	x = std::max(x, y);
}

int main(void) {
	scanf("%d%d", &n, &volume);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &price[i]);
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &counter[i]);
		maximum = std::max(maximum, counter[i]);
	}
	
	int now = 0;
	for (int j = 0; j <= maximum; ++j) {
		for (int k = 0; k <= volume; ++k) {
			best[now][j][k] = -1;
		}
	}
	best[now][0][0] = 0;
	for (int i = n; i >= 1; --i) {
		for (int j = 0; j <= maximum; ++j) {
			for (int k = 0; k <= volume; ++k) {
				best[now ^ 1][j][k] = -1;
			}
		}
		for (int j = 0; j <= maximum; ++j) {
			for (int k = 0; k <= volume; ++k) {
				if (best[now][j][k] == -1) {
					continue;
				}
				for (int number = 0; number <= counter[i] && k + number * price[i] <= volume; ++number) {
					update(best[now ^ 1][std::min(j + number, maximum)][k + number * price[i]], best[now][j][k] + std::min(j + number, counter[i]) * price[i]);
				}
			}
		}
		now ^= 1;
	}
	int answer = 0;
	for (int i = 0; i <= maximum; ++i) {
		for (int j = 0; j <= volume; ++j) {
			update(answer, best[now][i][j]);
		}
	}
	printf("%d\n", answer);
}
