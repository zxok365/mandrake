#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>

using namespace std;

int k;
string crib1, crib2, cipher;

char calc(char a, char b) {
	char result = a - (b - 'A' + 1);
	if (result < 'A') {
		result += 26;
	}
	return result;
}

string decipher(const string &key) {
	string result(cipher);
	for (int i = 0; i < (int)cipher.length(); ++i) {
		result[i] = calc(cipher[i], key[i % (int)key.length()]);
	}
	return result;
}

void get(multimap<string, int> &list, const string &crib, int len) {
	list.clear();
	string key(len, ' ');
	for (int i = 0; i + (int)crib.length() - 1 < (int)cipher.length(); ++i) {
		for (int j = 0; j < len; ++j) {
			key[(i + j) % len] = calc(cipher[i + j], crib[j]);
		}
		bool satisfy = true;
		for (int j = len; j < (int)crib.length(); ++j) {
			if (calc(cipher[i + j], crib[j]) != key[(i + j) % len]) {
				satisfy = false;
				break;
			}
		}
		if (satisfy) {
			list.insert(make_pair(key, i));
		}
	}
}

multimap<string, int> list1, list2;

void solve(void) {
	cin >> crib1 >> crib2 >> cipher;
	
	string answer;
	for (int len = 1; len <= k; ++len) {
		get(list1, crib1, len);
		get(list2, crib2, len);
		for (multimap<string, int>::const_iterator iter1 = list1.begin(); iter1 != list1.end(); ++iter1) {
			pair<multimap<string, int>::const_iterator, multimap<string, int>::const_iterator> range = list2.equal_range(iter1->first);
			for (multimap<string, int>::const_iterator iter2 = range.first; iter2 != range.second; ++iter2) {
				if (iter1->second + (int)crib1.length() - 1 < iter2->second || iter2->second + (int)crib2.length() - 1 < iter1->second) {
					if (answer == "") {
						answer = iter1->first;
					} else if (iter1->first != answer && decipher(answer) != decipher(iter1->first)){
						cout << "ambiguous" << endl;
						return;
					}
				}
			}
		}
	}
	if (answer == "") {
		cout << "impossible" << endl;
	} else {
		cout << decipher(answer) << endl;
	}
}

int main(void) {
	ios::sync_with_stdio(false);
	for (; cin >> k && k; solve()); 
}
