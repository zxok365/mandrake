#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 111;
const int K = 13;

struct Skill {
	int level, increment, bonus, id;
} skill[K];

int n, k;
int power[N], list[N], rank[N];
int best[N][(1 << 8) + 11];
int skillpoint, equipment;

void update(int &x, int y) {
	x = max(x, y);
}

__inline bool comp (const Skill &a, const Skill &b) {
	return a.increment > b.increment;
}

int result;
int counter[N];

void dfs(int x, int skillpoint, int power) {
	if (x == k) {
		for (int i = 0; i < k; ++i) {
			if (counter[i] == skill[i].level) {
				power += skill[i].increment * skill[i].level + skill[i].bonus;
			} else if (counter[i] + skillpoint >= skill[i].level) {
				power += skill[i].increment * skill[i].level + skill[i].bonus;
				skillpoint -= skill[i].level - counter[i];
			} else {
				power += skill[i].increment * (counter[i] + skillpoint);
				skillpoint = 0;
			}
		}
		result = max(result, power);
		return;
	}
	
	dfs(x + 1, skillpoint, power);
	
	if (skillpoint >= skill[x].level - counter[x]) {
		int backup = counter[x];
		
		counter[x] = skill[x].level;
		dfs(x + 1, skillpoint - skill[x].level + backup, power);
		counter[x] = backup;
	}
}

void solve() {
	for (int i = 0; i < k; ++i) {
		scanf("%d%d%d", &skill[i].level, &skill[i].increment, &skill[i].bonus);
		skill[i].id = i;
	}
	
	sort(skill, skill + k, comp);
	
	for (int i = 0; i < k; ++i) {
		rank[skill[i].id] = i;
	}

	for (int i = 1; i <= n; ++i) {
		scanf("%d", &power[i]);
		list[i] = 0;
		int num;
		for (scanf("%d", &num); num--; ) {
			int x;
			scanf("%d", &x);
			list[i] |= (1 << rank[x - 1]);
		}
	}
	
	scanf("%d%d", &skillpoint, &equipment);
	equipment = min(equipment, n);
	
	for (int i = 0; i <= n; ++i) {
		for (int mask = 0; mask < (1 << k); ++mask) {
			best[i][mask] = -1;
		}
	}

	best[0][0] = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = equipment; j >= 0; --j) {
			for (int mask = 0; mask < (1 << k); ++mask) {
				if (best[j][mask] == -1) {
					continue;
				}
				update(best[j + 1][mask | list[i + 1]], best[j][mask] + power[i + 1]);
			}
		}
	}

	result = 0;
	
	for (int mask = 0; mask < (1 << k); ++mask) {
		if (best[equipment][mask] == -1) {
			continue;
		}
		for (int i = 0; i < k; ++i) {
			counter[i] = (mask >> i & 1);
		}
		dfs(0, skillpoint, best[equipment][mask]);
	}
	
	printf("%d\n", result);
}

int main(void) {
	for (; scanf("%d%d", &k, &n) == 2; solve());
}
