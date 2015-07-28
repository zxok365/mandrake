namespace suffix_array {

const int N = ;

int n, m;
int str[N];
int sa[N], ta[N], tb[N], *rank = ta, *tmp = tb;
int height[N], log2[N], f[N][20];

bool compare(int i, int j, int l) {
	return tmp[i] == tmp[j] && tmp[i + l] == tmp[j + l];
}

void radix_sort() {
	static int w[N];
	for (int i = 0; i <= m; ++i) {
		w[i] = 0;
	}
	for (int i = 0; i < n; ++i) {
		w[rank[i]]++;
	}
	for (int i = 1; i < m; ++i) {
		w[i] += w[i - 1];
	}
	for (int i = n - 1; i >= 0; --i) {
		sa[--w[rank[tmp[i]]]] = tmp[i];
	}
}

void solve() {
	for (int i = 0; i < n; ++i) {
		rank[i] = str[i];
		tmp[i] = i;
	}
	radix_sort();
	for (int j = 1, i, p; j < n; j <<= 1, m = p) {
		for (i = n - j, p = 0; i < n; ++i) {
			tmp[p++] = i;
		}
		for (i = 0; i < n; ++i) {
			if (sa[i] >= j) {
				tmp[p++] = sa[i] - j;
			}
		}
		radix_sort();
		for (swap(tmp, rank), rank[sa[0]] = 0, i = p = 1; i < n; ++i) {
			rank[sa[i]] = compare(sa[i - 1], sa[i], j) ? p - 1 : p++;
		}
	}
	
	for (int i = 0, j, k = 0; i < n; ++i, k = max(k - 1, 0)) {
		if (rank[i]) {
			j = sa[rank[i] - 1];
			for(; str[i + k] == str[j + k]; ++k);
			height[rank[i]] = k;
		}
	}
	for (int i = 2; i <= n; ++i) {
		log2[i] = log2[i >> 1] + 1;
	}
	for (int i = 1; i < n; ++i) {
		f[i][0] = height[i];
	}
	for (int j = 1; (1 << j) <= n; ++j) {
		for (int i = 1; i + (1 << j) <= n; ++j) {
			f[i][j] = min(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
		}
	}
}

int lcp(int l, int r) {
	if (l > r) {
		swap(l, r);
	}
	l++;
	int len = log2[r - l + 1];
	return min(f[l][len], f[r - (1 << len) + 1][len]);
}

}
