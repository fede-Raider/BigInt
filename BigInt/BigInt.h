#pragma once
#include <vector>

namespace {
	struct div_ct {
		uint64_t quot;
		uint64_t rem;

		static div_ct Divide(int_fast64_t n, int_fast64_t d) {
			div_ct result;
			result.quot = n / d;
			result.rem = n % d;
			return result;
		}
	};
}

class BigInt {
	typedef uint32_t ELEM_TYPE;
	typedef uint64_t DOUBLE_ELEM_TYPE;
	static const DOUBLE_ELEM_TYPE BASE = 4294967296;
	static const short int ELEM_BITS = 32;

	friend std::ostream& operator<<(std::ostream& s, const BigInt& n);
	friend std::istream& operator>>(std::istream& s, BigInt &n);
	friend BigInt pow(const BigInt& base, const BigInt& exp);
public:

	//CONSTRUCTORS
	BigInt();
	BigInt(int i);
	BigInt(long i);
	BigInt(long long i);
	BigInt(unsigned int i);
	BigInt(unsigned long i);
	BigInt(unsigned long long i);
	BigInt(const std::string& s);
	BigInt(const char* c);

	//COPY
	BigInt(const BigInt& bi);
	const BigInt& operator=(const BigInt& bi);

	//MOVE
	BigInt(const BigInt&& bi);
	const BigInt& operator=(const BigInt&& bi);

	//MATHS OPERATORS
	BigInt operator+(const BigInt& rhs) const;
	BigInt operator-(const BigInt& rhs) const;
	BigInt operator-() const;
	BigInt operator*(const BigInt& rhs) const;
	BigInt operator/(const BigInt& rhs) const;
	BigInt operator%(const BigInt& rhs) const;

	const BigInt& operator+=(const BigInt& rhs);
	const BigInt& operator-=(const BigInt& rhs);
	const BigInt& operator*=(const BigInt& rhs);
	const BigInt& operator/=(const BigInt& rhs);
	const BigInt& operator%=(const BigInt& rhs);

	//INCREMENT OPERATORS
	const BigInt& operator++();
	BigInt operator++ (int);
	const BigInt& operator--();
	BigInt operator-- (int);

	//COMPARISON OPERATORS
	bool operator==(const BigInt& rhs) const;
	bool operator!=(const BigInt& rhs) const;
	bool operator<(const BigInt& rhs) const;
	bool operator<=(const BigInt& rhs) const;
	bool operator>(const BigInt& rhs) const;
	bool operator>=(const BigInt& rhs) const;

	//BITWISE OPERATORS
	//BigInt operator&(const BigInt& other) const;
	//BigInt operator|(const BigInt& other) const;
	BigInt operator<<(const BigInt &rhs) const;
	BigInt operator>>(const BigInt &rhs)const;

	BigInt operator>>=(const BigInt &rhs);
	BigInt operator<<=(const BigInt &rhs);

private:
	std::pair<BigInt, BigInt> divmod (const BigInt& divisor) const;
	void CheckZero();
	void RemoveUselessZero();
	std::string ToString() const;
	BigInt abs() const;
private:
	std::vector<ELEM_TYPE> number;
	bool positive = true;
};