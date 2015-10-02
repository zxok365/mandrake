#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

const double eps = 1e-8;
const double INF = 1e50;

__inline int sgn(const double &x) {
	return x < -eps ? -1 : x > eps;
}

typedef std::pair<double, double> Interval;

int n;
double l, m, r;
std::vector<Interval> intervals[2];

void insert(const Interval &a, const Interval &b, int now) {
	Interval result = Interval(a.first + b.first, a.second + b.second);
	if (result.second < -m - eps || result.first > m + eps) {
		return;
	}
	result.first = std::max(result.first, -m);
	result.second = std::min(result.second, m);
	if (result.second - result.first > -eps) {
		intervals[now].push_back(result);
	}
}

int main(void) {
	int now = 0;
	intervals[0].push_back(Interval(0, 0));

	scanf("%d%lf%lf%lf", &n, &l, &m, &r);
	for (double w; n--; ) {
		scanf("%lf", &w);
		
		intervals[now ^ 1].clear();
		for (int sign = -1; sign <= 1; sign += 2) {
			Interval interval = Interval(sign * w * r, sign * w * l / 2);
			if (interval.first > interval.second) {
				std::swap(interval.first, interval.second);
			}
			for (int i = 0; i < (int)intervals[now].size(); ++i) {
				insert(interval, intervals[now][i], now ^ 1);
			}
		}
		
		now ^= 1;
		std::sort(intervals[now].begin(), intervals[now].end());
/*		
		for (int i = 0; i < (int)intervals[now].size(); ++i) {
			printf("%f %f\n", intervals[now][i].first, intervals[now][i].second);
		}
		puts("");
*/		
		std::vector<Interval> list;
		Interval interval = Interval(-INF, -INF);
		for (int i = 0; i < (int)intervals[now].size(); ++i) {
			if (interval.second > intervals[now][i].first - eps) {
				interval.second = std::max(interval.second, intervals[now][i].second);
			} else {
				if (interval.first + interval.second > -INF) {
					list.push_back(interval);
				}
				interval = intervals[now][i];
			}
		}
		if (interval.first + interval.second > -INF) {
			list.push_back(interval);
		}
		
		if (list.empty()) {
			puts("No");
			return 0;
		}
		
		intervals[now] = list;
/*
		for (int i = 0; i < (int)intervals[now].size(); ++i) {
			printf("%f %f\n", intervals[now][i].first, intervals[now][i].second);
		}
		puts("");
*/	}
	puts("Yes");
}
