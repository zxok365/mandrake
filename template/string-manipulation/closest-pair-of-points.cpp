namespace closest_pair_of_points {

const int N = ;

int n;
Point points[N];

__inline bool compare(int i, int j) {
	return sgn(points[i].y - points[j].y) < 0;
}

double solve(int left, int right) {
	if (left == right) {
		return INF;
	}
	if (left + 1 == right) {
		return dist(points[left], points[right]);
	}
	int mid = left + right >> 1;
	double len = min(solve(left, mid), solve(mid + 1, right));
	vector<int> idx;
	for (int i = left; i <= right; ++i) {
		if (points[mid].x - points[i].x <= len) {
			idx.push_back(i);
		}
	}
	sort(idx.begin(), idx.end(), compare);
	for (int i = 0; i < (int)idx.size(); ++i) {
		for (int j = i + 1; j < (int)idx.size(); ++j) {
			int a = idx[i], b = idx[j];
			if (points[b].y - points[a].y >= len) {
				break;
			}
			len = min(len, dist(a, b));
		}
	}
	return len;
}

}
