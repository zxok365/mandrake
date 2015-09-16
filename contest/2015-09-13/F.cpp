#include <cstdio>
#include <cstring>
#include <algorithm>

const unsigned long long MAGIC = 4423;

const int N = 444444;

int length;
char text[N], reverse[N];
unsigned long long hash[N], magic[N];

int solve(char *text, int length) {
    int i = 0, j = 1, delta = 0;
    while (i < length && j < length && delta < length) {
        int tokeni = -(int)text[(i + delta) % length];
        int tokenj = -(int)text[(j + delta) % length];
        if (tokeni == tokenj) {
            delta++;
        } else {
            if (tokeni > tokenj) {
                i += delta + 1;
            } else {
                j += delta + 1;
            }
            if (i == j) {
                j++;
            }
            delta = 0;
        }
    }
    return std::min(i, j);
}

unsigned long long get(int left, int right) {
	if (left == 0) {
		return hash[right];
	} else {
		return hash[right] - hash[left - 1] * magic[right - left + 1];
	}
}

void solve(void) {
	scanf("%d%s", &length, text);
	for (int i = 0; i < length; ++i) {
		reverse[i] = text[length - 1 - i];
	}
	
	int pos1 = solve(text, length);
	int pos2 = solve(reverse, length);
	
	bool equal = true, more;
	for (int i = 0; i < length; ++i) {
		int a = (pos1 + i) % length;
		int b = (pos2 + i) % length;
		if (text[a] != reverse[b]) {
			equal = false;
			more = (text[a] > reverse[b]);
			break;
		}
	}
	
	for (int i = 0; i < length; ++i) {
		reverse[i + length] = reverse[i];
	}

	hash[0] = reverse[0];
	magic[0] = 1;
	for (int i = 1; i < length + length; ++i) {
		hash[i] = hash[i - 1] * MAGIC + reverse[i];
		magic[i] = magic[i - 1] * MAGIC;
	}

	for (int i = 0; i < length; ++i) {
		if (get(i, i + length - 1) == get(pos2, pos2 + length - 1)) {
			if (i > pos2) {
				pos2 = i;
			}
		}
	}
	
	pos2 = length - 1 - pos2;
	
	if (equal) {
		if (pos1 <= pos2) {
			printf("%d 0\n", pos1 + 1);
		} else {
			printf("%d 1\n", pos2 + 1);
		}
	} else {
		if (more) {
			printf("%d 0\n", pos1 + 1);
		} else {
			printf("%d 1\n", pos2 + 1);
		}
	}
}

int main(void) {
	int tests;
	for (scanf("%d", &tests); tests--; solve());
}
