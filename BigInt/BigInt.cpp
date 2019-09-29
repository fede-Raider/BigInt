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

const BigInt& BigInt::operator--() {
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
					*it = BASE - 1;
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

div_ct BigInt::DivideNumberToBase(PRODUCT_TYPE n) const {
	return div_ct::Divide(n, BASE);
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
		div_ct dt = DivideNumberToBase(i);
		number.push_back(dt.rem);
		i = dt.quot;
	} while (i != 0);
}

BigInt::BigInt(long i) : positive(i >= 0) {
	if (!positive) {
		i = -i;
	}
	do {
		div_ct dt = DivideNumberToBase(i);
		number.push_back(dt.rem);
		i = dt.quot;
	} while (i != 0);
}

BigInt::BigInt(long long i) : positive(i >= 0) {
	if (!positive) {
		i = -i;
	}
	do {
		div_ct dt = DivideNumberToBase(i);
		number.push_back(dt.rem);
		i = dt.quot;
	} while (i != 0);
}

BigInt::BigInt(unsigned int i) : positive(true) {
	do {
		div_ct dt = DivideNumberToBase(i);
		number.push_back(dt.rem);
		i = dt.quot;
	} while (i != 0);
}

BigInt::BigInt(unsigned long i) : positive(true) {
	do {
		div_ct dt = DivideNumberToBase(i);
		number.push_back(dt.rem);
		i = dt.quot;
	} while (i != 0);
}

BigInt::BigInt(unsigned long long i) : positive(true) {
	do {
		div_ct dt = DivideNumberToBase(i);
		number.push_back(dt.rem);
		i = dt.quot;
	} while (i != 0);
}

BigInt::BigInt(const std::string& s) {
	if (!s.size()) {
		number.push_back(0);
		return;
	}
	positive = s[0] != '-' ? true : false;

	if (!positive && s.size() < 2) {
		positive = true;
		number.push_back(0);
		return;
	}

	size_t slot = s.size() / DIGIT_COUNT + 1;
	number.reserve(slot);
	for (size_t i = 1; i < slot; ++i) {
		number.push_back(atoi(s.substr(s.size() - i * DIGIT_COUNT, DIGIT_COUNT).c_str()));
	}

	if (positive) {
		if (s.size() % DIGIT_COUNT != 0) {
			number.push_back(atoi(s.substr(0, s.size() % DIGIT_COUNT).c_str()));
		}
	} else {
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
			dt = DivideNumberToBase(dt.quot + (i < number.size() ? number[i] : 0) + (i < rhs.number.size() ? rhs.number[i] : 0));
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
			BigInt result;
			result.positive = positive;
			result.number.pop_back();
			div_t dt;
			dt.quot = 0;
			//in questo blocco if sono già nella situazione in cui il primo numero è maggiore nel secondo: le due size saranno al più uguali
			//dt.quot || (i < std::max(number.size(), rhs.number.size()))
			for (size_t i = 0; dt.quot || (i < number.size()); ++i) {
				dt.rem = (i < number.size() ? number[i] : 0) - (i < rhs.number.size() ? rhs.number[i] : 0) - dt.quot;
				if (dt.rem >= 0) {
					result.number.push_back(dt.rem);
					dt.quot = 0;
				} else {
					result.number.push_back(BASE  + dt.rem); // quando dt.rem è minore di 0, il suo valore numerico è quello che devo sottrarre a 1 000 000 000
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

	PRODUCT_TYPE carry = 0;
	size_t digit = 0;
	for (;; ++digit){
		div_ct dt = div_ct::Divide(carry, BASE);
		carry = dt.quot;
		result.number[digit] = static_cast<ELEM_TYPE>(dt.rem);

		bool found = false;
		for (size_t i = digit < rhs.number.size() ? 0 : digit - rhs.number.size() + 1; i < number.size() && i <= digit; ++i) {
			PRODUCT_TYPE pval = result.number[digit] + number[i] * static_cast<PRODUCT_TYPE>(rhs.number[digit - i]);
			if (pval >= BASE || pval <= -(int_fast32_t)BASE) {
				div_ct dt = div_ct::Divide(pval, BASE);
				carry += dt.quot;
				pval = dt.rem;
			}
			result.number[digit] = static_cast<ELEM_TYPE>(pval);
			found = true;
		}
		if (!found) {
			break;
		}
	}
	for (; carry > 0; ++digit) {
		div_ct dt = div_ct::Divide(carry, BASE);
		result.number[digit] = static_cast<ELEM_TYPE>(dt.rem);
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
	BigInt Q, R, D = (divisor.positive ? divisor : -divisor), N = (positive ? *this : -*this);
	Q.number.resize(N.number.size(), 0);
	for (size_t i = N.number.size(); i > 0; --i) {
		R.number.insert(R.number.begin(), N.number[i - 1]);
		R.RemoveUselessZero();

		ELEM_TYPE min = 0, max = BASE - 1;
		while (max > min) {
			ELEM_TYPE avg = max + min;
			div_ct dt = div_ct::Divide(avg, 2);

			avg = dt.rem ? (dt.quot + 1) : dt.quot;
			BigInt prod = D * avg;
			if (R == prod) {
				min = avg;
				break;
			} else if (R > prod) {
				min = avg;
			} else {
				max = avg - 1;
			}
		}
		ELEM_TYPE cnt = min;

		R -= D * cnt;
		Q.number[i - 1] += cnt;
	}
	Q.RemoveUselessZero();
	Q.positive = (Q.number.size() == 1 && Q.number[0] == 0) ? true : (positive == divisor.positive);
	return Q;
}

const BigInt& BigInt::operator/=(const BigInt & rhs) {
	*this = *this / rhs;
	return *this;
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

std::istream & operator>>(std::istream& s, BigInt& n){
	std::string str;
	s >> str;
	n = str;
	return s;
}

BigInt pow(const BigInt& base, const BigInt& exp) {
	if (exp.positive) {
		BigInt result(1);
		BigInt expCursor(0);
		while (expCursor != exp) {

			result = result * base;
			++expCursor;
		}

		return result;
	} else {
		//impossible: undefined in integers set
		BigInt result(0);
		return result;
	}

}

BigInt BigInt::operator<<(const BigInt &rhs) const {
	BigInt result;
	//bool isShiftable=true;
	//if every number is less than 134217728 (2 ^ 27) the whole number is shiftable
	//if not, there's at least a number which exploits bits from the 28th to the 30th
	//then, after shifting we could find a bit set to 1 in a position lower than 28th
	//so we could obtain a not mapped number
	// only numbers with 9 digits groups less or equal than 134217727 can be shifted
	
	if (isShiftable)
	{
		if (rhs.positive)
		{
			if (rhs >= 27 * number.size())
			{
				return result;
			}
			else
			{
				//I divided shift in two parts: the first one involves shifts of a number of positions less than 27, which does not involve
				// creation of new vector elements
				//in the method 'shift numbers left' there is an offset mask which knows all the bits needed to store the last vector elemenent
				result = *this;
				BigInt shiftCount =rhs%27;
				unsigned short int shiftCountVal = shiftCount.number[0];
				result.ShiftNumbersLeft(shiftCountVal);

				shiftCount = rhs / 27;
				while (shiftCount > 0)
				{
					//we should shift 27 position each time, and also cancel from the left
					//again, we should cancel out 27 bits each time and we could need a mask if these bits are distributed over two numbers
					result.number.insert(result.number.begin(),0);
					--shiftCount;
				}
				return result;
				
			}
		}
		else
		{
			return *this >> (-rhs);
		}
	}
	else
	{
		return result= std::move(*this);
	}
}
BigInt BigInt::operator>>(const BigInt &rhs)const
{
	BigInt result;
	if (isShiftable)
	{
		if (rhs.positive)
		{
			if (rhs >= 27 * number.size())
			{
				return result;
			}
			else
			{
				result = *this;
				BigInt shiftCount = rhs / 27;
				while (shiftCount > 0)
				{
					//we should shift 27 position each time, and also cancel from the left
					//again, we should cancel out 27 bits each time and we could need a mask if these bits are distributed over two numbers
					result.number.erase(result.number.begin());
					--shiftCount;
				}
				shiftCount = rhs % 27;

				unsigned short int shiftCountVal = shiftCount.number[0];

				result.ShiftNumbersRight(shiftCountVal);
				return result;
			}
		}
		else
		{
			return *this << (-rhs);
		}
	}
	else
	{
	return result = std::move(*this);
	}

}

BigInt BigInt::operator%(const BigInt& rhs) const
{
	BigInt R, D = (rhs.positive ? rhs : -rhs), N = (positive ? *this : -*this);
	for (size_t i = N.number.size(); i > 0; --i) {
		R.number.insert(R.number.begin(), N.number[i - 1]);
		R.RemoveUselessZero();

		ELEM_TYPE min = 0, max = BASE - 1;
		while (max > min) {
			ELEM_TYPE avg = max + min;
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
		ELEM_TYPE cnt = min;

		R -= D * cnt;
	}
	R.positive= (positive == rhs.positive);
	return R;
}

void BigInt::ShiftNumbersLeft(unsigned short int shiftCount)
{
	ELEM_TYPE offsetMask=0;
	unsigned short int offsetIndex = 27;
	while(offsetIndex>0)
	{
		--offsetIndex;
		offsetMask += 1 << offsetIndex;
	}
	offsetMask = offsetMask & (*(number.end()-1));
	offsetIndex = 27;
	bool found =false;
	while (offsetIndex > 0)
	{
		--offsetIndex;
		if (!found && (offsetMask & (1 << offsetIndex)) == true)
		{
			found = true;
		}
		if (found && (offsetMask & (1 << offsetIndex)) == false)
		{
			offsetMask += (1 << offsetIndex);
		}
	}

	ELEM_TYPE shiftMask = 0;
	unsigned short int shiftCountCopy = shiftCount;
	while (shiftCountCopy != 0)
	{
		shiftMask += 1 << (27 - shiftCountCopy);
		--shiftCount;
	}
	ELEM_TYPE toNextOrder=0;
	ELEM_TYPE fromLowerOrder=0;
	for (std::vector<ELEM_TYPE>::iterator it = number.begin(); it != number.end(); it++)
	{
		fromLowerOrder = toNextOrder>>(27-shiftCount);
		toNextOrder = shiftMask & (*it);
		(*it) = (*it) << shiftCount;

		(*it) = (*it) | fromLowerOrder;
	}
	(*(number.end() - 1)) &= offsetMask;
}



void BigInt::ShiftNumbersRight(unsigned short int shiftCount)
{
	
	ELEM_TYPE shiftMask = 0;
	unsigned short int shiftCountIncr = 0;
	while (shiftCountIncr != shiftCount)
	{
		shiftMask += 1 << shiftCountIncr;
		++shiftCount;
	}
	ELEM_TYPE toNextOrder = 0;
	ELEM_TYPE fromUpperOrder = 0;
	for (std::vector<ELEM_TYPE>::reverse_iterator it = number.rbegin(); it != number.rend(); it++)
	{
		fromUpperOrder = toNextOrder << (27 - shiftCount);
		toNextOrder = shiftMask & (*it);
		(*it) = (*it) >> shiftCount;

		(*it) = (*it) | fromUpperOrder;
	}
}

void BigInt::IntToBin()
{
	size_t i = number.size();
	while (i > 0)
	{
		--i;
		if (number[i] > 134217727)
		{
			isShiftable = false;
		}
	}
	if (isShiftable)
	{
		for (std::vector<ELEM_TYPE>::reverse_iterator rit = number.rbegin(); rit != number.rend(); rit++)
		{
			//size_t pos = 26;
			uint_fast32_t i = 1 << 26;
			while ( i > 0)
			{
				(*rit) & i ? binaryRepresentation.push_back(true) : binaryRepresentation.push_back(false);
				i /= 2;
				//--pos;
			}
		}
		size_t i = binaryRepresentation.size();
		while (!binaryRepresentation[i])
		{
			binaryRepresentation.pop_back();
			i = binaryRepresentation.size();
		}
	}
	
}