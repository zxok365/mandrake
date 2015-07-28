namespace aho_aorasick_automation {

class Node {
public:
	const static int N = 26;
	
	Node *child[N];
	Node *fail;
	int counter;

	Node() {
		fill(child, child + N, NULL);
		fail = NULL;
		counter = 0;
	}
};

void insert(Node *x, char *str) {
	int len = (int)strlen(str);
	for (int i = 0; i < len; ++i) {
		int c = str[i] - 'a';
		if (!x->child[c]) {
			x->child[c] = new Node();
		}
		x = x->child[c];
	}
	x->counter++;
}

void build() {
	vector<Node*> queue;
	queue.push_back(root->fail = root);
	for (int head = 0; head < (int)queue.size(); ++head) {
		Node* x = queue[head];
		for (int i = 0; i < Node::N; ++i) {
			if (x->child[i]) {
				x->child[i]->fail = (x == root) ? root : x->fail->child[i];
				x->child[i]->counter += x->child[i]->fail->counter;
				queue.push_back(x->child[i]);
			} else {
				x->child[i] = (x == root) ? root : x->fail->child[i];
			}
		}
	}
}

};
