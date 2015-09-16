#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int MAXN = 1111111;
char s[MAXN];
int n;
int fa[30];

void modify(char a, char b) {
	for (int i = 0; i < 26; i++) {
		if (fa[i] == a - 'A') fa[i] = b - 'A';
	}
}

void solve() {
	scanf("%s", s);
	scanf("%d", &n);
	for (int i = 0; i < 26; i++) fa[i] = i;
	for (int i = 1; i <= n; i++) {
		char s1[3], s2[3];
		scanf("%s %s", s1, s2);
		modify(s2[0], s1[0]);
	}
	
	int len = strlen(s);
	
	for (int i = 0; i < len; i++) {
		if (s[i] >= 'A' && s[i] <= 'Z') {
			int tmp = s[i] - 'A';
			putchar(fa[tmp] + 'A');
		}
		else putchar(s[i]);
	}
	puts("");
}

int main() {
	int test;
	scanf("%d", &test);
	for (int i = 1; i <= test; i++) {
		solve();
	}
	return 0;
}
