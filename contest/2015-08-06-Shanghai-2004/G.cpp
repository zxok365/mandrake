#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 24;

const int number[8][7] = {
{0, 2, 6, 11, 15, 20, 22},
{1, 3, 8, 12, 17, 21, 23},
{10, 9, 8, 7, 6, 5, 4},
{19, 18, 17, 16, 15, 14, 13},
{23, 21, 17, 12, 8, 3, 1},
{22, 20, 15, 11, 6, 2, 0},
{13, 14, 15, 16, 17, 18, 19},
{4, 5, 6, 7, 8, 9, 10}
};

bool read(int *element) {
	scanf("%d", &element[0]);
	if (element[0] == 0) {
		return false;
	}
	for (int i = 1; i < 24; ++i) {
		scanf("%d", &element[i]);
	}
	for (int i = 0; i < 24; ++i) {
		element[i]--;
	}
	return true;
}

int limit, size;
int element[N], answer[N * N * N], target[N];

int counter[3];
__inline int dist(int *element) {
	for (int i = 0; i < 3; ++i) {
		counter[i] = 0;
	}
	for (int i = 6; i < 9; ++i) {
		counter[element[i]]++;
	}
	for (int i = 11; i < 13; ++i) {
		counter[element[i]]++;
	}
	for (int i = 15; i < 18; ++i) {
		counter[element[i]]++;
	}
	int result = 8;
	for (int i = 0; i < 3; ++i) {
		result = min(result, 8 - counter[i]);
	}
	return result;
}

bool dfs(int dep, int *element) {
	if (dist(element) == 0) {
		size = dep;
		for (int i = 0; i < 24; ++i) {
			target[i] = element[i];
		}
		return true;
	}
	if (dep + dist(element) > limit) {
		return false;
	}
	
	int sequence[N];
	for (int dir = 0; dir < 8; ++dir) {
		answer[dep] = dir;
		
		for (int i = 0; i < 24; ++i) {
			sequence[i] = element[i];
		}
		for (int i = 0; i < 7; ++i) {
			sequence[number[dir][i]] = element[number[dir][(i + 1) % 7]];
		}
		if (dfs(dep + 1, sequence)) {
			return true;
		}
	}
	return false;
}

void solve(void) {
	if (dist(element) == 0) {
		puts("No moves needed");
		printf("%d\n", element[6] + 1);
		return;
	}
	
	for (limit = 1; !dfs(0, element); limit++);
	
	for (int i = 0; i < size; ++i) {
		putchar('A' + answer[i]);
	}
	puts("");
	printf("%d\n", target[6] + 1);
}

int main(void) {
	for (; read(element); solve());
}
