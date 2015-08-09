#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 2222;

int n, k;
int number[N], counter[N], index[N], a[N];
int maximum[N], best[N][N];

int greedy(std::vector<int> number) {
	int answer = 0;
	for (int i = 0; i < k; ++i) {
		int index = 0;
		for (int j = 0; j < n; ++j) {
			if (number[index] < number[j]) {
				index = j;
			}
		}
		answer += number[index];
		number[index] = 0;
		number[(index + n - 2) % n] += number[(index + n - 1) % n];
		number[(index + 2) % n] += number[(index + 1) % n];
		number[(index + 1) % n] = 0;
		number[(index + n - 1) % n] = 0;
	}
	return answer;
}

int solve(std::vector<int> number, int k) {
	int n = (int)number.size();
	for (int i = 1; i <= n; ++i) {
		a[i] = number[i - 1];
	}
	
	for (int i = 0; i <= k; ++i) {
		maximum[i] = 0;
	}
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= k; ++j) {
			best[i][j] = 0;
		}
	}
	
	best[1][1] = a[1];
	for (int i = 2; i <= n; ++i) {
		for (int j = 1; j <= k; ++j) {
			if (j > 1) {
				best[i][j] = best[i - 2][j - 1] + a[i] + a[i - 1];
			}
			best[i][j] = std::max(best[i][j], maximum[j - 1] + a[i]);
			maximum[j] = std::max(maximum[j], best[i - 2][j]);
		}
	}
	
	int answer = 0;
	for (int i = 2; i <= n; ++i) {
		for (int j = 1; j <= k; ++j) {
			answer = std::max(answer, best[i][j]);
		}
	}
	return answer;
}

int main(void) {
	std::vector<int> value;
	
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; ++i) {
		int number;
		scanf("%d", &number);
		value.push_back(number);
	}
	
	int answer = greedy(value);
	
	{
		std::vector<int> number = value;
		answer = std::max(answer, solve(number, k));
		
		std::reverse(number.begin(), number.end());
		answer = std::max(answer, solve(number, k));
	}
	{
		std::vector<int> number;
		number.push_back(value[1] + value[2]);
		for (int i = 3; i < n - 2; ++i) {
			number.push_back(value[i]);
		}
		number.push_back(value[n - 2] + value[n - 1]);
		answer = std::max(answer, value[0] + solve(number, k - 1));
		
		std::reverse(number.begin(), number.end());
		answer = std::max(answer, value[0] + solve(number, k - 1));
	}
	{
		std::vector<int> number;
		number.push_back(value[2] + value[3]);
		for (int i = 4; i < n - 1; ++i) {
			number.push_back(value[i]);
		}
		number.push_back(value[n - 1] + value[0]);
		answer = std::max(answer, value[1] + solve(number, k - 1));
		
		std::reverse(number.begin(), number.end());
		answer = std::max(answer, value[1] + solve(number, k - 1));
	}
	{
		std::vector<int> number;
		number.push_back(value[0] + value[1]);
		for (int i = 2; i < n - 3; ++i) {
			number.push_back(value[i]);
		}
		number.push_back(value[n - 3] + value[n - 2]);
		answer = std::max(answer, value[n - 1] + solve(number, k - 1));

		std::reverse(number.begin(), number.end());
		answer = std::max(answer, value[n - 1] + solve(number, k - 1));
	}
	
	printf("%d\n", answer);
}
