namespace point_in_polygon {

bool point_on_line(const Point &a, const Point &b, const Point &c) {
	return sgn(det(a - b, c - b)) == 0 && sgn(dot(b - a, c - a)) <= 0;
}

bool point_in_polygon(const Point &p, const vector<Point> &polygon) {
	int counter = 0;
	for (int i = 0; i < (int)polygon.size(); ++i) {
		Point a = polygon[i], b = polygon[(i + 1) % (int)polygon.size()];
		if (point_on_line(p, a, b)) {
			//	Point on the boundary are excluded.
			return false;
		}
		int x = sgn(det(p - a, b - a));
		int y = sgn(a.y - p.y);
		int z = sgn(b.y - p.y);
		counter += (x > 0 && y <= 0 && z > 0);
		counter -= (x < 0 && z <= 0 && y > 0);
	}
	return counter;
}

}
