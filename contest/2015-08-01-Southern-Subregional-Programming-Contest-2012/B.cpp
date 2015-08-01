#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

const int N = 2222;

int n;
long long seat;
long long a[N], number[N];

bool check(long long table, long long seat) {
	long long number3 = 0;
	for (int i = 0; i < n; ++i) {
		number[i] = a[i];
		if (number[i] % 2 == 1) {
			number3++;
			number[i] -= 3;
		}
	}
	long long odd = 0, even = table;
	
	if (seat % 2 == 1) {
		seat -= 3;
		
		if (table <= number3) {
			number3 -= table;
			even = table;
		} else {
			for (int i = 0; i < n && number3 < table - 1; ++i) {
				while (number[i] >= 6 && number3 < table - 1) {
					number[i] -= 6;
					number3 += 2;
				}
			}
			
			if (table <= number3) {
				number3 -= table;
				even = table;
			} else {
				odd = table - number3;
				even = number3;
			}
		}
	}

	if (odd > 0) {
		long long total = odd * (seat + 2) + even * seat;
		for (int i = 0;	i < n; ++i) {
			total -= number[i];
		}
		return total >= 0;
	} else {
		long long total = 0;
		for (int i = 0; i < n; ++i) {
			total += number[i];
		}

		for (int i = 0; i < even; ++i) {
			long long rest = seat;
			
			long long counter3 = min(rest / 6 * 2, number3);
			number3 -= counter3;
			rest -= counter3 * 3;
			
			long long counter2 = min(rest / 2, total / 2);
			total -= counter2 * 2;
			rest -= counter2 * 2;
			
			long long counter = min(rest / 3, number3);
			number3 -= counter;
			rest -= counter * 3;
			
			if (number3 <= 0 && total <= 0) {
				return true;
			}
		}
		return false;
	}
}

int main(void) {
	scanf("%d%lld", &n, &seat);
	
	long long total = 0;
	for (int i = 0; i < n; ++i) {
		scanf("%lld", a + i);
		total += a[i];
	}

	long long left = 0, right = total;
	for (; right - left > 1; ) {
		long long mid = left + right >> 1;
		
		if (!check(mid, seat)) {
			left = mid;
		} else {
			right = mid;
		}
	}
	
	printf("%lld\n", right);
}
