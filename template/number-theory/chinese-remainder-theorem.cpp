bool solve(int n, long long r[], long long m[], long long &remainder, long long &modular) {
	remainder = modular = 1;
	for (int i = 0; i < n; ++i) {
		long long x, y;
		euclid(modular, m[i], x, y);
		long long divisor = gcd(modular, m[i]);
		if ((r[i] - remainder) % divisor) {
			return false;
		}
		x *= (r[i] - remainder) / divisor;
		((x %= m[i]) += m[i]) %= m[i];
		remainder += modular * x;
		modular *= m[i] / divisor;
		((remainder %= modular) += modular) %= modular;
	}
	return true;
}