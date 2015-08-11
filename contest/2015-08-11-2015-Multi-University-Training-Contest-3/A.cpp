#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define lc (x << 1)
#define rc ((lc) + 1)

const long long inf = 1LL << 60;
using namespace std;
const int MAXN = 111111;

class Node {
public:
	long long value[2][2];
	
	Node() {
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 2; ++j) {
				value[i][j] = -inf;
			}
		}
	}
	
	friend Node operator + (const Node &a, const Node &b) {
		Node c;
		for (int i = 0; i <= 1; i++) {
			for (int j = 0; j <= 1; j++) {
				c.value[i][j] = max(a.value[i][j], b.value[i][j]);
				for (int k = 0 ; k<= 1; k++) {
					c.value[i][j] = max(c.value[i][j], a.value[i][k] + b.value[k ^ 1][j]);
				}
			}
		}
		return c;
	}
};

Node T[MAXN * 4];

int a[MAXN];
void update(int x) {
}
void build(int x, int l, int r) {
	T[x] = Node();
	if (l == r) {
		if (l & 1) {
			T[x].value[1][1] = a[l];
		}
		else {
			T[x].value[0][0] = a[l];
		}
		return;
	}
	int mid = (l + r) >> 1;
	build(lc, l, mid);
	build(rc, mid + 1, r);
	T[x] = T[x << 1] + T[x << 1 | 1];
}

void modify(int x, int l, int r, int pos, int to) {
	if (l == r) {
		if (l & 1) {
			T[x].value[1][1] = to;
		}
		else {
			T[x].value[0][0] = to;
		}
		return;
	}
	int mid = (l + r) >> 1;
	if (pos <= mid) modify(lc, l, mid, pos, to);
	else modify(rc, mid + 1, r, pos, to);
	T[x] = T[x << 1] + T[x << 1 | 1];
}

Node query(int x, int l, int r, int ll, int rr) {
	if (ll <= l && rr >= r) {
		return T[x];
	}
	int mid = (l + r) >> 1;
	Node ret = Node();
	if (ll <= mid) ret = ret + query(lc, l, mid, ll, rr);
	if (rr > mid) ret = ret + query(rc, mid + 1, r, ll, rr);
	return ret;
	
}
void solve() {
	int n, m;
	scanf("%d%d", &n, &m);
	
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	
	build(1, 1, n);
	for (int i = 1; i <= m; i++) {
		int qtype;
		scanf("%d", &qtype);
		if (qtype == 1) {
			int x, change;
			scanf("%d%d", &x, &change);
			modify(1, 1, n, x, change);
		}
		else {
			int ql, qr;
			scanf("%d%d", &ql, &qr);
			Node result = query(1, 1, n, ql, qr);
			long long answer = -inf;
			for (int a = 0; a < 2; ++a) {
				for (int b = 0; b < 2; ++b) {
					answer = max(answer, result.value[a][b]);
				}
			}
			printf("%lld\n", answer);
		}
	}
}
int main() {
	int test;
	scanf("%d", &test);
	for (int i = 1; i <= test; i++) {
		solve();
	}
	return 0;
}
