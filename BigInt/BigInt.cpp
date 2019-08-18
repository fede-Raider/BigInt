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
					//penso che il programma qui sia sbagliato: se dopo aver diminuito ogni numero
					//trovo che questo è più grande della base, allora vuol dire che ogni numero inizialmente era zero
					//pertanto il numero finale deve diventare -1 e quindi va impostato come numero negativo (ok)
					// e tutti gli altri numeri vanno riportati a 0 tranne il primo ( quello con iteratore number.begin() )
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
	// TODO: insert return statement here
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
	for (int i = number.size() - 1; i >= 0; --i) {
		if (number[i] != rhs.number[i]) {
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
		return positive ? false : true;
	}

	if (number.size() < rhs.number.size()) {
		return positive ? true : false;
	}

	for (int i = number.size() - 1; i >= 0; --i) {
		if (number[i] < rhs.number[i]) {
			return positive ? true : false;
		}
		if (number[i] > rhs.number[i]) {
			return positive ? false : true;
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
	for (int i = 1; i < slot; ++i) {
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

	while (number.size() > 1) {

		if (*(number.end() - 1) == 0)
		{
			number.pop_back();
		}
		else
		{
			break;
		}
	}
	//il ciclo for successivo non serve a niente, temo
	/*
	for (int i = number.size() - 1; i > 0; --i) {
		if (number[i] == 0) {
			number.pop_back();
		}
	}
	*/
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
		for (int i = 0; dt.quot || (i < std::max(number.size(), rhs.number.size())); ++i) {
			dt = DivideNumberToBase(dt.quot + (i < number.size() ? number[i] : 0) + (i < rhs.number.size() ? rhs.number[i] : 0));
			result.number.push_back(dt.rem);
		}
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
			for (int i = 0; dt.quot || (i < number.size()); ++i) {
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
			// con questo ciclo while con if interno tolgo tutti gli 0 finali - potrebbe esserci più di un numero uguale a 0.
			while (result.number.size() > 1) {

				if (*(result.number.end() - 1) == 0)
				{
					result.number.pop_back();
				}
				else
				{
					break;
				}
			}
			/*  -------- con questo ciclo if interno tolgo lo 0 finale, ma ne tolgo solo uno, l'ultimo
			if (result.number.size() > 1 && *(result.number.end()-1) == 0 ) {
				result.number.pop_back();
			}
			*/
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
	return result;
}


std::ostream& operator<<(std::ostream &s, const BigInt& bi) {
	if (!bi.positive) {
		s << '-';
	}
	bool first = true;
	for (int i = bi.number.size() - 1; i >= 0; --i) {
		if (first) {
			s << bi.number[i];
			first = false;
		}
		else {
			s << std::setfill('0') << std::setw(BigInt::DIGIT_COUNT) << bi.number[i];
		}
	}
	return s;
}

//NON FA NULLA
BigInt pow(const BigInt& base, const BigInt& exp) {
	return BigInt();
}