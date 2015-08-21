#include <cstdio>
#include <algorithm>
#include <cctype>

__inline bool intersect(int x1, int y1, int x2, int y2) {
	return std::max(x1, x2) < std::min(y1, y2);
}

__inline int input() {
	char token = getchar();
	for (; !isdigit(token); token = getchar());
	int number = token - '0';
	for (token = getchar(); isdigit(token); token = getchar()) {
		number = number * 10 + token - '0';
	}
	return number;
}

class Area {
public:
	int x1, y1, x2, y2;
	
	Area() {}
	Area(int x1, int y1, int x2, int y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}
	
	void read() {
		x1 = input() << 1;
		y1 = input() << 1;
		x2 = input() << 1;
		y2 = input() << 1;
	}
	
	bool legal() const {
		return x1 < x2 && y1 < y2;
	}
	
	Area get(int half) const {
		if (half == 0) {
			return Area(x1, y1, (x1 + x2) / 2, y2);
		} else if (half == 1) {
			return Area((x1 + x2) / 2, y1, x2, y2);
		} else if (half == 2) {
			return Area(x1, y1, x2, (y1 + y2) / 2);
		} else if (half == 3) {
			return Area(x1, (y1 + y2) / 2, x2, y2);
		}
	}
	
	friend Area intersect(const Area &a, const Area &b) {
		return Area(std::max(a.x1, b.x1), std::max(a.y1, b.y1), std::min(a.x2, b.x2), std::min(a.y2, b.y2));
	}
};

const int N = 111;

int n, m, answer;
Area lower[N], upper[N];
bool removed[N];

bool check(int index) {
	bool found = false;
	for (int dir = 0; dir < 4; ++dir) {
		bool clear = true;
		for (int i = 0; i < m; ++i) {
			if (removed[i] || i == index) {
				continue;
			}
			if (dir == 0) {
				if (lower[i].x1 >= lower[index].x2 && intersect(lower[i].y1, lower[i].y2, lower[index].y1, lower[index].y2)) {
					clear = false;
					break;
				} 
			}
			if (dir == 1) {
				if (lower[i].x2 <= lower[index].x1 && intersect(lower[i].y1, lower[i].y2, lower[index].y1, lower[index].y2)) {
					clear = false;
					break;
				} 
			}
			if (dir == 2) {
				if (lower[i].y1 >= lower[index].y2 && intersect(lower[i].x1, lower[i].x2, lower[index].x1, lower[index].x2)) {
					clear = false;
					break;
				} 
			}
			if (dir == 3) {
				if (lower[i].y2 <= lower[index].y1 && intersect(lower[i].x1, lower[i].x2, lower[index].x1, lower[index].x2)) {
					clear = false;
					break;
				} 
			}
		}
		if (clear) {
			found = true;
			break;
		}
	}
	if (!found) {
		return false;
	}
	for (int i = 0; i < n; ++i) {
		for (int half = 0; half < 4; ++half) {
			Area piece = upper[i].get(half);
			
			bool overlap = false;
			for (int j = 0; j < m; ++j) {
				if (removed[j] || j == index) {
					continue;
				}
				if (intersect(piece, lower[j]).legal()) {
					overlap = true;
					break;
				}
			}
			if (!overlap) {
				return false;
			}
		}
	}
	return true;
}

void dfs(int dep) {
	answer = std::max(answer, dep);
	for (int i = 0; i < m; ++i) {
		if (!removed[i] && check(i)) {
			removed[i] = true;
			dfs(dep + 1);
			removed[i] = false;
		}
	}
}

void solve(void) {
	n = input();
	for (int i = 0; i < m; ++i) {
		lower[i].read();
	}
	for (int i = 0; i < n; ++i) {
		upper[i].read();
	}
	answer = 0;
	dfs(0);
	printf("%d\n", answer);
}

int main(void) {
	for (int tests = 1; m = input(); ++tests) {
		printf("Case %d: ", tests);
		solve();
	}
}
