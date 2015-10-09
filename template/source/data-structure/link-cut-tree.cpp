#ifndef _DYNAMIC_TREE_CHAIN_

#define _DYNAMIC_TREE_CHAIN_

#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include "exception.h"

using namespace std;

template<class T>
class DynamicTreeChain {
private:
	class Node {
	public:
		T data, sum;
		
		Node *father;
		Node *vfather;
		Node *child[2];
		
		int index;
		bool reverse;
		
		Node() {
		}
		
		Node(int index, const T &data) {
			this->data = data;
			this->sum = data;
			this->father = nullptr;
			this->vfather = nullptr;
			this->child[0] = nullptr;
			this->child[1] = nullptr;
			this->index = index;
		}
		
		void update() {
			if (child[0]) {
				child[0]->release();
			}
			if (child[1]) {
				child[1]->release();
			}
			sum = (child[0] ? child[0]->sum : T()) + data + (child[1] ? child[1]->sum : T());
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
	
	void rotate(Node *x, bool dir){
		auto y = x->father;
		if (y->father) {
			y->father->child[y->father->child[1] == y] = x;
		}
		x->father = y->father;
		x->vfather = y->vfather;
		y->vfather = nullptr;
		if (x->child[dir ^ 1]) {
			x->child[dir ^ 1]->father = y;
		}
		y->child[dir] = x->child[dir ^ 1];
		x->child[dir ^ 1] = y;
		y->father = x;
		y->update();
	}
	
	void splay(Node *x, Node *target = nullptr){
		for (x->release(); x->father != target; ) {
			auto y = x->father;
			if (y->father == target){
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
	
	Node *access(Node *x){
		splay(x);
		if (x->child[0]) {
			x->release();
			x->child[0]->vfather = x;
			x->child[0]->father = nullptr;
			x->child[0] = nullptr;
			x->update();
		}
		auto y = x;
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
		auto w = access(y);
		splay(x);
		if (x->vfather == w || x == w) {
			throw Exception("Circle exists");
		}
		x->reverse ^= 1;
		access(y);
		y->child[0] = x;
		x->father = y;
		y->update();
	}
	
	void eraseEdge(Node *x, Node *y) {
		if (x == y) {
			throw Exception("Not connected");
		}
		access(x);
		if (access(y) == x){
			splay(x, y);
			if (x->child[0]) {
				throw Exception("Not connected");
			}
			y->release();
			y->child[1]->father = nullptr;
			y->child[1]->vfather = nullptr;
			y->child[1] = nullptr;
			y->update();
		} else {
			splay(x);
			if (x->vfather != y || x->child[1]) {
				throw Exception("Not connected");
			}
			access(x);
			x->release();
			x->child[1]->father = nullptr;
			x->child[1]->vfather = nullptr;
			x->child[1] = nullptr;
			x->update();
		}
	}
	
	void modify(Node *x, const T &v) {
		access(x);
		x->data = v;
		x->update();
	}
	
	T query(Node *x, Node *y) {
		access(x);
		auto u = access(y);
		auto sum = u->data;
		splay(u);
		if (u->child[0]) {
			sum = sum + u->child[0]->sum;
		}
		access(x);
		splay(u);
		if (u->child[0]) {
			sum = sum + u->child[0]->sum;
		}
		return sum;
	}
	
	Node* lca(Node *x, Node *y) {
		access(x);
		return access(y);
	}
	
	Node *root(Node *x) {
		access(x);
		for (; ; x = x->child[1]) {
			x->release();
			if (!x->child[1]) {
				break;
			}
		}
		return x;
	}
	
	void evert(Node *x) {
		access(x);
		x->reverse ^= 1;
	}
	
	Node *lastVertex(Node *x, Node *y) {
		if (x == y) {
			throw Exception("Out of range");
		}
		if (lca(x, y) == y) {
			access(x);
			splay(y);
			auto w = y->child[0];
			for (; w; w = w->child[1]) {
				w->release();
				if (!w->child[1]) {
					break;
				}
			}
			if (!w) {
				return x;
			}
			return w;
		} else {
			access(y);
			splay(y);
			auto w = y->child[1];
			for (; w; w = w->child[0]) {
				w->release();
				if (!w->child[0]) {
					break;
				}
			}
			if (!w) {
				return x;
			}
			return w;
		}
	}
	
public:
	int n;
	vector<Node> node;
	
	DynamicTreeChain(const vector<pair<int, int> > &edge, const vector<T> &weight) {
		n = 0;
		for (int i = 0; i < (int)edge.size(); ++i) {
			n = max(n, max(edge[i].first, edge[i].second));
		}
		n++;
		if (n != (int)weight.size()) {
			throw Exception("Contradiction exists");
		}
		for (int i = 0; i < n; ++i) {
			node.push_back(Node(i, weight[i]));
		}
		for (int i = 0; i < (int)edge.size(); ++i) {
			int x = edge[i].first, y = edge[i].second;
			if (x < 0 || x >= n || y < 0 || y >= n) {
				throw Exception("Contradiction exists");
			}
			if (root(x) == root(y)) {
				throw Exception("Circle exists");
			}
			addEdge(x, y);
		}
		for (int i = 0; i < n; ++i) {
			if (i < root(i)) {
				evert(i);
			}
		}
	}

	DynamicTreeChain(const DynamicTreeChain &other) {
		*this = other;
	}
	
	~DynamicTreeChain() {
	}

	DynamicTreeChain& operator = (const DynamicTreeChain &other) {
		if (this == &other) {
			return *this;
		}
		n = other.n;
		node = other.node;
		for (int i = 0; i < n; ++i) {
			if (node[i].father) {
				node[i].father = &node[node[i].father->index];
			}
			if (node[i].vfather) {
				node[i].vfather = &node[node[i].vfather->index];
			}
			if (node[i].child[0]) {
				node[i].child[0] = &node[node[i].child[0]->index];
			}
			if (node[i].child[1]) {
				node[i].child[1] = &node[node[i].child[1]->index];
			}
		}
		return *this;
	}
	
	void addEdge(int x, int y) {
		if (x < 0 || x >= n || y < 0 || y >= n) {
			throw Exception("Out of range");
		}
		addEdge(&node[y], &node[x]);
	}

	void eraseEdge(int x, int y) {
		if (x < 0 || x >= n || y < 0 || y >= n) {
			throw Exception("Out of range");
		}
		eraseEdge(&node[y], &node[x]);
	}

	void modify(int x, const T &v) {
		if (x < 0 || x >= n) {
			throw Exception("Out of range");
		}
		modify(&node[x], v);
	}

	T query(int x, int y) {
		if (x < 0 || x >= n || y < 0 || y >= n) {
			throw Exception("Out of range");
		}
		if (root(x) != root(y)) {
			throw Exception("Not connected");
		}
		return query(&node[x], &node[y]);
	}

	int lca(int x, int y) {
		if (x < 0 || x >= n || y < 0 || y >= n) {
			throw Exception("Out of range");
		}
		if (root(x) != root(y)) {
			throw Exception("Not connected");
		}
		return lca(&node[x], &node[y])->index;
	}
	
	int root(int x) {
		if (x < 0 || x >= n) {
			throw Exception("Out of range");
		}
		return root(&node[x])->index;
	}

	void evert(int x) {
		if (x < 0 || x >= n) {
			throw Exception("Out of range");
		}
		evert(&node[x]);
	}

	int lastVertex(int x, int y) {
		if (x < 0 || x >= n || y < 0 || y >= n) {
			throw Exception("Out of range");
		}
		if (root(x) != root(y)) {
			throw Exception("Not connected");
		}
		return lastVertex(&node[x], &node[y])->index;
	}
};

#endif
