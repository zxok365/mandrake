#include <cstdio>
#include <cstring>

const char letter[] = "ATCG";

const int N = 111111;

int length;
char text[N];
int counter[256];

int main(void) {
	scanf("%d%s", &length, text);
	for (int i = 0; i < length; ++i) {
		counter[text[i]]++;
	}
	char best = letter[0];
	for (int i = 0; i < 4; ++i) {
		if (counter[best] > counter[letter[i]]) {
			best = letter[i];
		}
	}
	printf("%d\n", counter[best]);
	for (int i = 0; i < length; ++i) {
		putchar(best);
	}
	puts("");
}
