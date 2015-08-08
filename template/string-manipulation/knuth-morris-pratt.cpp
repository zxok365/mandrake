void build(char *pattern) {
	int length = (int)strlen(pattern + 1);
	fail[0] = -1;
	for (int i = 1, j; i <= length; ++i) {
		for (j = fail[i - 1]; j != -1 && pattern[i] != pattern[j + 1]; j = fail[j]);
		fail[i] = j + 1;
	}
}
