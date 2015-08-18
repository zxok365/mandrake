int size;
int text[N];

class Node {
public:
	Node *child[26], *fail;
	int length;
	
	Node(int length) : length(length), fail(NULL) {
		memset(child, NULL, sizeof(child));
	}
};

Node *odd, *even;

Node* match(Node *now) {
	for (; text[size - now->length - 1] != text[size]; now = now->fail);
	return now;
}

bool extend(Node *&last, int token) {
	text[++size] = token;
	
	Node *now = last;
	now = match(now);
	if (now->child[token]) {
		last = now->child[token];
		return false;
	}
	
	last = now->child[token] = new Node(now->length + 2);
	if (now == odd) {
		last->fail = even;
	} else {
		now = match(now->fail);
		last->fail = now->child[token];
	}
	return true;
}

void build() {
	text[size = 0] = -1;
	even = new Node(0), odd = new Node(-1);
	even->fail = odd;
}
