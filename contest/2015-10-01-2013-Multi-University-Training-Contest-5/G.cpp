#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>

using namespace std;

const int N = 210;

int n;

vector<int> digit[22];

int gg[4][3][3], fh[N], a[N];
double f[N][3], p[N];
char type[N];

void work() {
	for(int i = 1; i <= n + 1; i++)
		scanf("%d", &a[i]);
	for(int i = 1; i <= n; i++) {
		scanf("%s", type + 1);
		if(type[1] == '|')
			fh[i] = 1;
		if(type[1] == '&')
			fh[i] = 2;
		if(type[1] == '^')
			fh[i] = 3;
	}
	for(int i = 1; i <= n; i++) 
		scanf("%lf", &p[i]);	
	for(int i = 1; i <= 21; i++)
		digit[i].clear();
	for(int i = 1; i <= 21; i++) {
		digit[i].push_back(0);
		for(int j = 2; j <= n + 1; j++)
			digit[i].push_back(a[j] % 2), a[j] /= 2;
	}
	double ans = 0;
	for(int pos = 1; pos <= 21; pos++) {
		for(int i = 0; i <= n; i++)
			for(int j = 0; j <= 1; j++)
				f[i][j] = 0;
		f[0][a[1] % 2] = 1; a[1] /= 2;
		for(int i = 1; i <= n; i++) 
			for(int j = 0; j <= 1; j++) {
				double res = 1. - p[i];
				for(int k = i - 1; k >= 0; k--) {
					for(int l = 0; l <= 1; l++) {
						if(gg[fh[i]][l][digit[pos][i]] != j) continue;
						f[i][j] += res * f[k][l];
					}
					res *= (p[k]);
				}
			}
		double CC = 0;
		double res = 1;
		for(int i = n; i >= 0; i--) {
			CC += f[i][1] * res;
			res *= p[i];
		}
		ans += 1. * (1 << (pos - 1)) * CC;
	}
	printf("%.6f\n", ans);
	return ;		
}

int main() {
	for(int i = 0; i <= 1; i++)
		for(int j = 0; j <= 1; j++)
			gg[1][i][j] = i | j;
	for(int i = 0; i <= 1; i++)
		for(int j = 0; j <= 1; j++)
			gg[2][i][j] = i & j;
	for(int i = 0; i <= 1; i++)
		for(int j = 0; j <= 1; j++)
			gg[3][i][j] = i ^ j;
	int test = 0;
	while(scanf("%d", &n) == 1) 
		printf("Case %d:\n", ++test), work();
	return 0;
}
