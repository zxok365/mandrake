#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

int priority[256];
char text[111111];
std::vector<int> stacknum;
std::vector<char> stackop;

void process(void) {
	int y = stacknum.back(); stacknum.pop_back();
	int x = stacknum.back(); stacknum.pop_back();
	if (stackop.back() == '+') {
		stacknum.push_back(x + y);
	} else if (stackop.back() == '-') {
		stacknum.push_back(x - y);
	} else if (stackop.back() == '*') {
		stacknum.push_back(x * y);
	} else if (stackop.back() == '/') {
		stacknum.push_back(x / y);
	} else if (stackop.back() == '%') {
		stacknum.push_back(x % y);
	}
	stackop.pop_back();
}

void solve(void) {
	stacknum.clear();
	stackop.clear();
	
	gets(text);
	int length = (int)strlen(text);
	for (int i = 0, j; i < length; i = j) {
		if (text[i] == ' ') {
			j = i + 1;
		} else if (isdigit(text[i])) {
			int number = 0;
			for (j = i; j < length && isdigit(text[j]); ++j) {
				number = number * 10 + text[j] - '0';
			}
			stacknum.push_back(number);
		} else {
			for (; !stackop.empty() && priority[stackop.back()] >= priority[text[i]]; process());
			stackop.push_back(text[i]);
			j = i + 1;
		}
	}
	for (; !stackop.empty(); process());
	printf("%d\n", stacknum.back());
}

int main(void) {
	priority['*'] = priority['/'] = priority['%'] = 2;
	priority['+'] = priority['-'] = 1;
	
	int tests;
	for (scanf("%d\n", &tests); tests--; solve());
}
