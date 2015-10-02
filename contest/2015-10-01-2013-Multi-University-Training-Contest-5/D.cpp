#include <cstdio>
#include <cstdlib>
#include <algorithm>

const int N = 5000010;

int n;
int answer[N];

int solve(int n) {
	if (!answer[n]) {
		if (n % 2 == 0) {
			answer[n] = n / 6 * 2 + 1;
		} else {
			answer[n] = (n - 3) / 6 * 2 + 2;
		}
		
		for (int i = 2; i * i <= n; ++i) {
			if (n % i == 0) {
				if (i * i == n) {
					answer[n] -= solve(i);
				} else {
					answer[n] -= solve(i) + solve(n / i);
				}
			}
		}
	}
	return answer[n];
}

void solve(void) {
	scanf("%d", &n);
	if (n % 2 == 0) {
		puts("0");
		return;
	}
	
	n = (n + 3) / 2;
	
	if (n % 3 == 0) {
		puts("0");
		return;
	}
/*	
	int counter = 0;
	for (int i = 1; i <= n; ++i) {
		if (std::__gcd(i, n) == 1 && (i + n) % 3 == 0) {
			counter++;
		}
	}
	printf("%d ", counter);
*/
	printf("%d\n", solve(n));

}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
