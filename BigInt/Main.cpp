#include <iostream>
#include "BigInt.h"
#include <assert.h> 

void TestConstruction();
void TestComparisonOperators();
void TestIncrementOperators();
void TestMoveCopyOperators();
void TestMathsOperators();
void TestMultiplication();
void TestDivision();
void TestModule();
void TestExample();

int main() {
	assert((BigInt(4) >> 1) == 2);
	assert((BigInt(4) << 1) == 8);
	assert((BigInt(1) << 100) == "1267650600228229401496703205376");
	assert((BigInt("1267650600228229401496703205376") >> 100) == 1);

	TestConstruction();
	std::cout << "Test 0 - Construction : succeeded\n";

	TestComparisonOperators();
	std::cout << "Test 1 - Comparison operators : succeeded\n";

	TestIncrementOperators();
	std::cout << "Test 2 - Increment operators : succeeded\n";

	TestMoveCopyOperators();
	std::cout << "Test 3 - Move Copy operators : succeeded\n";

	TestMathsOperators();
	std::cout << "Test 4 - Maths operators : succeeded\n";

	TestMultiplication();
	std::cout << "Test 5 - Multiplication : succeeded\n";

	TestDivision();
	std::cout << "Test 6 - Division : succeeded\n";

	TestModule();
	std::cout << "Test 7 - Module : succeeded\n";

	TestExample();
	std::cout << "Test Example : succeeded\n";
	std::cout << "Execution ended\n";

	int k = 0;
	std::cin >> k;
}

void TestConstruction() {
	BigInt x = "0";
	assert(x == 0);

	x = "";
	assert(x == 0);

	x = "-0";
	assert(x == 0);

	x = "-";
	assert(x == 0);
}

void TestComparisonOperators() {
	BigInt x = "-74823645945764595679202347874897";
	BigInt y;

	// ==
	assert(!(x == y));
	assert((x == x));

	BigInt zero = "0";
	BigInt zero2 = "-0";
	BigInt zero3 = "00000000000000000";
	BigInt zero4 = 0;
	BigInt zero5 = -0;
	assert(zero == zero2);
	assert(zero == zero3);
	assert(zero == zero4);
	assert(zero == zero5);

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

void TestIncrementOperators() {
	// ++int
	{
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


	// int++
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

	//int--
	x1 = "1000000000";
	x1--;
	assert(x1 == "999999999");

	x1 = "0";
	assert(x1-- == "0");
	assert(x1 == "-1");

	//--int
	--x1;
	assert(x1 == "-2");

	x1 = 0;
	assert(--x1 == "-1");
}

void TestMathsOperators() {
	BigInt x = 999999999;
	BigInt y = 1;
	assert(x + y == "1000000000");
	assert(y + x == "1000000000");
	assert(x - y == "999999998");
	assert(y - x == "-999999998");

	BigInt x1 = 999999999;
	BigInt y1 = 999999999;
	assert(x1 + y1 == "1999999998");
	assert(x1 - y1 == 0);
	assert(y1 - x1 == 0);
	
	x = -999999999;
	y = -1;
	assert(x + y == "-1000000000");
	assert(y + x == "-1000000000");
	assert(x - y == "-999999998");
	assert(y - x == "999999998");

	x1 = -999999999;
	y1 = -999999999;
	assert(x1 + y1 == "-1999999998");
	assert(y1 + x1 == "-1999999998");
	assert(x1 - y1 == "0");
	assert(y1 - x1 == "0");

	x1 = 999999999;
	y1 = -999999999;
	assert(x1 + y1 == "0");
	assert(y1 + x1 == "0");
	assert(x1 - y1 == "1999999998");
	assert(y1 - x1 == "-1999999998");

	x1 = -999999999;
	y1 = 1;
	assert(x1 - y1 == "-1000000000");
	assert(x1 + y1 == "-999999998");
	assert(y1 + x1 == "-999999998");
	assert(y1 - x1 == "1000000000");

	x = 999999999;
	y = -1;
	assert(x + y == 999999998);
	assert(y + x == 999999998);
	assert(x - y == "1000000000");
	assert(y - x == "-1000000000");

	x = 0;
	y = 0;
	assert(x + y == 0);
	assert(x - y == 0);
	assert(y + x == 0);
	assert(y - x == 0);

	x = 5;
	assert(x + y == 5);
	assert(x - y == 5);
	assert(y + x == 5);
	assert(y - x == -5);

	x = "123000000345";
	y = -34000;
	assert(x + y == "122999966345");

	x = "-123000000000000000345";
	y = "123000000000000000001";
	assert(x + y == "-344");

	x = "123000000000000000345";
	y = "115085000000000000001";
	assert(x - y == "7915000000000000344");

	x = "123000000000000000345";
	y = "123000000000000000345";
	assert(x - y == 0);

	x = "-123000000000000000345";
	y = "-123000000000000000345";
	assert(x - y == 0);

	x = "-123000000000000000345";
	y = "123000000000000000345";
	assert(x + y == 0);
	assert(y + x == 0);

	x = "-1000000000";
	y = 1;
	assert(x + y == "-999999999");

	x = "-1000000000";
	y = 1;
	x += y;
	assert(x == "-999999999");

	x = 999999999;
	y = 1;
	x -= y;
	assert(x == "999999998");
}

void TestMultiplication() {
	BigInt x1;
	BigInt x2;
	BigInt xres;
	x1 = "123000000000000000345";
	x2 = "115085000000000000001";
	xres = x1 * x2;
	std::cout << xres;
	assert(xres == "14155455000000000039827325000000000000345");

	x1 = "123008123000000545345";
	x2 = "115085040320000432333";
	xres = x1 * x2;
	assert(xres == "14156394795142635301522154269635770639885");

	x1 = "123008123000000545345";
	x2 = "85040320000432333";
	xres = x1 * x2;
	assert(xres == "10460650142572586847154269635770639885");

	x1 = "123008123000000545345";
	x2 = "40320000432333";
	xres = x1 * x2;
	assert(xres == "4959687572540492829269635770639885");

	x1 = "5000000005000000";
	x2 = "5000000005000000";
	xres = x1 * x2;
	assert(xres == "25000000050000000025000000000000");

	x1 = "5000019995001999";
	x2 = "5000019995001999";
	xres = x1 * x2;
	assert(xres == "25000199950419790104940013996001");

	x1 = "-5000019995001999";
	x2 = 0;
	xres = x1 * x2;
	assert(xres == "0");

	x1 = "-5000019995001999";
	x2 = 1;
	xres = x1 * x2;
	assert(xres == "-5000019995001999");

	x1 = "-5000019995001999";
	x2 = -1;
	xres = x1 * x2;
	assert(xres == "5000019995001999");

	x1 = "-5000019995001999";
	x2 = 1;
	xres = x1 * x2;
	assert(xres == "-5000019995001999");

	x1 = "5000019995001999";
	x2 = 1;
	xres = x1 * x2;
	assert(xres == "5000019995001999");

	x1 = "5000019995001999";
	x2 = 1;
	x1 *= x2;
	assert(x1 == "5000019995001999");
}

void TestMoveCopyOperators() {
	BigInt x = "-2";
	BigInt y = x;
	assert(x == y);

	BigInt k = 0;
	k = x;
	assert(y == k);

	x++;
	assert(y == k);
	assert(x != k);

	x = 1;
	y = -x;
	assert(y == -1);
	assert(y == -x);

	unsigned long long int n = 999999999999909999;
	BigInt w = n;
	BigInt w2 = std::move(w);
	assert(w2 == 999999999999909999);
}

void TestDivision() {
	BigInt x1;
	BigInt x2;

	x1 = "978141554550000000000398273250000000000003455671234";
	x2 = "657293042012542045321782";
	BigInt res = x1 /= x2;
	std::cout << res;
	assert(x1 == "1488136176757726470237790039");

	x1 = "5";
	x2 = "1";
	assert(x1 / x2 == 5);
	assert(x2 / x1 == 0);

	x2 = "5";
	assert(x1 / x2 == 1);
	assert(x2 / x1 == 1);

	x1 = "-5";
	x2 = "1";
	res = x1 / x2;
	assert(x1 / x2 == -5);   
	assert(x2 / x1 == 0);

	x1 = "-5";
	x2 = "-1";
	assert(x1 / x2 == 5);
	assert(x2 / x1 == 0);

	x1 = "5";
	x2 = "-1";
	//res=x1 / x2;
	assert(x1 / x2 == -5);
	assert(x2 / x1 == 0);

	x1 = "14155455000000000039827325000000000000345";
	x2 = "5";
	assert(x1 / x2 == "2831091000000000007965465000000000000069");

	x1 = "1000000000";
	x2 = "5";
	assert(x1 / x2 == "200000000");

	x1 = "1000000000";
	x2 = "1000000000";
	assert(x1 / x2 == 1);

	x1 = "14155455000000000039827325000000000000345";
	x2 = "1000000000";
	assert(x1 / x2 == "14155455000000000039827325000000");

	x1 = "14155455000000000039827325000000000000345";
	x2 = "1000000000";
	x1 /= x2;
	assert(x1 == "14155455000000000039827325000000");
}

void TestModule() {
	BigInt x = 15;

	assert(x % 1 == 0);
	assert(x % 2 == 1);
	assert(x % 3 == 0);
	assert(x % 5 == 0);
	assert(x % 6 == 3);
	assert(x % 7 == 1);
	assert(x % 8 == 7);
}

void TestExample() {
	BigInt x = 569;
	BigInt y;
	y = pow(x, 10);
	BigInt z = x;
	z += y;
	z %= y;
	z %= 5;

	BigInt w = ("348734834853836786386736");
	std::cout << w;
	w++;
	if (w <= y) {

	}
	z %= x;
	//std::cout << y;
	x = -y;
	//x <<= 5;
	//w = pow(w, y);

	BigInt testcin;
	std::cin >> testcin;
	std::cout << testcin;
}