#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>

using namespace std;

const int N = 55;
const int MO = (int)1e9 + 7;

struct Matrix {
	long long g[N][N];
}mat;

int n, m;
int a[N];
Matrix mul(Matrix m1, Matrix m2) {
	Matrix tmp;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			tmp.g[i][j] = 0;
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) {
				tmp.g[i][j] += m1.g[i][k] * m2.g[k][j];
				if (tmp.g[i][j] > MO) tmp.g[i][j] %= MO;
			}
	return tmp;
}

Matrix matrix_pow(int cnt) {
	Matrix tmp = matrix_pow(cnt / 2);
	if (cnt & 1) {
		return mul(mul(tmp, tmp), mat);
	}
	else 
		return mul(tmp, tmp);
}

bool check(int p1, int p2) {
	char s1[20], s2[20];
	sprintf(s1 + 1, "%d", a[p1]);
	sprintf(s2 + 1, "%d", a[p2]);
	//cout << s1 + 1 << " " << s2 + 1 << endl;
	int len1 = strlen(s1 + 1);
	int len2 = strlen(s2 + 1);
	if (min(len1, len2) < 2) return 0;
	int len = min(len1, len2);
	
	for (int i = 2; i <= len; i++) {
		int flg = 1;
		for (int j = 1; j <= i; j++) {
			if (s1[len1 - i + j] != s2[j]) flg = 0;
		}
		if (flg) return 1; 
	}
	return 0;
}
void solve() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	sort(a + 1 , a + n + 1);
	n = unique(a + 1, a + n + 1) - (a + 1);
	//cout << n << endl;
	
	if (n == 0 || m == 0) {
		puts("0");
		return;
	}

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			mat.g[i][j] = 0;
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (check(i, j)) mat.g[i][j] = 1;
		}
	}
		
	if (m == 1) {
		printf("%d\n", (int)n % MO);
		return;
	}
	
	Matrix ans_matrix = mat;
	for (int i = m - 2; i > 0; i >>= 1) {
		if (i & 1) {
			ans_matrix = mul(ans_matrix, mat);
		}
		mat = mul(mat, mat);
	}
	
	long long ans = 0;
	
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= n; j++) {
			ans += ans_matrix.g[i][j];
			ans %= MO;
		}
	
	printf("%d\n", (int)ans);
}

int main() {
	int T;
	scanf("%d", &T);
	for (int i = 1; i <= T; i++) {
		solve();
	}
}

