#include<cstring>
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const int N(111111);
int fac[N], inv[N], invFac[N];
long long getLL() {
	long long x(0);
	char c;
	c = getchar();
	while(c < '0' || c > '9') {
		c = getchar();
	}
	while(c >= '0' && c <= '9') {
		x = x * 10 + (c - 48);
		c = getchar();
	}
	return x;
}
int main() {
	int tests;
	tests = getLL();
	for(int qq(1); qq <= tests; qq++) {
		long long n, m, k;
		n = getLL();
		m = getLL();
		k = getLL();
		long long ans(0), mul(1);
		for(int i(0); i < k; i++) {
			int p;
			p = getLL();
			
			fac[0] = fac[1] = 1;
			inv[0] = inv[1] = 1;
			invFac[0] = invFac[1] = 1;
			for(int i(2); i < p; i++) {
				fac[i] = (long long)fac[i - 1] * i % p;
				inv[i] = (long long)inv[i - p % i] * ((p + i - 1) / i) % p;
				invFac[i] = (long long)invFac[i - 1] * inv[i] % p;
				//printf("inv[%d] = %d, invFac[%d] = %d\n", i, inv[i], i, invFac[i]);
			}
			int tmp(1), x(n), y(m);
			while(y) {
				//C(x % p, y % p)
				int xx(x % p), yy(y % p);
				//printf("%lld %lld %d %d %d\n", n, m, xx, yy, p);
				if(xx < yy) {
					tmp = 0;
					break;
				}else {
					tmp = (long long)tmp * fac[xx] % p * invFac[yy] % p * invFac[xx - yy] % p;
				}
				x /= p;
				y /= p;
				//printf("%d %d %d\n", xx, yy, xx - yy);
				//printf("%d %d %d %d\n", tmp, fac[xx], invFac[yy], invFac[xx - yy]);
			}
			//printf("%d %d\n", p, tmp);
			while(ans % p != tmp) {
				ans = ans + mul;
			}
			mul *= p;
		}
		cout << ans << endl;
	}
}
