#include<cstring>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<vector>
#include<cassert>
using namespace std;
const int N(55555), LOG(16);
int fa[N][LOG], pth[N], siz[N], idx[N], dep[N];
int q[N];
char str[111];
struct Edge {
	int y, next;
} edges[N * 2];
int l;
void build(int x, int y) {
	edges[++l].next = idx[x];
	edges[l].y = y;
	idx[x] = l;
}
int getInt() {
	int x(0);
	char c;
	c = getchar();
	while(c < '0' || c > '9') {
		c = getchar();
	}
	while(c >= '0' && c <= '9') {
		x = x * 10 + c - 48;
		c = getchar();
	}
	return x;
}
void print(long long ans) {
	int l(0);
	while(ans) {
		str[l++] = ans % 10 + 48;
		ans /= 10;
	}
	for(int i(0); i < l / 2; i++) {
		swap(str[i], str[l - i - 1]);
	}
	str[l] = '.';
	str[l + 1] = '0';
	str[l + 2] = '0';
	str[l + 3] = '0';
	str[l + 4] = '0';
	str[l + 5] = 0;
	puts(str);
}
int dis(int x, int y) {
	int ans(dep[x] + dep[y]);
	for(int i(LOG - 1); i >= 0; i--) {
		if(dep[fa[x][i]] >= dep[y]) {
			x = fa[x][i];
		}
		if(dep[fa[y][i]] >= dep[x])  {
			y = fa[y][i];
		}
	}
	for(int i(LOG - 1); i >= 0; i--) {
		if(fa[x][i] != fa[y][i]) {
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	if(x != y) {
		x = fa[x][0];
	}
	return ans - 2 * dep[x];
}
int main() {
	int tests;
	tests = getInt();
	for(int qq(1); qq <= tests; qq++) {
		int n;
		n = getInt();
//n = 50000;
		l = 0;
		fill(idx, idx + n, 0);
		for(int i(0); i < n - 1; i++) {
			int x, y;
			x = getInt();
			y = getInt();
//x = i;
//y = i + 1;
			build(x, y);
			build(y, x);
		}
		int cl(0);
		q[cl++] = 0;
		fill(dep, dep + n, -1);
		dep[0] = 0;
		for(int i(0); i < LOG; i++) {
			fa[0][i] = 0;
		}
		for(int op(0); op < cl; op++) {
			int v(q[op]);
			for(int p(idx[v]); p; p = edges[p].next) {
				int y(edges[p].y);
				if(dep[y] == -1) {
					dep[y] = dep[v] + 1;
					fa[y][0] = v;
					q[cl++] = y;
					for(int i(1); i < LOG; i++) {
						fa[y][i] = fa[fa[y][i - 1]][i - 1];
					}
				}
			}
		}
		
		int k;
		k = getInt();
//k = 100;
		for(int i(1); i <= k; i++) {
			int m, x, y;
			long long ans(0);
			m = getInt();
//m = 500;
			//printf("%d\n", i);
			x = getInt();
			y = getInt();
//x = rand() % n;
//y = rand() % n;
			//printf("%d %d %d\n", m, x, y);
			for(int j(2); j <= m; j++) {
				int now;
				now = getInt();
//now = rand() % n;
				ans += 2ll * (n - 1) * (dis(x, y) + dis(y, now) - dis(x, now)) / 2;
				y = now;
			}
			//printf("%d %d\n", x, y);
			if(x != y) {
				int cl(0);
				q[cl++] = y;
				fill(pth, pth + n, -1);
				pth[y] = 0;
				fill(siz, siz + n, 1);
			
				int d(dis(x, y));
				if(d == dep[x] - dep[y]) {
					int xx(x);
					for(int i(LOG - 1); i >= 0; i--) {
						if((d - 1) & (1 << i)) {
							xx = fa[xx][i];
						}
					}
					q[cl++] = xx;
					pth[xx] = y;
				}else {
					q[cl++] = fa[y][0];
					pth[q[cl - 1]] = y;
				}
				assert(dis(q[1], x) == dis(y, x) - 1);
				for(int op(1); op < cl; op++) {
					int v(q[op]);
					for(int p(idx[v]); p; p = edges[p].next) {
						int y(edges[p].y);
						if(pth[y] == -1) {
							pth[y] = v;
							q[cl++] = y;
						}
					}
				}
				for(int i(cl - 1); i > 0; i--) {
					//printf("%d\n", pth[q[i]]);
					if(pth[q[i]] != -1) {
						siz[pth[q[i]]] += siz[q[i]];
					}
				}
				int p(x);
				//printf("%lld %d %d\n", ans, siz[0], siz[1]);
				while(p != y) {
					ans += siz[p] * 2 - 1;
					//printf("%d\n", siz[p]);
					p = pth[p];
				}
				//printf("%lld\n", ans);
			}
			print(ans);
		}
		if(qq != tests) {
			puts("");
		}
	}
}
