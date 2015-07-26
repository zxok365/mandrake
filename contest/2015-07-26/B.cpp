#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

const int N = 1111;

string buffer;
string strl[N], strr[N];

void correct() {
	puts("The figure is correct.");
}

int calc(int x) {
	int ret = 0;
	for (int i = x; i > 0; i >>= 1) {
		if (i & 1) {
			ret += 500;
		} else {
			ret += 250;
		}
	}
	return ret;
}

void shift(string str[], int delta) {
	string temp[N];
	for (int i = 0; i < 7; ++i) {
		temp[i] = str[i];
	}
	for (int i = 0; i < 7; ++i) {
		str[(i + 7 + delta) % 7] = temp[i];
	}
}

void solve(void) {
	int counterl = 0, counterr = 0, linel = 0, liner = 0;
	
	getline(cin, buffer);
	for (int i = 0; i < 7; ++i) {
		getline(cin, buffer);

		strl[i] = strr[i] = "";

		bool left = true;
		for (int j = 0; j < (int)buffer.length(); ++j) {
			if (buffer[j] == '|') {
				left = false;
				continue;
			}
			
			if (left) {
				strl[i] += buffer[j];
			} else {
				strr[i] += buffer[j];
			}
			
			if (buffer[j] == '_') {
				if (left) {
					linel = i;
				} else {
					liner = i;
				}
			}
			
			if (isalpha(buffer[j])) {
				if (left) {
					counterl += calc(buffer[j]);
				} else {
					counterr += calc(buffer[j]);
				}
			}
		}
	}

	//	equal
	if (counterl == counterr) {
		if (linel == liner) {
			correct();
			return;
		}
		if (linel < liner) {
			shift(strl, 1);
			shift(strr, -1);
		} else {
			shift(strl, -1);
			shift(strr, 1);
		}
	}
	
	//	less
	if (counterl < counterr) {
		if (linel < liner) {
			correct();
			return;
		}
		if (linel == liner) {
			shift(strl, -1);
			shift(strr, 1);
		} else {
			shift(strl, -2);
			shift(strr, 2);
		}
	}
	
	//	more
	if (counterl > counterr) {
		if (linel > liner) {
			correct();
			return;
		}
		if (linel == liner) {
			shift(strl, 1);
			shift(strr, -1);
		} else {
			shift(strl, 2);
			shift(strr, -2);
		}
	}
	
	for (int i = 0; i < 7; ++i) {
		printf("%s||%s\n", strl[i].c_str(), strr[i].c_str());
	}
	
}

int main(void) {
	int tests;
	scanf("%d", &tests);
	for (int i = 1; i <= tests; ++i) {
		printf("Case %d:\n", i);
		solve();
	}
}
