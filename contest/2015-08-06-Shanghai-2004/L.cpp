#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

__inline long long absll(const long long &x) {
	return x > 0 ? x : -x;
}

class Point {
public:
	long long x, y;
	
	Point() {}
	
	Point(const long long &x, const long long &y) : x(x), y(y) {}
	
	void read() {
		int x, y;
		scanf("%d%d", &x, &y);
		this->x = x;
		this->y = y;
	}
	
	friend Point operator - (const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y);
	}
	
	friend bool operator < (const Point &a, const Point &b) {
		if (a.x != b.x) {
			return a.x < b.x;
		} else {
			return a.y < b.y;
		}
	}

	friend long long det(const Point &a, const Point &b) {
		return a.x * b.y - b.x * a.y;
	}
	
	friend long long det(const Point &a, const Point &b, const Point &c) {
		return det(b - a, c - a);
	}
	
	friend long long area(const Point &a, const Point &b, const Point &c) {
		return absll(det(a, b, c));
	}
};

vector<Point> convex_hull(vector<Point> point) {
	int n = (int)point.size();
	if (n <= 1) {
		return point;
	}
	sort(point.begin(), point.end());
	vector<Point> convex;
	{
		vector<Point> stack;
		stack.push_back(point[0]);
		stack.push_back(point[1]);
		for (int i = 2; i < n; ++i) {
			for (; (int)stack.size() >= 2 && det(stack[(int)stack.size() - 2], stack.back(), point[i]) <= 0; stack.pop_back());
			stack.push_back(point[i]);
		}
		for (int i = 0; i < (int)stack.size(); ++i) {
			convex.push_back(stack[i]);
		}
	}
	{
		vector<Point> stack;
		stack.push_back(point[n - 1]);
		stack.push_back(point[n - 2]);
		for (int i = n - 3; i >= 0; --i) {
			for (; (int)stack.size() >= 2 && det(stack[(int)stack.size() - 2], stack.back(), point[i]) <= 0; stack.pop_back());
			stack.push_back(point[i]);
		}
		for (int i = 1; i < (int)stack.size() - 1; ++i) {
			convex.push_back(stack[i]);
		}
	}
	return convex;
}

int n;
Point p;
vector<Point> point;

long long get(const vector<Point> &point) {
	int n = (int)point.size();
	if (n < 3) {
		return 0;
	}
	int i = 0, j = 1, k = 2;
	
	long long result = 0;
	result = max(result, area(point[i], point[j], point[k]));
	for (; ; ) {
		bool flag = false;
		
		for (; area(point[i], point[j], point[(k + 1) % n]) > area(point[i], point[j], point[k]); ) {
			flag = true;
			k = (k + 1) % n;
			result = max(result, area(point[i], point[j], point[k]));
		}
		
		for (; area(point[i], point[(j + 1) % n], point[k]) > area(point[i], point[j], point[k]); ) {
			flag = true;
			j = (j + 1) % n;
			result = max(result, area(point[i], point[j], point[k]));
		}

		for (; area(point[(i + 1) % n], point[j], point[k]) > area(point[i], point[j], point[k]); ) {
			flag = true;
			i = (i + 1) % n;
			result = max(result, area(point[i], point[j], point[k]));
		}

		if (!flag) {
			k = (k + 1) % n;
		}
		if (k == 0) {
			break;
		}
	}
	return result;
}

void solve(void) {
	point.clear();
	for (int i = 0; i < n; ++i) {
		p.read();
		point.push_back(p);
	}
	
	vector<Point> convex = convex_hull(point);
	long long result = get(convex);
	printf("%.2f\n", result / 2.);
}

int main(void) {
	for (; ~scanf("%d", &n) && ~n; solve());
}
