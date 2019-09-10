#include "BigInt.h"
#include <iomanip>
#include <algorithm>

BigInt::BigInt() : positive(true) {
	number.push_back(0);
}

BigInt& BigInt::operator++() {
	if (positive) {
		auto it = number.begin();
		while (it != number.end()) {
			++(*it);
			if (*it == BASE) {
				*it = 0;
				it++;
			}
			else {
				break;
			}

		}
		if (it == number.end()) {
			number.push_back(1);
		}
	}
	else {
		positive = !positive;
		(*this).operator--();
		positive = !positive;
	}
	CheckZero();
	return *this;
}

BigInt BigInt::operator++(int) {
	BigInt result(*this);
	++(*this);
	return result;
}

BigInt & BigInt::operator--() {
	if (!positive) {
		positive = !positive;
		(*this).operator++();
		positive = !positive;
	}
	else {
		auto it = number.begin();
		while (it != number.end()) {
			--(*it);
			if (*it > BASE) {
				if((it + 1) != number.end()){
					*it = 999999999;
					it++;
				} else {
					positive = !positive;
					*it = 1;
					it++; //IN REALTA E' GIUSTO: mancava questa riga
				}
			} else {
				if (number.size() > 1 && *it == 0 && (it + 1) == number.end()) {
					number.pop_back();
				}
				break;
			}
		}
	}
	CheckZero();
	return *this;
}

BigInt BigInt::operator--(int) {
	BigInt result(*this);
	--(*this);
	return result;
}

bool BigInt::operator==(const BigInt & rhs) const {
	if (positive != rhs.positive || number.size() != rhs.number.size()) {
		return false;
	}
	for (size_t i = number.size(); i > 0; --i) {
		if (number[i-1] != rhs.number[i-1]) {
			return false;
		}
	}
	return true;
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

div_t BigInt::DivideNumberToBase(int_fast64_t i) const {
	div_t result;
	result.quot = i / BASE;
	result.rem = i % BASE;
	return result;
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
		div_t dt = DivideNumberToBase(i);
		number.push_back(dt.rem);
		i = dt.quot;
	} while (i != 0);
}

BigInt::BigInt(long i) : positive(i >= 0) {
	if (!positive) {
		i = -i;
	}
	do {
		div_t dt = DivideNumberToBase(i);
		number.push_back(dt.rem);
		i = dt.quot;
	} while (i != 0);
}

BigInt::BigInt(long long i) : positive(i >= 0) {
	if (!positive) {
		i = -i;
	}
	do {
		div_t dt = DivideNumberToBase(i);
		number.push_back(dt.rem);
		i = dt.quot;
	} while (i != 0);
}

BigInt::BigInt(unsigned int i) : positive(true) {
	do {
		div_t dt = DivideNumberToBase(i);
		number.push_back(dt.rem);
		i = dt.quot;
	} while (i != 0);
}

BigInt::BigInt(unsigned long i) : positive(true) {
	do {
		div_t dt = DivideNumberToBase(i);
		number.push_back(dt.rem);
		i = dt.quot;
	} while (i != 0);
}

BigInt::BigInt(unsigned long long i) : positive(true) {
	do {
		div_t dt = DivideNumberToBase(i);
		number.push_back(dt.rem);
		i = dt.quot;
	} while (i != 0);
}

BigInt::BigInt(const std::string& s) {
	positive = s[0] != '-' ? true : false;
	int slot = s.size() / DIGIT_COUNT + 1;

	number.reserve(slot);
	for (size_t i = 1; i < slot; ++i) {
		number.push_back(atoi(s.substr(s.size() - i * DIGIT_COUNT, DIGIT_COUNT).c_str()));
	}

	if (positive) {
		if (s.size() % DIGIT_COUNT != 0) {
			number.push_back(atoi(s.substr(0, s.size() % DIGIT_COUNT).c_str()));
		}
	}
	else {
		if ((s.size() - 1) % DIGIT_COUNT != 0) {
			number.push_back(atoi(s.substr(1, (s.size() - 1) % DIGIT_COUNT).c_str()));
		}
	}
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

const BigInt & BigInt::operator=(const BigInt&& bi){
	number = std::move(bi.number);
	positive = bi.positive;
	return *this;
}


BigInt BigInt::operator+(const BigInt & rhs) const {
	if (positive == rhs.positive) {
		BigInt result;
		result.positive = positive;
		result.number.pop_back();
		div_t dt;
		dt.quot = 0;
		for (size_t i = 0; dt.quot || (i < std::max(number.size(), rhs.number.size())); ++i) {
			dt = DivideNumberToBase(dt.quot + (i < number.size() ? number[i] : 0) + (i < rhs.number.size() ? rhs.number[i] : 0));
			result.number.push_back(dt.rem);
		}
		//FORSE INUTILI
		result.RemoveUselessZero();
		result.CheckZero();
		//
		return result;
	}
	return *this - (-rhs);
}

BigInt BigInt::operator-(const BigInt & rhs) const {
	if (positive == rhs.positive) {
		if (abs() >= rhs.abs()) {
			BigInt result;
			result.positive = positive;
			result.number.pop_back();
			div_t dt;
			dt.quot = 0;
			//in questo blocco if sono già nella situazione in cui il primo numero è maggiore nel secondo: le due size saranno al più uguali
			//dt.quot || (i < std::max(number.size(), rhs.number.size()))
			for (size_t i = 0; dt.quot || (i < number.size()); ++i) {
				dt.rem = (i < number.size() ? number[i] : 0) - (i < rhs.number.size() ? rhs.number[i] : 0) - dt.quot;
				//
				if (dt.rem >= 0) {
					result.number.push_back(dt.rem);
					dt.quot = 0;
				}
				else {
					result.number.push_back(BASE  + dt.rem ); // quando dt.rem è minore di 0, il suo valore numerico è quello che devo sottrarre a 1 000 000 000
					dt.quot = 1;
				}
				//dt = DivideNumberToBase(-dt.quot + (i < number.size() ? number[i] : 0) - (i < rhs.number.size() ? rhs.number[i] : 0));
				//result.number.push_back(dt.rem);
			}
			result.RemoveUselessZero();
			result.CheckZero();
			return result;
		}
		return -(rhs - *this);
	}
	return *this + (-rhs);
}


BigInt BigInt::operator-() const {
	BigInt result = *this;
	result.positive = !positive;
	return result;
}
BigInt BigInt::operator*(const BigInt& rhs) const {
	BigInt result;
	result.positive = !(positive ^ rhs.positive);

	//auto it = number.begin(); it != number.end(); it++
	//auto rhsit = rhs.number.begin(); rhsit != rhs.number.end(); rhsit++
	//(*rhsit) *(*it)
	div_t dt;
	div_t dt2;
	for (size_t i = 0; i < number.size();i++) {

		for (size_t j = 0; j < rhs.number.size(); j++) {
			dt.quot = 0;
			dt.rem = 0;
			dt = DivideNumberToBase(((int_fast64_t)number[i]) * ((int_fast64_t)rhs.number[j]));
			if (i + j >= result.number.size()) {
				result.number.push_back(dt.rem);
			}
			else
			{
				result.number[i + j] += dt.rem;
				dt2.quot = 0;
				dt2.rem = 0;
				if (result.number[i + j] > BASE) {
					dt2 = DivideNumberToBase(result.number[i + j]);
					result.number[i + j] = dt2.rem;
					if (i + j + 1 >= result.number.size()) {
						result.number.push_back(dt2.quot);
					}
					else {
						result.number[i + j + 1] += dt2.quot;

					}
				}
			}
			if (dt.quot != 0) {

				if (i + j + 1 >= result.number.size()) {
					result.number.push_back(dt.quot);
				}
				else {
					result.number[i + j + 1] += dt.quot;
					dt2.quot = 0;
					dt2.rem = 0;
					if (result.number[i + j + 1] > BASE) {
						dt2 = DivideNumberToBase(result.number[i + j + 1]);
						result.number[i + j + 1] = dt2.rem;
						if (i + j + 2 >= result.number.size()) {
							result.number.push_back(dt2.quot);
						}
						else {
							result.number[i + j + 2] += dt2.quot;

						}
					}
				}
			}
		}
	}
	result.RemoveUselessZero();
	result.CheckZero();
	return result;
}
BigInt BigInt::operator/(const BigInt& divisor) const 
{
	BigInt quotient =BigInt();
	BigInt remainder = BigInt();

	quotient.positive = (positive && divisor.positive) || ((!positive) && (!divisor.positive));
	remainder.positive = quotient.positive;

	BigInt absDividend = abs();
	BigInt absDivisor = divisor.abs();

	if (absDivisor < absDividend)
	{  
		//there should be the division algorithm: we have only two cases, equal sizes or different ones
		//let's save in the remainder the only dividend numbers starting from index 'absDivisor.number.size() - 1'
		//size_t i = absDivisor.number.size() - 1;
		//absDivisor.number[absDivisor.number.size() - 1];
		BigInt tempRemainder = BigInt();
		BigInt tempQuotient = BigInt();
		BigInt tempQuotientInv = BigInt();

		tempRemainder.number[0] = absDividend.number[absDivisor.number.size() - 1];
		for (size_t i = absDivisor.number.size(); i < absDividend.number.size(); i++)
		{
			tempRemainder.number.push_back(absDividend.number[i]);
		}
		uint_fast32_t tempDivisor = absDivisor.number[absDivisor.number.size() - 1];

		while (absDivisor <= tempRemainder.abs())
		{

			size_t i = tempRemainder.number.size() - 1;

			lldiv_t intermediateResult;
			long long tempDividend = tempRemainder.number[i];

			intermediateResult.quot = tempDividend / tempDivisor;
			intermediateResult.rem = tempDividend % tempDivisor;
			div_t intermediateQuotToStore;
			tempQuotientInv.number[0] = intermediateResult.quot;
			while (i > 0)
			{
				--i;
				tempDividend = intermediateResult.rem * BASE + tempRemainder.number[i];
				intermediateResult.quot = tempDividend / tempDivisor;
				intermediateResult.rem = tempDividend % tempDivisor;
				intermediateQuotToStore = DivideNumberToBase(intermediateResult.quot);

				tempQuotientInv.number[tempQuotient.number.size() - 1] += intermediateQuotToStore.quot;
				tempQuotientInv.number.push_back(intermediateQuotToStore.rem);
			}

			std::vector<uint_fast32_t>::reverse_iterator it = tempQuotientInv.number.rbegin();
			tempQuotient.number.at(0) = *it;
			it++;
			while (it != tempQuotientInv.number.rend())
			{
				tempQuotient.number.push_back(*it);
				it++;
			}
			tempQuotient.positive = tempRemainder.positive;

			quotient = quotient + tempQuotient;
			tempRemainder = absDividend - quotient * absDivisor;
		}
		if (tempRemainder < 0)
		{
			--quotient;
			remainder = tempRemainder + divisor;

		}
		else
		{
			remainder = tempRemainder;
		}
		return quotient;

	}
	else if (absDivisor == absDividend)
	{
		if (quotient.positive)
		{
			++quotient;
		}
		else 
		{
			--quotient; //it only performs one more intermediate step (the sign inversion) which is reverted
		}
		return quotient;
	}
	else
	{
		remainder.number = absDividend.number;
		return quotient;
	}

}


std::ostream& operator<<(std::ostream &s, const BigInt& bi) {
	if (!bi.positive) {
		s << '-';
	}
	bool first = true;
	for (size_t i = bi.number.size(); i > 0; --i) {
		if (first) {
			s << bi.number[i-1];
			first = false;
		}
		else {
			s << std::setfill('0') << std::setw(BigInt::DIGIT_COUNT) << bi.number[i-1];
		}
	}
	return s;
}

//NON FA NULLA
BigInt pow(const BigInt& base, const BigInt& exp) {
	if (exp.positive)
	{
		BigInt result(1);
		BigInt expCursor(0);
		while (expCursor != exp) {

			result = result * base;
			++expCursor;
		}


		return result;
	}
	else {
		//impossible: undefined in integers set
		BigInt result(0);
		return result;
	}

}