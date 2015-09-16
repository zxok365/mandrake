#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 100005;

pair<int, int> tmp[N];

typedef unsigned long long ULL;
typedef long long LL;
const long long MOD = 1000000007;

int test = 0;

void work(){
	int n;
	scanf("%d", &n);
	ULL res = 0;
	for(int i = 1; i <=n; i++){
		scanf("%d%d", &tmp[i].first, &tmp[i].second);
		res += (ULL)tmp[i].second;
	}
	sort(tmp + 1, tmp + 1 + n);
	reverse(tmp + 1, tmp + 1 + n);
	ULL ans = 0;
	for(int i = 1; i <= n; i++){
		ans += (ULL)tmp[i].second * res;
		res -= (ULL)tmp[i].second;
	}
	LL CC = 1;
	for(int i = 2; i <= n; i++)
		CC = (CC * (tmp[i].second + 1)) % MOD;
	printf("Case %d: ", ++test);
	cout << ans << " " << CC << endl;
	return ;
}

int main(){
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++)
		work();
	return 0;
}
