#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

const int LIMIT = 20000000;

long long w, h;
long double f[LIMIT + 10];

void solve() {
	if (h == 0 && w % 8 != 0) {
		puts("Situation Impossible.");
		return;
	}
	
	long long l = max(0LL, (w - h * 7 + 7) / 8) + h - 1;
	long long r = w / 8 + h;
	
	long double coe = (r > LIMIT) ? (log(r) - log(l)) : (f[r] - f[l]);
	long double ans = (((long double)w + h) / (long double)(r - l)) * coe;
	
	printf("On Average Bob Reaches Round %.2f\n", (double)ans);
}

int main() {
	for(int i = 1; i <= LIMIT; i++)
		f[i] = f[i - 1] + 1. / (long double)i;
		
	for (int tests = 1; cin >> w >> h && (w || h); tests++) {
		cout << "Case " << tests << ":" << endl;
		solve();
	}
	return 0;
}
