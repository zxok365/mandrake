#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <map>
#include <vector>

using namespace std;
const int function_len = 8;
const int MAXN = 1000;
char s[MAXN];
void get_function(int pos) {
	int pointer;
	for (pointer = pos; str[pointer] != '{'; pointer++);
	stk[++top] = pointer;
	for (int i = pointer + 1; top; i++) {
		if (str[i] == '}') {
			top--;
			continue;
		}
		if (str[i] == 'i' && str[i + 1] == 'f') {
			int getleft, getright;
			for (getleft = i + 3; str[getleft] != '('; getleft++);
			for (getright = getleft + 1; str[getright] != ')'; getright++);
			string tmp;
			tmp.clear();
			for (int j = getleft  + 1; j <= getright - 1; j++) {
				if (str[j] == ' ') {
				
					continue;
				}
				tmp += str[j];
			}
		}
	}	
}
int main() {
	string str;
	while (gets(s + 1)) {
		int len = strlen(s + 1);
		for (int i = 1; i <= len; i++)
		 	str += s[i];
		 str += '#';
	}
	for (int i = 0; i < str.length(); i++)
		putchar(str[i]);
	cout << endl;
	int len = str.length();
	for (int i = 0; i < str.length(); i++) {
		string tmp;
		tmp.clear();
		for (int j = 1; j <= function_len && i + j - 1 < len; j++) {
			tmp += str[j + i - 1];
		}
		if (tmp == "function") {
			get_function(i + function_len);			
		} else continue;
	}
	return 0;
}

