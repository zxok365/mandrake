#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 222222;
const int N = 26;

struct Palindromic_Tree {
	int next[MAXN][N];
	int fail[MAXN];
	int cnt[MAXN];
	int num[MAXN];
	int len[MAXN];
	int S[MAXN];
	int last;
	int n;
	int p;
	
	int newnode(int l) {
		for (int i = 0; i < N; ++i) next[p][i] = 0;
		cnt[p] = 0;
		num[p] = 0;
		len[p] = l;
		return p++;
	}
	
	void init() {
		p = 0;
		newnode(0);
		newnode(-1);
		last = 0;
		n = 0;
		S[n] = -1;
		fail[0] = 1;
	}
	
	int get_fail(int x) {
		while (S[n - len[x] - 1] != S[n]) x = fail[x];
		return x;
	}
	
	void add(int c) {
		c -= 'A';
		S[++n] = c;
		int cur = get_fail(last);
		if (!next[cur][c]) {
			int now = newnode(len[cur] + 2);
			fail[now] = next[get_fail(fail[cur])][c];
			next[cur][c] = now;
			num[now] = num[fail[now]] + 1;
		}
		last = next[cur][c];
		cnt[last]++;
	}
	
	int count() {
		int answer = 0;
		for (int i = 0; i < p; ++i) {
			answer += (cnt[i] != 0);
		}
		return answer;
	}
} solver;

char text[5555];

int main() {
	scanf("%s", text);
	int length = (int)strlen(text);
	
	solver.init();
	for (int i = 0; i < length; ++i) {
		solver.add(text[i]);
	}
	printf("%d\n", solver.count());
}
