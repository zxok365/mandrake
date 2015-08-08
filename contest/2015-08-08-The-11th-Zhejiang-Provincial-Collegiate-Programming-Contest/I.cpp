#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

const int N = 111111;

int n, m, stamp, comps, top;
std::vector<int> edge[N];
int dfn[N], low[N], comp[N], stack[N], vertex[N], edges[N];

class Node {
public:
	Node *child[26], *fail;
	int index;
	bool ban;
	
	Node() {
		memset(child, 0, sizeof(child));
//		std::fill(child, child + 26, NULL);
		fail = NULL;
		index = 0;
		ban = false;
	}
	
	Node (int index) : index(index) {
		memset(child, 0, sizeof(child));
//		std::fill(child, child + 26, NULL);
		fail = NULL;
		ban = false;
	}
};

int size;
Node pool[N];

Node* apply() {
	pool[size] = Node(size);
	return &pool[size++];
}

void insert(Node *x, char *text) {
	int length = (int)strlen(text);
	for (int i = 0; i < length; ++i) {
		int token = text[i] - 'a';
		if (!x->child[token]) {
			x->child[token] = apply();
		}
		x = x->child[token];
	}
	x->ban = true;
}

void build(Node *root) {
	std::vector<Node*> queue;
	queue.push_back(root->fail = root);
	for (int head = 0; head < (int)queue.size(); ++head) {
		Node *x = queue[head];
		for (int token = 0; token < 26; ++token) {
			if (x->child[token]) {
				x->child[token]->fail = (x == root) ? root : x->fail->child[token];
				x->child[token]->ban |= x->child[token]->fail->ban;
				queue.push_back(x->child[token]);
			} else {
				x->child[token] = (x == root) ? root : x->fail->child[token];
			}
		}
	}
}

bool legal(char *text) {
	int length = (int)strlen(text);
	for (int i = 0; i < length; ++i) {
		if (text[i] < 'a' || text[i] > 'a' + m) {
			return false;
		}
	}
	return true;
}

void tarjan(int x) {
	dfn[x] = low[x] = ++stamp;
	stack[top++] = x;
	for (int i = 0; i < (int)edge[x].size(); ++i) {
		int y = edge[x][i];
		if (!dfn[y]) {
			tarjan(y);
			low[x] = std::min(low[x], low[y]);
		} else if (!comp[y]) {
			low[x] = std::min(low[x], dfn[y]);
		}
	}
	if (low[x] == dfn[x]) {
		comps++;
		do {
			int y = stack[--top];
			comp[y] = comps;
		} while (stack[top] != x);
	}
}

void solve(void) {
	size = 0;
	Node *root = apply();
	
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		static char text[N];
		scanf("%s", text);
		if (legal(text)) {
			insert(root, text);
		}
	}
	build(root);
	
	for (int i = 0; i < size; ++i) {
		edge[i].clear();
	}
	
	for (int i = 0; i < size; ++i) {
		Node *x = &pool[i];
		if (x->ban) {
			continue;
		}
		for (int token = 0; token < m; ++token) {
			Node *y = x->child[token];
			if (y->ban) {
				continue;
			}
			edge[x - pool].push_back(y - pool);
		}
	}
	
/*	printf("!!!%d\n", size);
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < (int)edge[i].size(); ++j) {
			printf("%d ", edge[i][j]);
		}
		puts("");
	}*/

	for (int i = 0; i < size; ++i) {
		std::sort(edge[i].begin(), edge[i].end());
		edge[i].erase(std::unique(edge[i].begin(), edge[i].end()), edge[i].end());
	}
/*	
	printf("%d\n", size);
	
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < (int)edge[i].size(); ++j) {
			printf("%d %d\n", i, edge[i][j]);
		}
	}
*/	
	stamp = comps = top = 0;
	std::fill(dfn, dfn + size, 0);
	std::fill(comp, comp + size, 0);
	for (int i = 0; i < size; ++i) {
		if (!dfn[i]) {
			tarjan(i);
		}
	}
/*	
	for (int i = 0; i < size; ++i) {
		printf("%d ", comp[i]);
	}
	puts("");
*/	
	std::fill(vertex + 1, vertex + comps + 1, 0);
	std::fill(edges + 1, edges + comps + 1, 0);
	for (int x = 0; x < size; ++x) {
		vertex[comp[x]]++;
		for (int i = 0; i < (int)edge[x].size(); ++i) {
			int y = edge[x][i];
			if (comp[x] == comp[y]) {
				edges[comp[x]]++;
			}
		}
	}
	for (int i = 1; i <= comps; ++i) {
		if (vertex[i] < edges[i]) {
			puts("Yes");
			return;
		}
	}
	puts("No");
}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
