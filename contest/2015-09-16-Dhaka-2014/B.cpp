#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
long long ones[70];

void dfs(long long number, vector<long long> &answer, long long base, long long pos) {
	if (number <= 0) return;
	long long digit = number % 2;
	if (digit >= 1) answer[pos] += base;
	long long tmp = pos;
	for (long long rest = number / 2; rest; rest /= 2) {
		tmp++;
		if (rest % 2) answer[tmp] += (digit + 1) * base;
	}
	
	answer[pos] += (number / 2) * base;
	dfs(number / 2 - 1, answer, base * 2, pos + 1);
}

void solve() {
	long long a, b;
	scanf("%lld %lld", &a, &b);
	a--;
	long long sum = b - a;
	vector<long long> answer1 (70, 0);
	vector<long long> answer2 (70, 0);
	dfs(a, answer1, 1, 0);
	dfs(b, answer2, 1, 0);
	for (long long i = 0; i <= 62; i++)
		ones[i] = answer2[i] - answer1[i];
	long long ornum = 0, andnum = 0;
	for (long long i = 0; i <= 62; i++) {
		if (ones[i] > 0) ornum += (1LL << i);
		if (ones[i] == sum) andnum+= (1LL << i);
	}
	printf("%lld %lld\n", ornum, andnum);
}

int main() {
	long long test;
	scanf("%lld", &test);
	for (long long i = 1; i <= test; i++) {
		static long long counter = 0;
		printf("Case %lld: ", ++counter);
		solve();
	}
	return 0;
}
