void build(char *text) {
	int length = (int)strlen(text + 1);
	fail[0] = -1;
	for (int i = 1, j; i <= length; ++i) {
		for (j = fail[i - 1]; j != -1 && text[i] != text[j + 1]; j = fail[j]);
		fail[i] = j + 1;
	}
}
