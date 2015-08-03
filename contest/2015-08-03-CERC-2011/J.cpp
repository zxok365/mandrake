#include <iostream>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int MAXN = 200000;
char key[MAXN], code[MAXN];
int main() {
	while (scanf("%s",key + 1) && key[1] != '0') {
		scanf("%s", code + 1);
		int len1 = strlen(key + 1);
		int len2 = strlen(code + 1);
		for (int i = 1; i <= len2; i++) {
			char ch;
			int pos = i % len1;
			if (!pos) pos = len1;
			ch = code[i] - 'A' + 1 + key[pos];
			if (ch > 'Z') ch -= 26;
			putchar(ch);
		}
		puts("");
	}

	return 0;
}

