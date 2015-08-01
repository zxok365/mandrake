#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;

const int MOD = 99990001;

__inline void add(int &x, int y) {
	x = (x + y % MOD) % MOD;
}

__inline void multiply(int &x, int y) {
	x = 1LL * x * y % MOD;
}

const int N = 222222;

int n;
int belong[N], tag[N];
set<int> edge[N];
pair<int, int> pairing[N];
map<pair<int, int>, int> weight;

class State {
public:
	int x, father, head;
	set<int>::iterator pointer;
	vector<pair<int, int> > queue;
	
	State(int x) : x(x) {
		father = 0;
		head = 1;
		pointer = edge[x].begin();
		queue.push_back(make_pair(x, 0));
	}
};

bool expand(State &state) {
	for (set<int>::iterator iter = state.pointer; iter != edge[state.x].end(); ++iter) {
		int y = *iter;
		if (y == state.father) {
			continue;
		}
		state.pointer = ++iter;
		state.queue.push_back(make_pair(y, state.x));
		return true;
	}
	for (; state.head < (int)state.queue.size(); ) {
		int x = state.queue[state.head].first;
		int father = state.queue[state.head].second;
		state.head++;
		
		for (set<int>::iterator iter = edge[x].begin(); iter != edge[x].end(); ++iter) {
			int y = *iter;
			if (y == father) {
				continue;
			}
			state.x = x;
			state.father = father;
			state.pointer = ++iter;
			state.queue.push_back(make_pair(y, x));
			return true;
		}
	}
	return false;
}

void solve(const State &state, int w, int index) {
	for (int head = 0; head < (int)state.queue.size(); ++head) {
		int x = state.queue[head].first;
		for (set<int>::iterator iter = edge[x].begin(); iter != edge[x].end(); ++iter) {
			int y = *iter;
			if (x < y) {
				add(weight[make_pair(x, y)], tag[belong[x]]);
				multiply(weight[make_pair(x, y)], w);
			}
		}
		belong[x] = index;
	}
}

int main(void) {
	scanf("%d", &n);
	for (int i = 1; i < n; ++i) {
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		if (x > y) {
			swap(x, y);
		}
		edge[x].insert(y);
		edge[y].insert(x);
		weight[make_pair(x, y)] = w;
		pairing[i] = make_pair(x, y);
	}
	
	for (int i = 1; i < n; ++i) {
		int index;
		scanf("%d", &index);
		int x = pairing[index].first, y = pairing[index].second;
		int w = weight[make_pair(x, y)];
		add(w, tag[belong[x]]);
		
		edge[x].erase(y);
		edge[y].erase(x);
	
		printf("%d\n", w);
		fflush(stdout);
	
 		for (State sidex(x), sidey(y); ; ) {
			bool expandx = expand(sidex);
			bool expandy = expand(sidey);

			if (!expandx && !expandy) {
				vector<pair<int, int> >::iterator minx = min_element(sidex.queue.begin(), sidex.queue.end());
				vector<pair<int, int> >::iterator miny = min_element(sidey.queue.begin(), sidey.queue.end());
				if (minx->first < miny->first) {
					expandy = true;
				} else {
					expandx = true;
				}
			}
		
			if (!expandx) {
				solve(sidex, w, i);
				add(tag[belong[y]], w);
				break;
			}
			if (!expandy) {
				solve(sidey, w, i);
				add(tag[belong[x]], w);
				break;
			}
		}
	}
}
