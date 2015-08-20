#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <vector>

class Node {
public:
	Node *child[26], *fail;
	int index;
	int counter;
	int degree;

	Node();
};

std::vector<Node*> pool;

Node::Node() : fail(NULL), counter(0), degree(0) {
	memset(child, NULL, sizeof(child));
	pool.push_back(this);
}

Node* insert(Node *x, char *text) {
	int length = (int)strlen(text);
	for (int i = 0; i < length; ++i) {
		int token = text[i] - 'a';
		if (!x->child[token]) {
			x->child[token] = new Node();
		}
		x = x->child[token];
	}
	return x;
}

Node *root;

void build() {
	std::vector<Node*> queue;
	queue.push_back(root->fail = root);
	for (int head = 0; head < (int)queue.size(); ++head) {
		Node *x = queue[head];
		for (int token = 0; token < 26; ++token) {
			if (x->child[token]) {
				x->child[token]->fail = (x == root) ? root : x->fail->child[token];
				queue.push_back(x->child[token]);
			} else {
				x->child[token] = (x == root) ? root : x->fail->child[token];
			}
		}
	}
}

const int N = 1111111;

int n;
char str[222][111];
Node *where[N];

void solve() {
	root = new Node();
	for (int i = 0; i < n; ++i) {
		scanf("%s", str[i]);
		where[i] = insert(root, str[i]);
	}
	
	build();
	
	static char text[N];
	scanf("%s", text);
	int length = (int)strlen(text);
	Node *pos = root;
	for (int i = 0; i < length; ++i) {
		int token = text[i] - 'a';
		pos = pos->child[token];
		pos->counter++;
	}
	
	for (int i = 0; i < (int)pool.size(); ++i) {
		if (pool[i]->fail != root) {
			pool[i]->fail->degree++;
		}
	}
	std::vector<Node*> queue;
	for (int i = 0; i < (int)pool.size(); ++i) {
		if (pool[i]->degree == 0) {
			queue.push_back(pool[i]);
		}
	}
	for (int head = 0; head < (int)queue.size(); ++head) {
		Node *x = queue[head];
		if (x->fail != root && (--x->fail->degree) == 0) {
			queue.push_back(x->fail);
		}
	}
	for (int i = 0; i < (int)queue.size(); ++i) {
		queue[i]->fail->counter += queue[i]->counter;
	}
	
	int answer = 0;
	for (int i = 0; i < n; ++i) {
		answer = std::max(answer, where[i]->counter);
	}
	printf("%d\n", answer);
	for (int i = 0; i < n; ++i) {
		if (where[i]->counter == answer) {
			printf("%s\n", str[i]);
		}
	}
	for (int i = 0; i < (int)pool.size(); ++i) {
		delete pool[i];
	}
	pool.clear();
}

int main(void) {
	for (; scanf("%d", &n) && n; solve());
}
