#include <cstdio>

const int N = 22222;

int m;
int child[N][3];

int calc(int a, int b) {
	return a << m | b;
}

void addEdge(int x, int y, int a) {
	child[x][a] = y;
}

int main(void) {
	scanf("%d", &m);
	
	int node = m * (1 << m) + 1;
	int stay = node - 1;
	
	for (int i = 0; i < 3; ++i) {
		addEdge(stay, stay, i);
	}
	
	for (int i = 0; i < m; ++i) {
		for (int mask = 0; mask < (1 << m); ++mask) {
			if (mask >> i & 1) {
				addEdge(calc(i, mask), stay, 0);
				addEdge(calc(i, mask), calc((i + 1) % m, mask) & ~(1 << i), 2);
			} else {
				addEdge(calc(i, mask), stay, 2);
				addEdge(calc(i, mask), calc((i + 1) % m, mask) | (1 << i), 0);
			}
			if (i == m - 1 || (mask >> i & 1) || (mask >> i + 1 & 1)) {
				addEdge(calc(i, mask), stay, 1);
			} else {
				addEdge(calc(i, mask), calc((i + 1) % m, mask) | (1 << i + 1), 1);
			}
		}
	}
	
	printf("%d 1\n1 1\n", node);
	for (int i = 0; i < node; ++i) {
		for (int j = 0; j < 3; ++j) {
			printf("%d%s", child[i][j] + 1, (j == 2) ? "\n" : " ");
		}
	}
}
