#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

using namespace std;

int n, m;
map<vector<string>, int> table;

int main(void) {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		vector<string> element;
		
		int counter;
		for (scanf("%d", &counter); counter--; ) {
			static char buffer[111111];
			scanf("%s", buffer);
			element.push_back(buffer);
		}
		
		sort(element.begin(), element.end());
		
		for (int mask = 0; mask < (1 << (int)element.size()); ++mask) {
			vector<string> list;
			for (int j = 0; j < (int)element.size(); ++j) {
				if (mask >> j & 1) {
					list.push_back(element[j]);
				}
			}
			table[list]++;
		}
	}
	
	scanf("%d", &m);
	for (int i = 0; i < m; ++i) {
		vector<string> element;
		
		int counter;
		for (scanf("%d", &counter); counter--; ) {
			static char buffer[111111];
			scanf("%s", buffer);
			element.push_back(buffer);
		}
		
		sort(element.begin(), element.end());
		
		printf("%d\n", table[element]);
	}
}
