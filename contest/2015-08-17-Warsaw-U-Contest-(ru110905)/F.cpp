#include <cstdio>
#include <algorithm>
#include <vector>
#include <climits>

const int N = 333333;

int n, m, k;
std::vector<int> belong[N];
int ql[N], qr[N], val[N], answer[N];
long long number[N], sum[N], tree[N];

__inline long long lowbit(int x) {
	return x & -x;
}

long long query(int x) {
	long long answer = 0;
	for (int i = x; i > 0; i -= lowbit(i)) {
		answer += tree[i];
	}
	return answer;
}

void modify(int x, const long long &value) {
	for (int i = x; i <= m; i += lowbit(i)) {
		tree[i] += value;
	}
}

void modify(int left, int right, const long long &value) {
	modify(left, value);
	modify(right + 1, -value);
}

void solve(const std::vector<int> &set, int left, int right) {
	if (right - left <= 1) {
		for (int i = 0; i < (int)set.size(); ++i) {
			answer[set[i]] = right;
		}
	} else {
		int mid = left + right >> 1;
		
		for (int i = left + 1; i <= mid; ++i) {
			if (ql[i] <= qr[i]) {
				modify(ql[i], qr[i], val[i]);
			} else {
				modify(ql[i], m, val[i]);
				modify(1, qr[i], val[i]);
			}
		}
		for (int i = 0; i < (int)set.size(); ++i) {
			int x = set[i];
			sum[x] = 0;
			for (int j = 0; j < (int)belong[x].size(); ++j) {
				sum[x] += query(belong[x][j]);
				sum[x] = std::min(sum[x], number[x]);
			}
		}
		std::vector<int> setl, setr;
		for (int i = 0; i < (int)set.size(); ++i) {
			int x = set[i];
			if (sum[x] >= number[x]) {
				setl.push_back(x);
			} else {
				setr.push_back(x);
			}
		}
		
		for (int i = 0; i < (int)setr.size(); ++i) {
			int x = setr[i];
			number[x] -= sum[x];
		}
		
		for (int i = left + 1; i <= mid; ++i) {
			if (ql[i] <= qr[i]) {
				modify(ql[i], qr[i], -val[i]);
			} else {
				modify(ql[i], m, -val[i]);
				modify(1, qr[i], -val[i]);
			}
		}
		
		solve(setl, left, mid);
		solve(setr, mid, right);
	}
}

int main(void) {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int owner;
		scanf("%d", &owner);
		belong[owner].push_back(i);
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &number[i]);
	}
	scanf("%d", &k);
	for (int i = 1; i <= k; ++i) {
		scanf("%d%d%d", &ql[i], &qr[i], &val[i]);
	}
	
	std::vector<int> set;
	for (int i = 1; i <= n; ++i) {
		set.push_back(i);
	}
	
	solve(set, 0, k + 1);
	
	for (int i = 1; i <= n; ++i) {
		if (answer[i] <= k) {
			printf("%d\n", answer[i]);
		} else {
			puts("NIE");
		}
	}
}
