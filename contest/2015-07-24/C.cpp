#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int T;
int main(){
	scanf("%d", &T);
	for (int tt = 1; tt <= T; tt++)
	{
		int a1, b1, c1, d1, e1, tag;
		scanf("%d%d%d%d%d%d", &a1, &b1, &c1, &d1, &e1, &tag);
		int now = a1 + b1 + c1 + d1 + e1;
		int ans = 0;
		if (now <= 0 && now < tag)
		{
			printf("Case #%d: %d\n",tt, -1);
			continue;
		}
		while (now < tag)
		{
			now *= 2;
			ans++;
		}
		printf("Case #%d: %d\n", tt, ans);
	}
	
	return 0;
}
