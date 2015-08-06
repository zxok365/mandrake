#include <cstdio>
#include <vector>

using namespace std;

int left, right;

void dfs(int number, vector<int> &answer, int base) {
	if (number <= 0) {
		return;
	}
	int digit = number % 10;
	for (int i = 1; i <= digit; ++i) {
		answer[i] += base;
	}
	for (int rest = number / 10; rest; rest /= 10) {
		answer[rest % 10] += (digit + 1) * base;
	}
	for (int i = 0; i < 10; ++i) {
		answer[i] += (number / 10) * base;
	}
	dfs(number / 10 - 1, answer, base * 10);
}

void solve(void) {
	if (left > right) {
		swap(left, right);
	}
	left--;
		
	vector<int> answerl(10, 0), answerr(10, 0);
	dfs(left, answerl, 1);
	dfs(right, answerr, 1);
	
	for (int i = 0; i < 10; ++i) {
		printf("%d%s", answerr[i] - answerl[i], (i == 9) ? "\n" : " ");
	}
}

int main(void) {
	for (; ~scanf("%d%d", &left, &right) && (left || right); solve());
}
