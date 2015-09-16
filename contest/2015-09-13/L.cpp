#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
int modulo(1000000007);
int inv2((1000000007 + 1) / 2);
int getInt() {
	int x(0);
	char c;
	c = getchar();
	while(c < '0' || c > '9') {
		c = getchar();
	}
	while(c >= '0' && c <= '9') {
		x = x * 10 + c - '0';
		c = getchar();
	}
	return x;
}
const int N(111111);
struct Point {
	int x, y;
	void scan() {
		x = getInt();
		y = getInt();
	}
	Point() {
	}
	Point(int x, int y) : x(x), y(y) {
	}
} a[N];
__inline int add(int x, int y) {
	x += y;
	if(x >= modulo) {
		x -= modulo;
	}
	return x;
}
__inline int sub(int x, int y) {
	x -= y;
	if(x < 0) {
		x += modulo;
	}
	return x;
}

__inline Point operator + (const Point & a, const Point & b) {
	return Point(add(a.x, b.x), add(a.y, b.y));
}
__inline Point operator - (const Point & a, const Point & b) {
	return Point(sub(a.x, b.x), sub(a.y, b.y));
}
__inline Point operator * (const int & a, const Point & b) {
	return Point((long long)a * b.x % modulo, (long long)a * b.y % modulo);
}
__inline int operator * (const Point & a, const Point & b) {
	int res(((long long)a.x * b.y - (long long)b.x * a.y) % modulo);
	if(res < 0) {
		res += modulo;
	}
	return res;
}
int main() {
	int tests;
	tests = getInt();
	for(int qq(1); qq <= tests; qq++) {
		int n;
		n = getInt();
		for(int i(0); i < n; i++) {
			a[i].scan();
		}
		Point sum(0, 0);
		int pw(1);
		for(int i(n - 1); i >= 1; i--) {
			sum = sum + pw * a[i];
			pw = add(pw, pw);
		}
		pw = (long long)pw * inv2 % modulo;
		int ans(0);
		for(int i(0); i < n; i++) {
			ans = add(ans, a[i] * sum);
			sum = sum - pw * a[i + 1];
			sum = 2 * sum;
			sum = sum + a[i];
		}
		printf("%d\n", (ans + modulo) % modulo);
	}
}
