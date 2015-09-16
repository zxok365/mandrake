#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<cstring>

using namespace std;

const int N = 205;
const double eps = 1e-8;
int S[N], num[N], a[10005];

pair<double, int> get(int L, int R, double need){
	pair<double, int> ans = make_pair(10000000.0, 260);
	for(int i = L; i <= R - 1; i++){
		double t = fabs(1. * (S[R] - S[i]) - need) + fabs(1. * (S[i] - S[L - 1]) - need);
		if(t > ans.first - eps) continue;
		ans = make_pair(t, i);
	}
	return ans;
}


void work(){
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
		a[i]++;
	}
	sort(a + 1, a + 1 + n);
	for(int i = 1; i <= 161; i++)
		num[i] = 0;
	for(int i = 1; i <= n; i++)
		num[a[i]]++;
	for(int i = 1; i <= 161; i++)
		S[i] = S[i - 1] + num[i];
	double Min = 10000000000000000.0;
	pair<int, pair<int, int> > t = make_pair(210, make_pair(210, 210));
	for(int i = 2; i <= 160; i++){
		pair<double, int> t1 = get(1, i, 1. * n / 4.);
		pair<double, int> t2 = get(i + 1, 161, 1. * n / 4.);
		double now = t1.first + t2.first;
		if(now > Min + eps) continue;
		if(fabs(now - Min) < eps){
			t = min(t, make_pair(t1.second, make_pair(i, t2.second)));
		}
		else{
			t = make_pair(t1.second, make_pair(i, t2.second));
			Min = now;
		}
	}
	printf("%d %d %d\n", t.first - 1, t.second.first - 1, t.second.second - 1);
}

int main(){
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++){
		printf("Case %d: ", i);
		work();
	}
	return 0;
}
