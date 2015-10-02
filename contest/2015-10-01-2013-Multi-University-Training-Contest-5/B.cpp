#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>


using namespace std;
const int N = 111111;
int match[N], fail[N];
char str[N], s[N];
char origin[N];
void build(char *pattern) {
	int length = (int)strlen(pattern + 1);
	fail[0] = -1;
	for (int i = 1, j; i <= length; i++) {
		for (j = fail[i - 1]; j != -1 && pattern[i] != pattern[j + 1]; j = fail[j]);
		fail[i] = j + 1;
	}
}

int get(char *text, char *pattern) {
	int length = (int)strlen(text + 1);
	for (int i = 1, j; i <= length; i++) {
			for (j = match[i - 1]; j != -1 && text[i] != pattern[j + 1];j = fail[j]);
			match[i] = j + 1;
	}
	int target = (int)strlen(pattern + 1);
	
	for (int i = 1; i <= length; i++) {
		if (match[i] == target) return 1;
	}
	return 0;
}
void solve() {
	int len = strlen(str + 1);
	vector<pair<char, int> > vec;
	for (int i = 1; i <= len; i++) {
		vec.push_back(make_pair(str[i], i));
	}
	int now = 0;
	sort(vec.begin(), vec.end());
	for (int p = 0; now <= len; p = vec[p].second - 1) {
		origin[++now] = vec[p].first;
	}
	origin[++now] = 0;
	
	int m;
	scanf("%d", &m);
	for (int t = 0; t < m; t++) {
		scanf("%s", s + 1);
		build(s);
		if (get(origin, s)) {
			puts("YES");
		} else {
			puts("NO");
		}
	}
}
int main() {
	while (scanf("%s", str + 1) != EOF) {
		solve();
	}
}
