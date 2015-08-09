class State {
public:
	State *child[N], *parent;
	int length;
	
	State(int length) : parent(NULL), length(length) {
		memset(child, NULL, sizeof(child));
	}
	
	State* extend(State *start, int token) {
		State *p = this;
		State *np = new State(length + 1);
		for (; p && !p->child[token]; p = p->parent) {
			p->child[token] = np;
		}
		if (!p) {
			np->parent = start;
		} else {
			State *q = p->child[token];
			if (p->length + 1 == q->length) {
				np->parent = q;
			} else {
				State *nq = new State(p->length + 1);
				memcpy(nq->child, q->child, sizeof(q->child));
				nq->parent = q->parent;
				np->parent = q->parent = nq;
				for (; p && p->child[token] == q; p = p->parent) {
					p->child[token] = nq;
				}
			}
		}
		return np;
	}
};
