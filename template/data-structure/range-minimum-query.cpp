const int N = , M = ;

int log2[N];
pair<int, int> num[N][M];

void build(int n, int a[]) {
	for (int i = 2; i <= n; ++i) {
		log2[i] = log2[i >> 1] + 1;
	}
	for (int i = 1; i <= n; ++i) {
		num[i][0] = make_pair(a[i], i);
	}
	for (int j = 1; (1 << j) <= n; ++j) {
		for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
			num[i][j] = min(num[i][j - 1], num[i + (1 << j - 1)][j - 1]);
		}
	}
}

pair<int, int> solve(int left, int right) {
	int k = log2[right - left + 1];
	return min(num[left][k], num[right - (1 << k) + 1][k]);
}