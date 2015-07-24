namespace convex_hull {

vector<Point> convex_hull(vector<Point> point) {
	int n = (int)point.size();
	if (n <= 1) {
		return point;
	}
	sort(point.begin(), point.end());
	vector<Point> convex;
	{
		vector<Point> stack;
		stack.push_back(point[0]);
		stack.push_back(point[1]);
		for (int i = 2; i < n; ++i) {
			for (; (int)stack.size() >= 2 && sgn(det(stack[(int)stack.size() - 2], stack.back(), point[i])) <= 0; stack.pop_back());
			stack.push_back(point[i]);
		}
		for (int i = 0; i < (int)stack.size(); ++i) {
			convex.push_back(stack[i]);
		}
	}
	{
		vector<Point> stack;
		stack.push_back(point[n - 1]);
		stack.push_back(point[n - 2]);
		for (int i = n - 3; i >= 0; --i) {
			for (; (int)stack.size() >= 2 && sgn(det(stack[(int)stack.size() - 2], stack.back(), point[i])) <= 0; stack.pop_back());
			stack.push_back(point[i]);
		}
		for (int i = 1; i < (int)stack.size() - 1; ++i) {
			convex.push_back(stack[i]);
		}
	}
	return convex;
}

}
