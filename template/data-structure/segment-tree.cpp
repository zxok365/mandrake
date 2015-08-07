void modify(int x, int value) {
	data[x] += value;
	tag[x] += value;
}

void update(int x) {
	data[x] = data[x << 1] + data[x << 1 | 1];
}

void release(int x) {
	if (tag[x]) {
		modify(x << 1, tag[x]);
		modify(x << 1 | 1, tag[x]);
		tag[x] = 0;
	}
}

void edit(int x, int l, int r, int ql, int qr, int value) {
	if (qr < l || r < ql) {
		return;
	}
	if (ql <= l && r <= qr) {
		modify(x, value);
		return;
	}
	release(x);
	int mid = l + r >> 1;
	edit(x << 1, l, mid, ql, qr, value);
	edit(x << 1 | 1, mid + 1, r, ql, qr, value);
	update(x);
}

int query(int x, int l, int r, int ql, int qr) {
	if (qr < l || r < ql) {
		return 0;
	}
	if (ql <= l && r <= qr) {
		return data[x];
	}
	release(x);
	int mid = l + r >> 1;
	return query(x << 1, l, mid, ql, qr) + query(x << 1 | 1, mid + 1, r, ql, qr);
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