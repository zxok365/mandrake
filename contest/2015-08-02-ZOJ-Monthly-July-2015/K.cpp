#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>

using namespace std;

const int N = 111111;

int k, bin[N];
int x[N], y[N], hash[N], len, height[N], rank[N], sa[N], pow10[N], increment[N], sum[N], ans[N];
char str[N];


__inline int get(int left, int right) {
	int result = hash[right] - hash[left - 1] * pow10[right - left + 1];
	result %= k;
	result += k;
	result %= k;
	return result;
}

void sort(int a[], int b[], int c[], int n, int m)
{
	for(int i = 0; i <= m; i++)
		bin[i] = 0;
	for(int i = 1; i <= n; i++)
		bin[c[a[i]]]++;
	for(int i = 1; i <= m; i++)
		bin[i] += bin[i - 1];
	for(int i = n; i >= 1; i--)
		b[bin[c[a[i]]]--] = a[i];
}

void calc_sa()
{
	for(int i = 1; i <= len; i++)
		rank[i] = i, x[i] = str[i];
	sort(rank, sa, x, len, 256);
	rank[sa[1]] = 1;
	for(int i = 2; i <= len; i++)
		rank[sa[i]] = rank[sa[i - 1]] + (x[sa[i]] != x[sa[i - 1]]);
	for(int i = 1; i <= len; i <<= 1)
	{
		for(int j = 1; j <= len; j++)
			sa[j] = j, y[j] = i + j <= len ? rank[i + j] : 0, x[j] = rank[j];
		sort(sa, rank, y, len, len);sort(rank, sa, x, len, len);
		rank[sa[1]] = 1;
		for(int j = 2; j <= len; j++)
			rank[sa[j]] = rank[sa[j - 1]] + (x[sa[j - 1]] != x[sa[j]] || y[sa[j - 1]] != y[sa[j]]);
		if(rank[sa[len]] == len) return ;
	}
}	

void calc_height()
{
	int now = 0;
	for(int i = 1; i <= len; i++)
	{
		if(now > 0) now--;
		if(rank[i] != 1)
			while(str[i + now] == str[sa[rank[i] - 1] + now]) now++;
		height[rank[i]] = now;
	}
}

void solve(void) {
	len = (int)strlen(str + 1);

	pow10[0] = 1;
	for (int i = 1; i <= len; ++i) {
		pow10[i] = pow10[i - 1] * 10 % k;
		hash[i] = (hash[i - 1] * 10 + (str[i] - '0')) % k;
	}
	
	fill(sum, sum + k, 0);
	fill(ans, ans + k, 0);
	
	bool zero = false;
	for (int i = 1; i <= len; ++i) {
		int x = str[i] - '0';
		for (int j = 0; j < k; ++j) {
			increment[j] = 0;
		}
		for (int j = 0; j < k; ++j) {
			increment[(j * 10 + x) % k] += sum[j];
		}
		if (x == 0) {
			zero = true;
		} else {
			increment[x % k]++;
		}
		for (int j = 0; j < k; ++j) {
			sum[j] = increment[j];
			ans[j] += increment[j];
		}
	}
	if (zero) {
		ans[0]++;
	}

	calc_sa(); calc_height();
	
	fill(sum, sum + k, 0);
/*	
	for (int i = 1; i <= len; ++i) {
		printf("%d%s", sa[i], (i == len) ? "\n" : " ");
	}
	for (int i = 1; i <= len; ++i) {
		printf("%d%s", height[i], (i == len) ? "\n" : " ");
	}
*/	
	int last = 0, prev = -1;
	for (int i = 2; i <= len; ++i) {
		int pos = sa[i];

		if (last < height[i]) {
			for (int j = last + 1; j <= height[i]; ++j) {
//printf("%d\n", get(pos, pos + j - 1));
				sum[get(pos, pos + j - 1)]++;
			}
		} else {
			for (int j = last; j > height[i]; --j) {
//printf("%d\n", get(pos, pos + j - 1));
				sum[get(prev, prev + j - 1)]--;
			}
		}
		
		last = height[i];
				
		if (str[pos] != '0') {
			for (int j = 0; j < k; ++j) {
				ans[j] -= sum[j];
			}
		}
		
		prev = pos;
	}
	
	for (int i = 0; i < k; ++i) {
		printf("%d%s", ans[i], (i == k - 1) ? "\n" : " ");
	}
}

int main(void) {
	for (; ~scanf("%s%d", str + 1, &k); solve());
}
