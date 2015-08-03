#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

class LinkCutTree {
public:

	class Node {
	public:
		Node *father;
		Node *vfather;
		Node *child[2];
		
		bool reverse;
		
		Node() {
			this->father = NULL;
			this->vfather = NULL;
			this->child[0] = NULL;
			this->child[1] = NULL;
			this->reverse = false;
		}
		
		void update() {
			if (child[0]) {
				child[0]->release();
			}
			if (child[1]) {
				child[1]->release();
			}
		}
		
		void release() {
			if (reverse) {
				if (child[0]) {
					child[0]->reverse ^= 1;
				}
				if (child[1]) {
					child[1]->reverse ^= 1;
				}
				swap(child[0], child[1]);
				reverse = false;
			}
		}
	};
	
	void rotate(Node *x, bool dir) {
		Node *y = x->father;
		if (y->father) {
			y->father->child[y->father->child[1] == y] = x;
		}
		x->father = y->father;
		x->vfather = y->vfather;
		y->vfather = NULL;
		if (x->child[dir ^ 1]) {
			x->child[dir ^ 1]->father = y;
		}
		y->child[dir] = x->child[dir ^ 1];
		x->child[dir ^ 1] = y;
		y->father = x;
		y->update();
	}
	
	void splay(Node *x, Node *target = NULL) {
		for (x->release(); x->father != target; ) {
			Node *y = x->father;
			if (y->father == target) {
				y->release();
				x->release();
				bool dir = (y->child[1] == x);
				rotate(x, dir);
			} else {
				y->father->release();
				y->release();
				x->release();
				bool dir = (y->child[1] == x);
				if ((y->father->child[1] == y) == dir) {
					rotate(y, dir);
					rotate(x, dir);
				} else {
					rotate(x, dir);
					rotate(x, dir ^ 1);
				}
			}
		}
		x->update();
	}
	
	Node* access(Node *x) {
		splay(x);
		if (x->child[0]) {
			x->release();
			x->child[0]->vfather = x;
			x->child[0]->father = NULL;
			x->child[0] = NULL;
			x->update();
		}
		Node *y = x;
		if (x->vfather) {
			y = access(x->vfather);
			x->vfather->child[0] = x;
			x->father = x->vfather;
			x->vfather->update();
		}
		splay(x);
		return y;
	}
	
	void addEdge(Node *x, Node *y) {
		access(x);
		Node *w = access(y);
		splay(x);
		x->reverse ^= 1;
		access(y);
		y->child[0] = x;
		x->father = y;
		y->update();
	}
	
	void eraseEdge(Node *x, Node *y) {
		access(x);
		if (access(y) == x) {
			splay(x, y);
			y->release();
			y->child[1]->father = NULL;
			y->child[1]->vfather = NULL;
			y->child[1] = NULL;
			y->update();
		} else {
			splay(x);
			access(x);
			x->release();
			x->child[1]->father = NULL;
			x->child[1]->vfather = NULL;
			x->child[1] = NULL;
			x->update();
		}
	}
	
	Node* root(Node *x) {
		access(x);
		for (; ; x = x->child[1]) {
			x->release();
			if (!x->child[1]) {
				break;
			}
		}
		return x;
	}
	
	vector<Node> node;
	vector<int> counter;
	
	void build(int n) {
		node.clear();
		counter.clear();
		node.resize(n);
		counter.resize(n);
	}
	
	void addEdge(int x, int y) {
		addEdge(&node[y], &node[x]);
		counter[x]++;
		counter[y]++;
	}
	
	void eraseEdge(int x, int y) {
		eraseEdge(&node[x], &node[y]);
		counter[x]--;
		counter[y]--;
	}
	
	Node* root(int x) {
		return root(&node[x]);
	}
};

const int C = 111;

int n, m, c, t;
LinkCutTree tree[C];
map<pair<int, int>, int> edges;

void solve(void) {
	edges.clear();
	for (int i = 0; i < c; ++i) {
		tree[i].build(n);
	}
	for (int i = 0; i < m; ++i) {
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		x--; y--; w--;
		
		if (x > y) {
			swap(x, y);
		}
		edges[make_pair(x, y)] = w;
		tree[w].addEdge(x, y);
	}
	for (int i = 0; i < t; ++i) {
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		x--; y--; w--;
		
		if (x > y) {
			swap(x, y);
		}
		if (edges.count(make_pair(x, y)) == 0) {
			puts("No such cable.");
			continue;
		}
		if (edges[make_pair(x, y)] == w) {
			puts("Already owned.");
			continue;
		}
		if (tree[w].counter[x] >= 2 || tree[w].counter[y] >= 2) {
			puts("Forbidden: monopoly.");
			continue;
		}
		if (tree[w].root(x) == tree[w].root(y)) {
			puts("Forbidden: redundant.");
			continue;
		}
		puts("Sold.");
		tree[edges[make_pair(x, y)]].eraseEdge(x, y);
		tree[w].addEdge(x, y);
		edges[make_pair(x, y)] = w;
	}
	puts("");
}

int main(void) {
	for (; ~scanf("%d%d%d%d", &n, &m, &c, &t) && (n || m || c || t); solve());
}
