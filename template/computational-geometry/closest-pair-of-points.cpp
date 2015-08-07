bool comparex(const Point &a, const Point &b) {
	return sgn(a.x - b.x) < 0;
}

bool comparey(const Point &a, const Point &b) {
	return sgn(a.y - b.y) < 0;
}

double solve(Point point[], int left, int right) {
	if (left == right) {
		return INF;
	}
	if (left + 1 == right) {
		return dist(point[left], point[right]);
	}
	int mid = left + right >> 1;
	double result = min(solve(left, mid), solve(mid + 1, right));
	vector<Point> candidate;
	for (int i = left; i <= right; ++i) {
		if (point[mid].x - point[i].x <= result) {
			candidate.push_back(point[i]);
		}
	}
	sort(candidate.begin(), candidate.end(), compare);
	for (int i = 0; i < (int)candidate.size(); ++i) {
		for (int j = i + 1; j < (int)candidate.size(); ++j) {
			int a = index[i], b = index[j];
			if (points[b].y - points[a].y >= result) {
				break;
			}
			result = min(result, dist(point[a], point[b]));
		}
	}
	return result;
}

double solve(Point point[], int length) {
	return solve(point, 1, length);
}