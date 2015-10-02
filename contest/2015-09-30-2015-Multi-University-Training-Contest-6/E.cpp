#include <cstdio>
#include <cstring>

const long long mod = 1e9 + 7;
const int N = 1e6 + 100;

int n;
char text[N];
long long f[N], g[N], match[N], prev[N];
long long answer[N];

void solve(void) {
	scanf("%s", text + 1);
	n = (int)strlen(text + 1);
	
	for (int i = 0; i <= n + 1; ++i) {
		f[i] = g[i] = match[i] = prev[i] = answer[i] = 0;
	}
	
	static int stack[N];
	int top = 0;
	
	for (int i = 1; i <= n; ++i) {
		if (text[i] == '(') {
			stack[top++] = i;
		} else if (top) {
			match[i] = stack[top - 1];
			match[stack[top - 1]] = i;
			
			top--;
			if (top) {
				prev[match[i]] = stack[top - 1];
			}
		}
	}
	
	for (int i = n; i >= 1; --i) {
		if (text[i] == '(' && match[i]) {
			f[i] = f[match[i] + 1] + 1;
		}
	}
	for (int i = 1; i <= n; ++i) {
		if (text[i] == ')' && match[i]) {
			g[i] = g[match[i] - 1] + 1;
		}
	}
	
	for (int i = 1; i <= n; ++i) {
		if (text[i] == '(' && match[i]) {
			answer[i] = (answer[prev[i]] + f[i] * g[match[i]] % mod) % mod;
			answer[match[i]] = answer[i];
		}
	}
	long long result = 0;
	for (int i = 1; i <= n; ++i) {
		result += 1LL * i * answer[i] % mod;
	}
	printf("%lld\n", result);
}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
