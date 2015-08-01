#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define N 200005

int w[N], c[N];
int S[N], C[N];

int main()
{
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	for(int i = 1; i <= n; i++)
		scanf("%d %d", &w[i], &c[i]);
	for(int i = 1; i <= n; i++)
		S[i] = S[i - 1] + w[i],
		C[i] = C[i - 1] + c[i];
	int l = n - m + 1, r = n;
	int CC, H, T, base = 0;
	CC = H = T = 0;
	while(1)
	{
		if(S[r] - S[l - 1] > S[l - 1] * k) break;
		int left = 1, right = l - 1;
		int ans;
		while(left <= right)
		{
			int mid = left + right >> 1;
			if((S[l - 1] - S[mid - 1]) * k >= S[r] - S[l - 1])
			{
				ans = mid;
				left = mid + 1;
			} 
			else
				right = mid - 1;
		}
		int now = base + C[ans - 1];
		if(now > CC)
			CC = now, H = n - r,T = ans - 1;
		base += c[r];
		l--, r--;
	}
	printf("%d %d\n", H + T, CC);
	for(int i = 1; i <= H; i++)
		printf("H");
	for(int i = 1; i <= T; i++)
		printf("T");
	puts("");
	return 0;
}
