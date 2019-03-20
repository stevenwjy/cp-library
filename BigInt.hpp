/*
	BigInt implementation for C++
	Implementation is not owned by me, but I have made some modification to the original code.

	I lost the reference to the original code, feel free to contact me if you know it :)
*/

class BigInt {
private:
	static const int BASE = 100000000, LEN = 8;
	bool negative;
	std::vector<int> a;
	BigInt& normalize();
public:
	BigInt(int x = 0);
	BigInt(const std::string& s);
	BigInt& operator = (const BigInt& x);
	BigInt& operator = (int x);
	BigInt& operator = (const std::string& s);
	const bool operator < (const BigInt& x) const;
	const bool operator > (const BigInt& x) const;
	const bool operator <= (const BigInt& x) const;
	const bool operator >= (const BigInt& x) const;
	const bool operator != (const BigInt& x) const;
	const bool operator == (const BigInt& x) const;
	BigInt operator -() const;
	BigInt& operator += (const BigInt& x);
	BigInt& operator -= (const BigInt& x);
	BigInt& operator *= (const BigInt& x);
	BigInt& operator /= (const BigInt& x);
	BigInt& operator %= (const BigInt& x);
	const BigInt operator + (const BigInt& x) const;
	const BigInt operator - (const BigInt& x) const;
	const BigInt operator * (const BigInt& x) const;
	const BigInt operator / (const BigInt& x) const;
	const BigInt operator % (const BigInt& x) const;
	friend std::pair<BigInt,BigInt> divmod(const BigInt& lhs, const BigInt& rhs);
	friend std::istream& operator >> (std::ostream& is, BigInt& x); //適当実装
	friend std::ostream& operator << (std::ostream& os, const BigInt& x);
	friend const BigInt abs(BigInt x);
};
BigInt& BigInt::normalize() {
	int i = a.size()-1;
	while (i >= 0 && a[i] == 0) --i;
	a.resize(i+1);
	if (a.size() == 0) negative = false;
	return *this;
}
BigInt::BigInt(int x) : negative(x<0) {
	x = abs(x);
	for (; x > 0; x /= BASE) a.push_back(x % BASE);
}
BigInt::BigInt(const std::string& s): negative(false) {
	int p = 0;
	if (s[p] == '-') { ++p; negative = true; }
	else if (s[p] == '+') { ++p; }
	for (int i = s.size()-1, v = BASE; i >= p; --i, v*=10) {
		int x = s[i]-'0';
		if (x < 0 || 9 < x) {
			std::cerr<<"error: parse error:"<<s<<std::endl;
			exit(1);
		}
		if (v == BASE) {
			v = 1;
			a.push_back(x);
		} else a.back() += (x)*v;
	}
	normalize();
}
BigInt& BigInt::operator = (const BigInt& x) {
	negative = x.negative;
	a = x.a;
	return *this;
}
BigInt& BigInt::operator = (int x) { return *this = BigInt(x); }
BigInt& BigInt::operator = (const std::string& s) { return *this = BigInt(s); }
const bool BigInt::operator < (const BigInt& x) const {
	if (negative != x.negative) return negative < x.negative;
	if (a.size() != x.a.size()) return (a.size() < x.a.size())^negative;
	for(int i = a.size()-1; i >= 0; --i)
		if (a[i] != x.a[i]) return (a[i] < x.a[i])^negative;
	return false;
}
const bool BigInt::operator > (const BigInt& x) const { return x<(*this); }
const bool BigInt::operator <= (const BigInt& x) const { return !(x<(*this)); }
const bool BigInt::operator >= (const BigInt& x) const { return !((*this)<x); }
const bool BigInt::operator != (const BigInt& x) const { return (*this)<x || x<(*this); }
const bool BigInt::operator == (const BigInt& x) const { return !((*this)<x || x<(*this)); }
BigInt BigInt::operator -() const {
	BigInt ret(*this);
	if (a.size()) ret.negative = !ret.negative;
	return ret;
}
BigInt& BigInt::operator += (const BigInt& x) {
	if (negative != x.negative) return *this -= -x;
	if (a.size() < x.a.size()) a.resize(x.a.size());
	int tmp = 0;
	for (int i = 0; i < a.size(); ++i) {
		a[i] += (i<x.a.size()?x.a[i]:0) + tmp;
		tmp = a[i] / BASE;
		a[i] %= BASE;
	}
	if (tmp) a.push_back(1);
	return *this;
}
BigInt& BigInt::operator -= (const BigInt& x) {
	if (negative != x.negative) return *this += -x;
	std::vector<int> b(x.a);
	if ((*this < x) ^ negative) {
		a.swap(b);
		negative = !negative;
	}
	for (int i = 0, tmp = 0; i < a.size(); ++i) {
		a[i] += BASE - (i<b.size()?b[i]:0) + tmp;
		tmp = a[i] / BASE - 1;
		a[i] %= BASE;
	}
	return this->normalize();
}
BigInt& BigInt::operator *= (const BigInt& x) {
	negative ^= x.negative;
	std::vector<int> c(a.size()*x.a.size()+1);
	for (int i = 0; i < a.size(); ++i) {
		long long tmp = 0;
		for (int j = 0; j < x.a.size(); ++j) {
			long long v = (long long)a[i] * x.a[j] + c[i+j] + tmp;
			tmp = v / BASE;
			c[i+j] = (int)(v % BASE);
		}
		if (tmp) c[i+x.a.size()] += (int)tmp;
	}
	a.swap(c);
	return this->normalize();
}
BigInt& BigInt::operator /= (const BigInt& x) {
	return *this = divmod(*this,x).first;
}
BigInt& BigInt::operator %= (const BigInt& x) {
	return *this = divmod(*this,x).second;
}
const BigInt BigInt::operator + (const BigInt& x) const {
	BigInt res(*this); return res += x;
}
const BigInt BigInt::operator - (const BigInt& x) const {
	BigInt res(*this); return res -= x;
}
const BigInt BigInt::operator * (const BigInt& x) const {
	BigInt res(*this); return res *= x;
}
const BigInt BigInt::operator / (const BigInt& x) const {
	BigInt res(*this); return res /= x;
}
const BigInt BigInt::operator % (const BigInt& x) const {
	BigInt res(*this); return res %= x;
}
std::pair<BigInt,BigInt> divmod(const BigInt& lhs, const BigInt& rhs) {
	if (!rhs.a.size()) {
		std::cerr<<"error: division by zero"<<std::endl;
		exit(1);
	}
	BigInt x(abs(rhs)), q, r;
	for (int i = lhs.a.size()-1; i >= 0; --i) {
		r = r * BigInt::BASE + lhs.a[i];
		int head = 0, tail = BigInt::BASE;
		if (r >= x) {
			while (head + 1 < tail) {
				int mid = (head + tail) / 2;
				if (x * BigInt(mid) > r) tail = mid;
				else head = mid;
			}
			r -= x * head;
		}
		q.a.push_back(head);
	}
	reverse(q.a.begin(), q.a.end());
	bool neg = lhs.negative ^ lhs.negative;
	q.negative = neg; r.negative = neg;
	return std::make_pair(q.normalize(), r.normalize());
}
std::istream& operator >> (std::istream& is, BigInt& x) {
	std::string tmp; is >> tmp;
	x = BigInt(tmp);
	return is;
}
std::ostream& operator << (std::ostream& os, const BigInt& x) {
	if (x.negative) os << '-';
	if (!x.a.size()) os << 0;
	else os << x.a.back();
	for (int i = x.a.size()-2; i >= 0; --i) {
		os.width(BigInt::LEN);
		os.fill('0');
		os << x.a[i];
	}
	return os;
}
const BigInt abs(BigInt x) {
	x.negative = false;
	return x;
}
