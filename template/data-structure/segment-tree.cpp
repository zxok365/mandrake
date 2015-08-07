const int N = ;

Data data[N << 2];
Tag tag[N << 2];

void cover(int x, const Edit &val) {
		data[x] += val;
		tag[x] += val;
}

void update(int x) {
		data[x] = data[x << 1] + data[x << 1 | 1];
}

void release(int x) {
	if (tag[x]) {
		cover(x << 1, tag[x]);
		cover(x << 1 | 1, tag[x]);
		tag[x] = 0;
	}
}

void edit(int x, int l, int r, int ql, int qr, const Edit &val) {
	if (qr < l || r < ql) {
		return;
	}
	if (ql <= l && r <= qr) {
		cover(x, val);
		return;
	}
	release(x);
	int mid = l + r >> 1;
	edit(x << 1, l, mid, ql, qr, val);
	edit(x << 1 | 1, mid + 1, r, ql, qr, val);
	update(x);
}

Ans query(int x, int l, int r, int ql, int qr) {
	if (qr < l || r < ql) {
		return 0;
	}
	if (ql <= l && r <= qr) {
		return data[x];
	}
	release(x);
	Ans ans = 0;
	int mid = l + r >> 1;
	ans += query(x << 1, l, mid, ql, qr);
	ans += query(x << 1 | 1, mid + 1, r, ql, qr);
	return ans;
}

void build(int x, int left, int right) {
	tag[x] = 0;
	if (left == right) {
		data[x] = 0;
	} else {
		int mid = left + right >> 1;
		build(x << 1, left, mid);
		build(x << 1 | 1, mid + 1, right);
		update(x);
	}
}