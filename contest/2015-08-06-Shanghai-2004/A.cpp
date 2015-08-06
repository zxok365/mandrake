#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

class Point {
public:
	int x, y, type;
	
	Point() {}
	
	Point(int x, int y) : x(x), y(y) {}
	
	void read() {
		scanf("%d%d%d", &x, &y, &type);
	}
};

__inline int det(const Point &a, const Point &b) {
	return a.x * b.y - b.x * a.y;
}

__inline bool compare(const Point &a, const Point &b) {
	return det(a, b) > 0;
}

const int N = 1111;

int n;
Point a[N];

void solve(void) {
	for (int i = 0; i < n; ++i) {
		a[i].read();
	}
	
	int result = 0;
	for (int pivot = 0; pivot < n; ++pivot) {
		vector<Point> list;
		for (int i = 0; i < n; ++i) {
			if (i == pivot) {
				continue;
			}
			static Point p;
			p.x = a[i].x - a[pivot].x;
			p.y = a[i].y - a[pivot].y;
			p.type = a[i].type;

			if (p.y < 0 || (p.y == 0 && p.x < 0)) {
				p.x = -p.x;
				p.y = -p.y;
				p.type ^= 1;
			}
			
			list.push_back(p);
		}
		
		sort(list.begin(), list.end(), compare);
		
		int counter0 = 0;
		for (int i = 0; i < (int)list.size(); ++i) {
			counter0 += (list[i].type == 0);
		}
		
		int counter1 = 0;
		for (int i = 0, j; i < (int)list.size(); i = j) {
			int counter = 0;
			for (j = i; j < (int)list.size() && det(list[i], list[j]) == 0; ++j) {
				if (list[j].type == 1) {
					counter1++;
				} else {
					counter++;
				}
			}
			result = max(result, counter0 + counter1 + 1);
			result = max(result, (int)list.size() - counter0 - counter1 + j - i + 1);
			counter0 -= counter;
		}
	}
	printf("%d\n", result);
}

int main(void) {
	for (; scanf("%d", &n) && n; solve());
}
