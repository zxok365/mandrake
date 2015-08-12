#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

const int N = 1111111;

int n, m, k;
char text[N];

void solve(void) {
	scanf("%d%d%d%s", &m, &n, &k, text);
	std::vector<int> pos;
	for (int i = 0; i < k; ++i) {
		if (text[i] == '1') {
			pos.push_back(i);
		}
	}
	long long step = m - n;
	for (int now = m, next; now < (int)pos.size(); now = next) {
		next = lower_bound(pos.begin(), pos.end(), pos[now - m] + n) - pos.begin();
		if (next == now) {
			puts("IMPOSSIBLE");
			return;
		}
		step += m + pos[next - m] - pos[now - m];
	}
	std::cout << step << std::endl;
}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
