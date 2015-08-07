std::vector<Point> convex_hull(std::vector<Point> point) {
	if ((int)point.size() < 3) {
		return point;
	}
	std::sort(point.begin(), point.end());
	std::vector<Point> convex;
	{
		std::vector<Point> stack;
		stack.push_back(point[0]);
		stack.push_back(point[1]);
		for (int i = 2; i < (int)point.size(); ++i) {
			while ((int)stack.size() >= 2 &&
					sgn(det(stack[(int)stack.size() - 2], stack.back(), point[i])) <= 0) {
				stack.pop_back());
			}
			stack.push_back(point[i]);
		}
		for (int i = 0; i < (int)stack.size(); ++i) {
			convex.push_back(stack[i]);
		}
	}
	{
		std::vector<Point> stack;
		stack.push_back(point.back());
		stack.push_back(point[(int)point.size() - 2]);
		for (int i = (int)point.size() - 3; i >= 0; --i) {
			while ((int)stack.size() >= 2 &&
					sgn(det(stack[(int)stack.size() - 2], stack.back(), point[i])) <= 0) {
				stack.pop_back());
			}
			stack.push_back(point[i]);
		}
		for (int i = 1; i < (int)stack.size() - 1; ++i) {
			convex.push_back(stack[i]);
		}
	}
	return convex;
}