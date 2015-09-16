#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>

using namespace std;

const int N = 15;
const double pi = acos(-1.);

double a[N];
double num[N * 2], coe[N * 2];

double calc(double k[], double t, int len){
	double now = 1., ans = 0.;
	for(int i = 0; i <= len; i++){
		ans += now * k[i];
		now *= t;
	}
	return ans;
}
	

double get(double x, double rad){
	return x * x * sin(rad) / 2.;
}

void work(){
	int n;
	scanf("%d", &n);
	for(int i = n; i >= 0; i--)	
		scanf("%lf", &a[i]);
	double l, r;
	scanf("%lf%lf", &l, &r);
	int sl, sr;
	scanf("%d%d", &sl, &sr);
	for(int i = 0; i <= 2 * n; i++)
		num[i] = 0;
	for(int i = 0; i <= n; i++)
		for(int j = 0; j <= n; j++)
			num[i + j] += a[i] * a[j];
	
	for(int i = 0; i <= 2 * n; i++)
		coe[i + 1] = num[i] / (i + 1);
	
	double tr_v = calc(coe, r, 2 * n + 1) - calc(coe, l, 2 * n + 1);
	
	tr_v *= pi;
	
	double ap_v = 0;
	double rad = 2. * pi / (double)sl;
	double step = (r - l) / sr;
	for(int i = 1; i <= sr; i++){
		double st = l + (i - 1) * step;
		double ed = l + i * step;
		
		st = calc(a, st, n); ed = calc(a, ed, n);
		
		
		st = sl * get(st, rad);
		ed = sl * get(ed, rad);

		ap_v += ((st + ed + sqrt(st * ed)) / 3. * step);
	}
	printf("%.4f\n", fabs(ap_v - tr_v) / tr_v * 100.);
	return ;
}

int main(){
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++)
		printf("Case %d: ", i), work();
	return 0;
}
