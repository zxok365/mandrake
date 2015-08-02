#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int N = 111111;

class Node {
public:
	int value, pos, min, max;

	Node() {}
	Node(int value, int pos, int min, int max) : value(value), pos(pos), min(min), max(max) {}
	
	friend bool operator < (const Node &a, const Node &b) {
		if (a.value != b.value) {
			return a.value < b.value;
		} else {
			return a.max > b.max;
		}
	}
};

int n, m;
int a[N], b[N], fail[N], value[N];

vector<Node> calc(int len, int element[]) {
	vector<Node> result;
	fail[1] = 1;
	value[1] = element[1];
	result.push_back(Node(element[1], 1, 1, 1));
	for (int i = 2; i <= len; ++i) {
		fail[i] = i;
		value[i] = element[i];
		for (int pos = i; pos > 0; pos = fail[pos] - 1) {
			value[pos] = __gcd(value[pos], element[i]);
			for (; fail[pos] > 1 && __gcd(value[fail[pos] - 1], value[pos]) == value[pos]; fail[pos] = fail[fail[pos] - 1]);
			result.push_back(Node(value[pos], i, i - pos + 1, i - fail[pos] + 1));
		}
	}
	sort(result.begin(), result.end());
	return result;
}

int get(const vector<Node> &vec1, const vector<Node> &vec2, int start1, int end1, int start2, int end2) {
	for (int i = start1, j = start2; i < end1 && j < end2; ) {
		if (vec1[i].max > vec2[j].max) {
			if (vec1[i].min <= vec2[j].max) {
				return vec2[j].max;
			}
			i++;
		} else {
			if (vec2[j].min <= vec1[i].max) {
				return vec1[i].max;
			}
			j++;
		}
	}
	return -1;
}

void solve(void) {
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	for (int i = 1; i <= m; ++i) {
		scanf("%d", &b[i]);
	}
	
	vector<Node> vec1 = calc(n, a);
	vector<Node> vec2 = calc(m, b);
	
	int answer = -1;
	for (int start1 = 0, start2 = 0, end1, end2; start1 < (int)vec1.size(); start1 = end1, start2 = end2) {
		for (end1 = start1; end1 < (int)vec1.size() && vec1[end1].value == vec1[start1].value; ++end1);
		for (end2 = start2; end2 < (int)vec2.size() && vec2[end2].value < vec1[start1].value; ++end2);
		if (end2 == (int)vec2.size()) {
			break;
		}
		start2 = end2;
		if (vec2[start2].value != vec1[start1].value) {
			continue;
		}
		for (end2 = start2; end2 < (int)vec2.size() && vec2[end2].value == vec2[start2].value; ++end2);
		
		answer = max(answer, get(vec1, vec2, start1, end1, start2, end2));
	}
	
	if (answer == -1) {
		puts("0 0");
		return;
	}

	
	long long ways = 0;
	for (int start1 = 0, start2 = 0, end1, end2; start1 < (int)vec1.size(); start1 = end1, start2 = end2) {
		for (end1 = start1; end1 < (int)vec1.size() && vec1[end1].value == vec1[start1].value; ++end1);
		for (end2 = start2; end2 < (int)vec2.size() && vec2[end2].value < vec1[start1].value; ++end2);
		if (end2 == (int)vec2.size()) {
			break;
		}
		start2 = end2;
		if (vec2[start2].value != vec1[start1].value) {
			continue;
		}
		for (end2 = start2; end2 < (int)vec2.size() && vec2[end2].value == vec2[start2].value; ++end2);
	
		int counter1 = 0;
		for (int i = start1; i < end1; ++i) {
			if (vec1[i].min <= answer && answer <= vec1[i].max) {
				counter1++;
			}
		}
		int counter2 = 0;
		for (int i = start2; i < end2; ++i) {
			if (vec2[i].min <= answer && answer <= vec2[i].max) {
				counter2++;
			}
		}
		ways += 1LL * counter1 * counter2;
	}
	
	cout << answer << " " << ways << endl;
}

int main(void) {
	for (; ~scanf("%d%d", &n, &m); solve());
}
