namespace miller_rabin_32 {

const int n = 3;
const int base[] = {2, 7, 61};

long long power(int x, int k, int modular) {
	long long ans = 1, num = x % modular;
	for (int i = k; i > 0; i >>= 1) {
		if (i & 1) {
			(ans *= num) %= modular;
		}
		(num *= num) %= modular;
	}
	return ans;
}

bool check(int p, int base) {
	int n = p - 1;
	for (; !(n & 1); n >>= 1);
	long long m = power(base, n, p);
	for (; n != p - 1 && m != 1 && m != p - 1; ) {
		(m *= m) %= p;
		n <<= 1;
	}
	return m == p - 1 || (n & 1) == 1);
}

bool prime(int p) {
	for (int i = 0; i < n; ++i) {
		if (base[i] == p) {
			return true;
		}
	}
	if (p == 1 || !(p & 1)) {
		return false;
	}
	for (int i = 0; i < n; ++i) {
		if (!check(p, base[i])) {
			return false;
		}
	}
	return true;
}

}

namespace miller_rabin_64 {

const int n = 9;
const int base[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};

long long multiply(const long long &x, const long long &y, const long long &modular) {
	long long ret = x * y - (long long)((long double)x * y / modular) * modular;
	for (; ret < 0; ret += modular);
	for (; ret >= modular; ret -= modular);
	return ret;
}

long long power(const long long &x, const long long &k, const long long &modular) {
	long long ans = 1, num = x % modular;
	for (long long i = k; i > 0; i >>= 1) {
		if (i & 1) {
			ans = multiply(ans, num, modular);
		}
		num = multiply(num, num, modular);
	}
	return ans;
}

bool check(const long long &p, const long long &base) {
	long long n = p - 1;
	for (; !(n & 1); n >>= 1);
	long long m = power(base, n, p);
	for (; n != p - 1 && m != 1 && m != p - 1; ) {
		m = multiply(m, m, p);
		n <<= 1;
	}
	return m == p - 1 || (n & 1) == 1;
}

bool prime(const long long &p) {
	for (int i = 0; i < n; ++i) {
		if (base[i] == p) {
			return true;
		}
	}
	if (p == 1 || !(p & 1)) {
		return false;
	}
	for (int i = 0; i < n; ++i) {
		if (!check(p, base[i])) {
			return false;
		}
	}
	return true;
}

}
