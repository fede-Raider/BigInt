#include <iostream>
#include "BigInt.h"
#include <assert.h> 

void TestOperators() {
	BigInt x = "-74823645945764595679202347874897";
	BigInt y;

	// ==
	assert(!(x == y));
	assert((x == x));

	BigInt zero = "0";
	BigInt zero2 = "-0";
	BigInt zero3 = "00000000000000000";
	assert(zero == zero2);
	assert(zero == zero3);

	BigInt one = "01";
	BigInt one2 = "00000000000000000001";
	BigInt one3 = "-00000000000000000001";
	assert(one == one2);
	assert(one != one3);

	// !=
	assert(x != y);
	assert(!(x != x));

	// <
	assert(x < y);
	assert(!(x < x));
	assert(!(y < x));

	// <=
	assert(x <= y);
	assert(x <= x);
	assert(!(y <= x));

	// >
	assert(!(x > y));
	assert(!(x > x));
	assert(y > x);

	// >=
	assert(!(x >= y));
	assert(x >= x);
	assert(y >= x);
}

void TestOperators2() {
	BigInt x = "123456789";
	BigInt y = "123456789";

}

void TestOperators3() {
	BigInt x1 = 1;
	assert(++x1 == 2);
	BigInt x2 = 0;
	assert(++x2 == 1);
	BigInt x3 = "999999999";
	assert(++x3 == "1000000000");
	BigInt x4 = "-999999999";
	assert(++x4 == "-999999998");
	BigInt x5 = "-1";
	assert(++x5 == "0");
	BigInt x6 = "-2";
	assert(++x6 == "-1");
	BigInt x7 = "-0";
	assert(++x7 == "1");
}

void TestOperators4() {
	BigInt x1 = 1;
	assert(x1++ == 1);
	assert(x1 == 2);
	BigInt x2 = 0;
	assert(x2++ == 0);
	assert(x2 == 1);
	BigInt x3 = "999999999";
	assert(x3++ == "999999999");
	assert(x3++ == "1000000000");
	BigInt x4 = "-999999999";
	assert(x4++ == "-999999999");
	assert(x4 == "-999999998");
	BigInt x5 = "-1";
	assert(x5++ == "-1");
	assert(x5 == "0");
	BigInt x6 = "-2";
	assert(x6++ == "-2");
	assert(x6 == "-1");
	BigInt x7 = "-0";
	assert(x7++ == "0");
	assert(x7 == "1");

	x1 = "-1000000000";
	x1++;
	assert(x1 == "-999999999");

	x1 = "1000000000";
	x1--;
	assert(x1 == "999999999");
}

void TestCopy() {
	BigInt x = "-2";
	BigInt y = x;
	assert(x == y);

	BigInt k = 0;
	k = x;
	assert(y == k);

	x++;
	assert(y == k);
	assert(x != k);
}

void TestOperators5() {
	BigInt x = 1;
	BigInt y = -x;
	assert(y == -1);
	assert(y == -x);
}
int main() {

	TestOperators();
	TestOperators2();
	TestOperators3();
	TestOperators4();
	TestCopy();
	{
		unsigned long long int k = 999999999999909999;
		BigInt x = k;
		BigInt k2 = std::move(x);
	}


	
	BigInt x = 999999999;
	BigInt y = 1;
	assert(x + y == "1000000000");

	BigInt x1 = 999999999;
	BigInt y1 = 999999999;
	assert(x1 + y1 == "1999999998");


	x = -999999999;
	y = -1;
	assert(x + y == "-1000000000");

	x1 = -999999999;
	y1 = -999999999;
	assert(x1 + y1 == "-1999999998");


	x1 = -999999999;
	y1 = 1;
	assert(x1 - y1 == "-1000000000");
	
	x = 999999999;
	y = -1;
	assert(x + y == 999999998);

	x = -999999999;
	y = 1;
	assert(x + y == -999999998);

	x = "-1000000002";
	y = 1;
	assert(x + y == "-1000000001");


	x = "-1000000000";
	y = 1;
	assert(x + y == "-999999999");
	
	//BigInt y = pow(x, 10);

	BigInt w = "-999999999";
	++w;
	system("PAUSE");

}