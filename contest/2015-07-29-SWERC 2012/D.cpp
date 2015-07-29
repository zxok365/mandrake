#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <cassert>

using namespace std;

const int N = 2222;

char mapping[N];
string buffer, str;

int k;
int counter[N];
char symbol[N];
int best[150][150][21];

int prepare() {
	int n = 0;
	
	stringstream os(buffer);
	for (char ch; os >> ch; ) {
		int num;
		os >> num;
		counter[n] = num;
		symbol[n++] = ch;
	}
	
	int result = 0;
	if (n > 1) {
		if (symbol[0] == mapping[symbol[n - 1]]) {
			int number = min(counter[0], counter[n - 1]);

			if (symbol[0] == 'C' || symbol[0] == 'G') {
				number = min(number, k);
				k -= number;
			}
			
			result += number;
			counter[0] -= number;
			counter[n - 1] -= number;
		}
		
		int rest = 0;
		for (int i = 1; i < n - 1; ++i) {
			rest += counter[i];
		}
		
		counter[0] = min(counter[0], rest);
		counter[n - 1] = min(counter[n - 1], rest);
	}
	
	str = "";
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < counter[i]; ++j) {
			str += symbol[i];
		}
	}
	
	return result;
}

int dfs(int left, int right, int k) {
	if (left >= right) {
		return 0;
	}
	int &result = best[left][right][k];
	if (result >= 0) {
		return result;
	}
	result = dfs(left + 1, right, k);
	if (str[left] == 'C' || str[left] == 'G') {
		k--;
	}
	if (k < 0) {
		return result;
	}
	for (int i = left + 1; i <= right; ++i) {
		if (mapping[str[i]] == str[left]) {
			for (int j = 0; j <= k; ++j) {
				result = max(result, dfs(left + 1, i - 1, j) + dfs(i + 1, right, k - j) + 1);
			}
		}
	}
	return result;
}	

void solve(void) {
	memset(best, 0xFF, sizeof(best));
	cin >> buffer >> k;

	int result = prepare();
	result += dfs(0, (int)str.length() - 1, k);
	cout << result << endl;
}

int main(void) {
	mapping['A'] = 'U';
	mapping['C'] = 'G';
	mapping['G'] = 'C';
	mapping['U'] = 'A';

	ios::sync_with_stdio(false);
	int tests;
	cin >> tests;
	for (int i = 1; i <= tests; ++i) {
		cout << "Case " << i << ": ";
		solve();
	}
}
