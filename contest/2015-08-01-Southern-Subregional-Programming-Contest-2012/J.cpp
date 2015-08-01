#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n ,t1, t2;

int main() {
	scanf("%d%d%d", &n, &t1, &t2);
	
	int time = 1;
	int counter = 0;
	bool stop1 = false, stop2 = false;
	for (; !stop1 || !stop2; time++) {
		if (!stop1 && time % t1 == 0) {
			counter++;
		}
		if (!stop2 && time % t2 == 0) {
			counter++;
		}
		if (time % t1 == 0 && counter >= n) {
			stop1 = true;
		}
		if (time % t2 == 0 && counter >= n) {
			stop2 = true;
		}
	}
	
	cout << counter << " " << time - 1 << endl;
	return 0;
}
