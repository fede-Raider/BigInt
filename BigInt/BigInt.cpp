#include "BigInt.h"
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <string>
#include <limits.h>

BigInt::BigInt() : positive(true) {
	number.push_back(0);
}

const BigInt& BigInt::operator++() {
	return *this += 1;
}

BigInt BigInt::operator++(int) {
	BigInt result(*this);
	++(*this);
	return result;
}

const BigInt& BigInt::operator--() {
	return *this -= 1;
}

BigInt BigInt::operator--(int) {
	BigInt result(*this);
	--(*this);
	return result;
}

bool BigInt::operator==(const BigInt & rhs) const {
	return positive == rhs.positive && number == rhs.number;
}

bool BigInt::operator!=(const BigInt & rhs) const {
	return !(*this==rhs);
}

bool BigInt::operator<(const BigInt & rhs) const {
	if (positive && !rhs.positive) {
		return false;
	}
	if (!positive && rhs.positive) {
		return true;
	}

	if (number.size() > rhs.number.size()) {
		return !positive;
	}

	if (number.size() < rhs.number.size()) {
		return positive;
	}

	for (size_t i = number.size(); i > 0; --i) {
		if (number[i-1] < rhs.number[i-1]) {
			return positive;
		}
		if (number[i-1] > rhs.number[i-1]) {
			return !positive;
		}
	}
	return false;
}

bool BigInt::operator<=(const BigInt & rhs) const {
	return *this== rhs || *this < rhs ;
}

bool BigInt::operator>(const BigInt & rhs) const {
	return !(*this < rhs) && (*this != rhs);
}

bool BigInt::operator>=(const BigInt & rhs) const {
	return !(*this < rhs);
}

void BigInt::CheckZero() {
	if (number.size() == 1 && number[0] == 0) {
		positive = true;
	}
}

void BigInt::RemoveUselessZero() {
	for (size_t i = number.size() - 1; i > 0; --i) {
		if (number[i] == 0) {
			number.pop_back();
		} else {
			return;
		}
	}
}

BigInt BigInt::abs() const {
	BigInt result = *this;
	result.positive = true;
	return result;
}

BigInt::BigInt(int i) : positive(i >= 0) {
	if (!positive) {
		i = -i;
	}
	do {
		div_ct dt = div_ct::Divide(i, BASE);
		number.push_back(dt.rem);
		i = dt.quot;
	} while (i != 0);
}

BigInt::BigInt(long i) : positive(i >= 0) {
	if (!positive) {
		i = -i;
	}
	do {
		div_ct dt = div_ct::Divide(i, BASE);
		number.push_back(dt.rem);
		i = dt.quot;
	} while (i != 0);
}

BigInt::BigInt(long long i) : positive(i >= 0) {
	if (!positive) {
		i = -i;
	}
	do {
		div_ct dt = div_ct::Divide(i, BASE);
		number.push_back(dt.rem);
		i = dt.quot;
	} while (i != 0);
}

BigInt::BigInt(unsigned int i) : positive(true) {
	do {
		div_ct dt = div_ct::Divide(i, BASE);
		number.push_back(dt.rem);
		i = dt.quot;
	} while (i != 0);
}

BigInt::BigInt(unsigned long i) : positive(true) {
	do {
		div_ct dt = div_ct::Divide(i, BASE);
		number.push_back(dt.rem);
		i = dt.quot;
	} while (i != 0);
}

BigInt::BigInt(unsigned long long i) : positive(true) {
	do {
		div_ct dt = div_ct::Divide(i, BASE);
		number.push_back(dt.rem);
		i = dt.quot;
	} while (i != 0);
}

BigInt::BigInt(const std::string& s) {
	if (!s.size()) {
		number.push_back(0);
		return;
	}
	size_t index = s[0] != '-' ? 0 : 1;

	if (index && s.size() < 2) {
		positive = true;
		number.push_back(0);
		return;
	}

	for (; index < s.size(); index++) {
		char d = s[index];
		d -= '0';
		*this = (*this * 10) + d;
	}

	positive = s[0] != '-' ? true : false;
	RemoveUselessZero();
	CheckZero();
}

BigInt::BigInt(const char* c) : BigInt(std::string(c)) {
}

BigInt::BigInt(const BigInt & bi) : positive(bi.positive), number(bi.number) {
}

const BigInt & BigInt::operator=(const BigInt & bi) {
	positive = bi.positive;
	number = bi.number;
	return *this;
}

BigInt::BigInt(const BigInt&& bi){
	number = std::move(bi.number);
	positive = bi.positive;
}

const BigInt & BigInt::operator=(const BigInt&& bi) {
	number = std::move(bi.number);
	positive = bi.positive;
	return *this;
}

BigInt BigInt::operator+(const BigInt & rhs) const {
	if (positive == rhs.positive) {
		BigInt result;
		result.positive = positive;
		result.number.pop_back();
		div_ct dt;
		dt.quot = 0;
		for (size_t i = 0; dt.quot || (i < std::max(number.size(), rhs.number.size())); ++i) {
			dt = div_ct::Divide(dt.quot + (i < number.size() ? number[i] : 0) + (i < rhs.number.size() ? rhs.number[i] : 0), BASE);
			result.number.push_back(dt.rem);
		}
		result.RemoveUselessZero();
		result.CheckZero();
		return result;
	}
	return *this - (-rhs);
}

const BigInt& BigInt::operator+=(const BigInt & rhs) {
	*this = *this + rhs;
	return *this;
}

BigInt BigInt::operator-(const BigInt & rhs) const {
	if (positive == rhs.positive) {
		if (abs() >= rhs.abs()) {
			BigInt result = *this;
			for (size_t i = 1; i <= rhs.number.size(); i++) {
				// *this >= rhs
				if (result.number[rhs.number.size() - i] >= rhs.number[rhs.number.size() - i]) {
					result.number[rhs.number.size() - i] -= rhs.number[rhs.number.size() - i];
				} else {
					size_t indexToCarry = rhs.number.size() - i + 1;
					while (!result.number[indexToCarry]) {
						indexToCarry++;
					}
					result.number[indexToCarry]--;
					indexToCarry--;
					for (; indexToCarry > rhs.number.size() - i; indexToCarry--) {
						result.number[indexToCarry] = BASE - 1;
					}
					result.number[indexToCarry] = result.number[indexToCarry] + BASE - rhs.number[indexToCarry];
				}
			}

			result.RemoveUselessZero();
			result.CheckZero();
			return result;
		}
		return -(rhs - *this);
	}
	return *this + (-rhs);
}

const BigInt& BigInt::operator-=(const BigInt & rhs) {
	*this = *this - rhs;
	return *this;
}

BigInt BigInt::operator-() const {
	BigInt result = *this;
	result.positive = !positive;
	return result;
}

BigInt BigInt::operator*(const BigInt& rhs) const {
	BigInt result;
	result.positive = !(positive ^ rhs.positive);
	result.number.resize(number.size() + rhs.number.size(), 0);

	DOUBLE_ELEM_TYPE carry = 0;
	size_t digit = 0;
	for (;; ++digit) {
		div_ct dt = div_ct::Divide(carry, BASE);
		carry = dt.quot;
		result.number[digit] = (ELEM_TYPE)dt.rem;

		bool found = false;
		for (size_t i = digit < rhs.number.size() ? 0 : digit - rhs.number.size() + 1; i < number.size() && i <= digit; ++i) {
			DOUBLE_ELEM_TYPE pval = result.number[digit] + number[i] * (DOUBLE_ELEM_TYPE)rhs.number[digit - i];
			if (pval >= BASE) {
				div_ct dt = div_ct::Divide(pval, BASE);
				carry += dt.quot;
				pval = dt.rem;
			}
			result.number[digit] = (ELEM_TYPE)pval;
			found = true;
		}
		if (!found) {
			break;
		}
	}
	for (; carry > 0; ++digit) {
		div_ct dt = div_ct::Divide(carry, BASE);
		result.number[digit] = (ELEM_TYPE)dt.rem;
		carry = dt.quot;
	}

	result.RemoveUselessZero();
	result.CheckZero();
	return result;
}

const BigInt& BigInt::operator*=(const BigInt & rhs) {
	*this = *this * rhs;
	return *this;
}

BigInt BigInt::operator/(const BigInt& divisor) const {
	return divmod(divisor).first;
}

const BigInt& BigInt::operator/=(const BigInt & rhs) {
	*this = *this / rhs;
	return *this;
}

BigInt BigInt::operator%(const BigInt& divisor) const {
	return divmod(divisor).second;
}

const BigInt & BigInt::operator%=(const BigInt & rhs) {
	*this = *this % rhs;
	return *this;
}

std::string BigInt::ToString() const {
	std::string out = "";
	BigInt copy = *this;
	copy.abs();
	std::pair<BigInt, BigInt> quotres;
	do {
		quotres = copy.divmod(10);
		out = std::to_string(quotres.second.number[0]) + out;
		copy = std::move(quotres.first);
	} while (copy != "0");

	if (!positive) {
		out = "-" + out;
	}

	return out;
}

std::ostream& operator<<(std::ostream &s, const BigInt& bi) {
	s << bi.ToString();
	return s;
}

std::istream & operator>>(std::istream& s, BigInt& n){
	std::string str;
	s >> str;
	n = str;
	return s;
}

BigInt pow(const BigInt& base, const BigInt& exp) {
	if (!exp.positive) {
		return 0;
	}
	BigInt result(1);
	BigInt expCursor(0);
	while (expCursor != exp) {
		result = result * base;
		++expCursor;
	}
	return result;
}

std::pair<BigInt, BigInt> BigInt::divmod(const BigInt& divisor) const {
	BigInt Q, R, D = (divisor.positive ? divisor : -divisor), N = (positive ? *this : -*this);
	Q.number.resize(N.number.size(), 0);
	for (size_t i = N.number.size(); i > 0; --i) {
		R.number.insert(R.number.begin(), N.number[i - 1]);
		R.RemoveUselessZero();

		DOUBLE_ELEM_TYPE min = 0, max = BASE - 1;
		while (max > min) {
			DOUBLE_ELEM_TYPE avg = max + min;
			div_ct dt = div_ct::Divide(avg, 2);

			avg = dt.rem ? (dt.quot + 1) : dt.quot;
			BigInt prod = D * avg;
			if (R == prod) {
				min = avg;
				break;
			}
			else if (R > prod) {
				min = avg;
			}
			else {
				max = avg - 1;
			}
		}
		DOUBLE_ELEM_TYPE cnt = min;

		R -= D * cnt;
		Q.number[i - 1] += cnt;
	}
	Q.RemoveUselessZero();
	Q.CheckZero();
	Q.positive = (Q.number.size() == 1 && Q.number[0] == 0) ? true : (positive == divisor.positive);
	R.positive = positive;
	R.RemoveUselessZero();
	R.CheckZero();
	return std::pair<BigInt, BigInt>(std::move(Q), std::move(R));
}

BigInt BigInt::operator>>(const BigInt& shift) const {
	BigInt result(*this);
	result >>= shift;
	return result;
}

const BigInt& BigInt::operator>>=(const BigInt& shift) {
	if (shift < 0) {
		return *this <<= -shift;
	}

	if (shift / ELEM_BITS >= number.size()) {
		*this = 0;
		return *this;
	}

	BigInt shiftCopy = shift;
	while (shiftCopy >= ELEM_BITS) {
		number.erase(number.begin());
		shiftCopy -= ELEM_BITS;
	}

	ELEM_TYPE carry = 0;
	ELEM_TYPE nextcarry = 0;
	ELEM_TYPE mask = 0;
	for (size_t i = 0; i < shiftCopy.number[0]; i++) {
		mask <<= 1;
		mask |= 1u;
	}
	for (size_t i = number.size(); i > 0; i--) {
		nextcarry = number[i - 1] & mask;
		number[i - 1] >>= shiftCopy.number[0];
		carry <<= ELEM_BITS - shiftCopy.number[0];
		number[i - 1] |= carry;
		carry = nextcarry;
	}

	RemoveUselessZero();
	CheckZero();
	return *this;
}

BigInt BigInt::operator&(const BigInt& other) const {
	BigInt result(*this);
	result &= other;
	return result;
}

const BigInt& BigInt::operator&=(const BigInt& other) {
	size_t j = number.size() > other.number.size() ? number.size() : other.number.size();

	BigInt otherCopy = other;
	for (size_t k = otherCopy.number.size(); k < j; k++) {
		otherCopy.number.push_back(0);
	}
	for (; j > 0; j--) {
		number[j - 1] &= otherCopy.number[j - 1];
	}
	RemoveUselessZero();
	CheckZero();
	return *this;
}

BigInt BigInt::operator|(const BigInt& other) const {
	BigInt result(*this);
	result |= other;
	return result;
}

const BigInt& BigInt::operator|=(const BigInt& other) {
	size_t i = number.size() > other.number.size() ? other.number.size() : number.size();
	size_t j = number.size() > other.number.size() ? number.size() : other.number.size();

	for (size_t k = number.size(); k < j; k++) {
		number.push_back(0);
	}
	for (; i > 0; i--) {
		number[i - 1] |= other.number[i - 1];
	}
	RemoveUselessZero();
	return *this;
}

BigInt BigInt::operator^(const BigInt& other) const {
	BigInt result(*this);
	result ^= other;
	return result;
}

const BigInt& BigInt::operator^=(const BigInt& other) {
	BigInt otherCopy = other;
	if (number.size() > otherCopy.number.size()) {
		for (size_t k = otherCopy.number.size(); k < number.size(); k++) {
			otherCopy.number.push_back(0);
		}
	} else if (number.size() < otherCopy.number.size()) {
		for (size_t k = number.size(); k < otherCopy.number.size(); k++) {
			number.push_back(0);
		}
	}

	for (size_t i = number.size(); i > 0; i--) {
		number[i - 1] ^= otherCopy.number[i - 1];
	}
	RemoveUselessZero();
	CheckZero();
	return *this;
}

BigInt BigInt::operator<<(const BigInt& shift) const {
	BigInt result(*this);
	result <<= shift;
	return result;
}

const BigInt& BigInt::operator<<=(const BigInt& shift) {
	if (shift < 0) {
		return *this >>= -shift;
	}

	BigInt shiftCopy = shift;
	while (shiftCopy >= ELEM_BITS) {
		number.insert(number.begin(), 0);
		shiftCopy -= ELEM_BITS;
	}

	ELEM_TYPE carry = 0;
	ELEM_TYPE nextcarry = 0;
	ELEM_TYPE mask = std::numeric_limits<ELEM_TYPE>::max();
	for (size_t i = 0; i < shiftCopy.number[0]; i++) {
		mask >>= 1;
	}
	mask = ~mask;
	for (size_t i = 0; i < number.size(); i++) {
		nextcarry = number[i] & mask;
		number[i] <<= shiftCopy.number[0];
		carry >>= ELEM_BITS - shiftCopy.number[0];
		number[i] |= carry;
		carry = nextcarry;
	}
	if (carry) {
		carry >>= ELEM_BITS - shiftCopy.number[0];
		number.push_back(carry);
	}

	RemoveUselessZero();
	return *this;
}

BigInt BigInt::operator~() const {
	BigInt result(*this);
	for (size_t i = 0; i < result.number.size(); i++) {
		result.number[i] = ~result.number[i];
	}
	result.RemoveUselessZero();
	result.CheckZero();
	return result;
}
