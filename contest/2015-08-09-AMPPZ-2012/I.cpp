#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>

using namespace std;

#define N 1000005

int f[N], a[N], stack[N];

int find(int x) {
	if (f[x] != x) {
		f[x] = find(f[x]);
	}
	return f[x];
}

void merge(int x, int y)
{
	if (x == y) {
		return;
	}
	if (x > y) {
		std::swap(x, y);
	}
	f[y] = x;
}

int main()
{
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
		
	for(int i = 1; i <= n; i++)
		f[i] = i;
		
	int top = 0;
	stack[++top] = a[1];
	for(int i = 2; i <= n; i++) {
		if (a[i] > stack[top]) {
			stack[++top] = a[i];
		} else {
			int number = stack[top];
			while(top && stack[top] >= a[i]) {
				merge(find(stack[top]), find(a[i]));
				top--;
			}
			stack[++top] = number;
		}
	}
	
	static pair<int, int> tmp[N];
	for(int i = 1; i <= n; i++)
		tmp[i] = make_pair(find(i), i);
	
	sort(tmp + 1, tmp + 1 + n);
	int answer = 0;
	for (int i = 1, j; i <= n; i = j) {
		for (j = i; j <= n && tmp[j].first == tmp[i].first; ++j);
		answer++;
	}
	printf("%d\n", answer);
	for (int i = 1, j; i <= n; i = j) {
		for (j = i; j <= n && tmp[j].first == tmp[i].first; ++j);
		printf("%d", j - i);
		for (j = i; j <= n && tmp[j].first == tmp[i].first; ++j) {
			printf(" %d", tmp[j].second);
		}
		puts("");
	}
	return 0;
}			
