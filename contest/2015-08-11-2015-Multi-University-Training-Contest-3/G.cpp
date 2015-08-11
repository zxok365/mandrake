#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

const long long MOD = 998244353;

typedef long long LL;

LL times(LL x, LL y)
{
	return x * y % MOD;
}

LL pow(LL x, LL y)
{
	LL ans = 1;
	for(; y; y >>= 1, x = times(x, x))
		if(y & 1)
			ans = times(ans, x);
	return ans;
}

const int N = 100005;

long long fact[N], inverse[N], f[N];

int main() {
	fact[0] = 1;
	for(int i = 1; i < N; i++)
		fact[i] = times(fact[i - 1], i);
	inverse[0] = 1;
	for(int i = 1; i < N; i++)
		inverse[i] = pow(fact[i], MOD - 2);
		
	f[0] = f[1] = 1;
	long long a = 0, b = 0, c = 0;
	for (long long i = 0; i < 2; ++i) {
		(a += f[i] * inverse[i] % MOD) %= MOD;
		(b += (i * f[i] % MOD) * inverse[i] % MOD) %= MOD;
		(c += ((i * i % MOD) * f[i] % MOD) * inverse[i] % MOD) %= MOD;
	}
	for (long long i = 2; i < N; ++i) {
		f[i] = ((i * i % MOD) * a % MOD - (2 * i % MOD) * b % MOD + c % MOD) * fact[i - 1] % MOD;
		(f[i] += MOD) %= MOD;
		(a += f[i] * inverse[i] % MOD) %= MOD;
		(b += (i * f[i] % MOD) * inverse[i] % MOD) %= MOD;
		(c += ((i * i % MOD) * f[i] % MOD) * inverse[i] % MOD) %= MOD;
	}
	
	int p;
	while(scanf("%d", &p) == 1) {
		printf("%d\n", (int)f[p]);
	}
	return 0;
}
		
