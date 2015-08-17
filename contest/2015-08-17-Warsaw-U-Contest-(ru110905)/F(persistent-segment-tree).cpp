#include <cstdio>
#include <algorithm>
#include <vector>
#include <climits>

class Node {
public:
	Node *left, *right;
	long long value;

	Node(Node *left, Node *right, const long long &value) : left(left), right(right), value(value) {}

	Node* modify(int l, int r, int ql, int qr, const long long &value);
	long long query(int l, int r, int qx);
};

Node* null;

Node* Node::modify(int l, int r, int ql, int qr, const long long &value) {
	if (qr < l || r < ql) {
		return this;
	}
	if (ql <= l && r <= qr) {
		return new Node(this->left, this->right, this->value + value);
	}
	int mid = l + r >> 1;
	return new Node(this->left->modify(l, mid, ql, qr, value),
					this->right->modify(mid + 1, r, ql, qr, value),
					this->value);
}

long long Node::query(int l, int r, int qx) {
	if (qx < l || r < qx) {
		return 0;
	}
	if (qx <= l && r <= qx) {
		return this->value;
	}
	int mid = l + r >> 1;
	return this->left->query(l, mid, qx) + this->right->query(mid + 1, r, qx) + this->value;
}

const int N = 333333;

int n, m, k;
std::vector<int> belong[N];
long long number[N];
Node *root[N];

int main(void) {
	scanf("%d%d", &n, &m);
	
	for (int i = 1; i <= m; ++i) {
		int owner;
		scanf("%d", &owner);
		belong[owner].push_back(i);
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &number[i]);
	}
	
	null = new Node(NULL, NULL, 0);
	null->left = null->right = null;
	
	root[0] = null;
	
	scanf("%d", &k);
	for (int i = 1; i <= k; ++i) {
		int left, right, value;
		scanf("%d%d%d", &left, &right, &value);
		if (left <= right) {
			root[i] = root[i - 1]->modify(1, m, left, right, value);
		} else {
			root[i] = root[i - 1]->modify(1, m, 1, right, value)->modify(1, m, left, m, value);
		}
	}
	
	for (int i = 1; i <= n; ++i) {
		int left = 0, right = k + 1;
		while (right - left > 1) {
			int mid = left + right >> 1;
			
			long long sum = 0;
			for (int j = 0; j < (int)belong[i].size(); ++j) {
				sum += root[mid]->query(1, m, belong[i][j]);
				sum = std::min(sum, number[i]);
			}
			
			if (sum < number[i]) {
				left = mid;
			} else {
				right = mid;
			}
		}
		if (right <= k) {
			printf("%d\n", right);
		} else {
			puts("NIE");
		}
	}
}
