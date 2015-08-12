#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdio>

using namespace std;
const int N = 222;
struct Person {
	int money, id;
}person[N];

int a[N], ans[N];

bool cmp(Person p1, Person p2) {
	if (p1.money != p2.money) return p1.money > p2.money;
	else return p1.id < p2.id;
}

void solve() {
	int tag, n;
	scanf("%d%d", &tag, &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	int sum = 0;
	for (int i = 1; i <= n; i++) sum += a[i];
	if (sum < tag) {
		puts("IMPOSSIBLE");
		return;
	}
	for (int i = 1; i <= n; i++) person[i].id = i, person[i].money = a[i];
	sort(person + 1, person + n + 1, cmp);
	for (int i = 1; i <= n; i++) ans[i] = 0;
	int rest = tag;
	for (int i = n; i >= 1; i--) {
		if (person[i].money < rest / i) {
			ans[person[i].id] = person[i].money;
			rest -= person[i].money;
		}
		else {
			ans[person[i].id] = rest / i;
			int Left = rest % i;
			for (int j = 1; j <= i - 1; j++) ans[person[j].id] = rest / i;
			for (int j = 1; j <= Left; j++) ans[person[j].id]++;
			break;
		}
	}
	
	for (int i = 1; i < n; i++)
		printf("%d ", ans[i]);
	printf("%d\n", ans[n]);
}

int main() {
	int T;
	scanf("%d", &T);
	for (int tt = 1; tt <= T; tt++) {
		solve();
	}
}
