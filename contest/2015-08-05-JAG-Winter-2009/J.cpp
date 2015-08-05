#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <climits>

using namespace std;

const int N = 1111;

int n;
pair<long long, long long> a[N]; 
long long best[N][N];

long long dfs(int left, int right) {
	long long &result = best[left][right];
	if (result) {
		return result;
	}
	if (left == right) {
		return result = 0;
	}
	result = LONG_LONG_MAX;
	for (int mid = left; mid < right; ++mid) {
		result = min(result, dfs(left, mid) + dfs(mid + 1, right) + a[mid].second - a[right].second + a[mid + 1].first - a[left].first);
	}
	return result;
}

int main() {
	ios::sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> a[i].first >> a[i].second;
	}
	cout << dfs(1, n) << endl;
	return 0;
}
