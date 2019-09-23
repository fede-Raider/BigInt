#pragma once
#include <vector>

namespace {
	struct div_ct {
		uint_fast32_t quot;
		uint_fast32_t rem;

		static div_ct Divide(int_fast64_t n, int_fast64_t d) {
			div_ct result;
			result.quot = n / d;
			result.rem = n % d;
			return result;
		}
	};
}

class BigInt {
	typedef uint_fast32_t ELEM_TYPE;
	static const ELEM_TYPE BASE = 1000000000;
	static const ELEM_TYPE DIGIT_COUNT = 9;

	friend std::ostream& operator<<(std::ostream& s, const BigInt& n);
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

	//MOVE (?)
	BigInt(const BigInt&& bi);
	const BigInt& operator=(const BigInt&& bi);

	//MATHS OPERATORS
	BigInt operator+(const BigInt& rhs) const;
	BigInt operator-(const BigInt& rhs) const;
	BigInt operator-() const;
	BigInt operator*(const BigInt& rhs) const;
	BigInt operator/(const BigInt& divisor) const;

	BigInt operator+=(const BigInt& rhs);
	BigInt operator-=(const BigInt& rhs);
	BigInt operator*=(const BigInt& rhs);
	BigInt operator/=(const BigInt& divisor);

	//INCREMENT OPERATORS
	BigInt& operator++();
	BigInt operator++ (int);
	BigInt& operator--();
	BigInt operator-- (int);

	//COMPARISON OPERATORS
	bool operator==(const BigInt& rhs) const;
	bool operator!=(const BigInt& rhs) const;
	bool operator<(const BigInt& rhs) const;
	bool operator<=(const BigInt& rhs) const;
	bool operator>(const BigInt& rhs) const;
	bool operator>=(const BigInt& rhs) const;
private:
	div_ct DivideNumberToBase(int_fast64_t n) const;
	void CheckZero();
	void RemoveUselessZero();
	BigInt abs() const;
private:
	// std::vector<int> number;
	// std::vector<uint32_t> number;
	std::vector<uint_fast32_t> number;
	bool positive = true;
};