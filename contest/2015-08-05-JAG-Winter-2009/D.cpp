#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cassert>
#include <cmath>

#define SIZE(x) ((int)x.size())

using namespace std;

const int N = 555;

const double eps = 1e-6;

int Sign(const double &x) {
	return (x > eps) - (x + eps < 0);
}
struct Point {
	double x, y, z;
	
	Point() {}
	
	Point(const double &x, const double &y, const double &z) : x(x), y(y), z(z) {}
	
	void Input() {
		scanf("%lf%lf%lf", &x, &y, &z);
	}
	
	double length() const {
		return sqrt(x * x + y * y + z * z);
	}
	
	double dot(const Point &b) const {
		return x * b.x + y * b.y + z * b.z;
	}
	
	Point cross(const Point &b) const {
		return Point(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);
	}
	
	friend Point operator + (const Point &a, const Point &b) {
		return Point(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	friend Point operator - (const Point &a, const Point &b) {
		return Point(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	friend Point operator / (const Point &a, const double &b) {
		return Point(a.x / b, a.y / b, a.z / b);
	}
	
	friend bool operator == (const Point &a, const Point &b) {
		return Sign(a.x - b.x) == 0 && Sign(a.y - b.y) == 0 && Sign(a.z - b.z) == 0;
	}
};


int mark[N][N];
Point info[N];
int n, cnt;

double mix(const Point &a, const Point &b, const Point &c) {
	return a.dot(b.cross(c));
}

double volume(int a, int b, int c, int d) {
	return mix(info[b] - info[a], info[c] - info[a], info[d] - info[a]);
}

double area(int a,int b, int c) {
	return ((info[b] - info[a]).cross(info[c] - info[a])).length();
}

struct Face {
	int a, b, c;
	Face() {}
	Face(int a, int b, int c) : a(a), b(b), c(c) {}
	int &operator [] (int k) {return k == 0 ? a : k == 1 ? b : c;}
};

vector <Face> face;
inline void insert(int a, int b, int c) {
	face.push_back(Face(a, b, c)); 
}

void add(int v) {
	vector <Face> tmp;
	int a, b, c;
	cnt++;
	for (int i = 0; i < SIZE(face); i++) {
		a = face[i][0]; b = face[i][1]; c = face[i][2];
		if (Sign(volume(v, a, b, c)) < 0) 
			mark[a][b] = mark[b][a] = mark[b][c] = mark[c][b] = mark[c][a] = mark[a][c] = cnt;
		else tmp.push_back(face[i]);
	}
	face = tmp;
	for (int i = 0; i < SIZE(tmp); i++) {
		a = face[i][0]; b = face[i][1]; c = face[i][2];
		if (mark[a][b] == cnt) insert(b, a, v);
		if (mark[b][c] == cnt) insert(c, b, v);
		if (mark[c][a] == cnt) insert(a, c, v); 
	}
}

int Find() {
	for (int i = 2; i < n; i++) {
		Point ndir = (info[0] - info[i]).cross(info[1] - info[i]);
		if (ndir == Point()) continue;
		swap(info[i], info[2]);
		for (int j = i + 1; j < n; j++)
			if (Sign(volume(0, 1, 2, j)) != 0) {
				swap(info[j], info[3]);
				insert(0, 1, 2);insert(0, 2, 1);
				return 1;
			}
	}
	return 0;
}
int main() {
	for (; scanf("%d", &n) == 1; ) {
		for (int i = 0; i < n; i++) {
			info[i].Input();
		}
		face.clear();
		random_shuffle(info, info + n);
		if (Find()) {
			memset(mark, 0, sizeof mark);
			cnt = 0;
			for (int i = 3; i < n; i++) add(i);
			vector<Point> Ndir;
			for (int i = 0; i < SIZE(face); ++i) {
				Point p = (info[face[i][0]] - info[face[i][1]]).cross(info[face[i][2]] - info[face[i][1]]);
				p = p / p.length();
			}
			double ans = 0;
			for (int i = 0; i < (int)face.size(); ++i) {
				ans += fabs(area(face[i].a, face[i].b, face[i].c));
			}
			printf("%.3f\n", ans / 2);
		} else {
			printf("%.3f\n", 0.);
		}
	}
	return 0;
}
