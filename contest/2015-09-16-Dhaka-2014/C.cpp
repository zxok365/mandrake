#include <cstdio>
#include <algorithm>
#include <vector>

const long long mod = 21092013;
const long long inverse = (mod + 1) / 2;

const int N = 222222;

class EdgeList {
public:
	int size;
	int last[N], succ[N], other[N];
	
	void clear(int n) {
		size = 0;
		std::fill(last + 1, last + n + 1, 0);
	}
	
	void add(int x, int y) {
		size++;
		succ[size] = last[x];
		other[size] = y;
		last[x] = size;
	}
} e;

int n;
int father[N], max[N], min[N];
long long answer[N];
long long ways[N][51];

__inline void update(long long &x, const long long &y) {
	(x += y % mod) %= mod;
}

void solve(void) {
	scanf("%d", &n);
	e.clear(n);
	
	for (int i = 1; i < n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		e.add(x, y);
		e.add(y, x);
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &min[i]);
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &max[i]);
	}
	
	int bound = 50;
	
	std::vector<int> queue;
	queue.push_back(1);
	father[1] = 0;
	for (int head = 0; head < (int)queue.size(); ++head) {
		int x = queue[head];
		for (int i = e.last[x]; i; i = e.succ[i]) {
			int y = e.other[i];
			if (y == father[x]) {
				continue;
			}
			father[y] = x;
			queue.push_back(y);
		}
	}
	for (int index = n - 1; index >= 0; --index) {
		int x = queue[index];
		
		for (int val = 1; val <= bound; ++val) {
			ways[x][val] = 0;
			
			long long counter = max[x] / val - (min[x] + val - 1) / val + 1;
			
			update(ways[x][val], counter);
			
			for (int i = e.last[x]; i; i = e.succ[i]) {
				int y = e.other[i];
				if (y == father[x]) {
					continue;
				}
				update(ways[x][val], counter * ways[y][val] % mod);
			}
		}
	}
	
	for (int val = 1; val <= bound; ++val) {
		answer[val] = 0;
		
		for (int x = 1; x <= n; ++x) {
			long long counter = max[x] / val - (min[x] + val - 1) / val + 1;
			
			update(answer[val], counter);
			
			long long sum1 = 0, sum2 = 0;
			for (int i = e.last[x]; i; i = e.succ[i]) {
				int y = e.other[i];
				if (y == father[x]) {
					continue;
				}
				long long total = ways[y][val];
				update(answer[val], counter * total % mod);
				update(sum1, total);
				update(sum2, total * total % mod);
			}
			
			long long number = (sum1 * sum1 - sum2) % mod;
			update(answer[val], (counter * number % mod) * inverse % mod);
		}
	}
	
	for (int i = bound; i >= 1; --i) {
		for (int j = i + i; j <= bound; j += i) {
			update(answer[i], -answer[j]);
		}
	}
	
	for (int i = 1; i <= 50; ++i) {
		answer[i] %= mod;
		answer[i] += mod;
		answer[i] %= mod;
		printf("%d: %d\n", i, (int)answer[i]);
	}
}

int main(void) {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; ++i) {
		printf("Case %d:\n", i);
		solve();
	}
}
