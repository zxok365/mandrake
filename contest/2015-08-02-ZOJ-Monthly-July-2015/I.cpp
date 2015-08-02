#include <cstdio>
#include <iostream>

using namespace std;

const int N = 1111;

unsigned long long n, result[N], element[N];
int a, b, s, t;

bool check(int round, int length) {
	if (length > n) {
		return false;
	}
	length -= round;
	for (int i = 1; i <= length; ++i) {
		result[i] = i;
	}
	for (int repeat = 0; repeat < round; ++repeat) {
		element[1] = 1;
		for (int i = 1; i <= length; ++i) {
			element[i + 1] = element[i] + result[i];
		}
		length++;
		for (int i = 1; i <= length; ++i) {
			if (element[i] < 1 || element[i] > n) {
				return false;
			}
			result[i] = element[i];
		}
	}
	return true;
}

void solve(void) {
	static bool first = true;
	if (first) {
		first = false;
	} else {
		cout << endl;
	}
	if (!check(a, s)) {
		cout << "-1" << endl;
	} else {
		for (int i = 1; i <= s; ++i) {
			cout << result[i];
			if (i == s) {
				cout << endl;
			} else {
				cout << " ";
			}
		}
	}
	
	if (!check(b, t)) {
		cout << "-1" << endl;
	} else {
		for (int i = 1; i <= t; ++i) {
			cout << n - result[i] + 1;
			if (i == t) {
				cout << endl;
			} else {
				cout << " ";
			}
		}
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	for (; cin >> n >> a >> b >> s >> t; solve());
}
