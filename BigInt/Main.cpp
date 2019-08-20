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

	x1 = "0";
	std::cout << x1 << "\n";
	assert(x1-- == "0");
	assert(x1 == "-1");
	std::cout << x1 << "\n";
	--x1;
	assert(x1 == "-2");
	std::cout << x1 <<"\n";

}
void TestMultiplication() {
	std::cout << "Test signed 64 bit integer fast  max value" << "\n";
	std::cout << INT_FAST64_MAX << "   " << INT_FAST64_MIN << "\n\n";

	BigInt x1;
	BigInt x2;
	BigInt xres;
	x1 = "123000000000000000345";
	x2 = "115085000000000000001";
	xres = x1 * x2;
	assert(xres == "14155455000000000039827325000000000000345");
	x1 = "123008123000000545345";  //"123 008 123 000 000 545 345"
	x2 = "115085040320000432333";  //"115 085 040 320 000 432 333" 
	xres = x1 * x2;
	assert(xres == "14156394795142635301522154269635770639885");
	x1 = "123008123000000545345";  //"123 008 123 000 000 545 345"
	x2 = "85040320000432333";      //"     85 040 320 000 432 333" 
	xres = x1 * x2;
	assert(xres == "10460650142572586847154269635770639885");
	x1 = "123008123000000545345";  //"123 008 123 000 000 545 345"
	x2 = "40320000432333";         //"         40 320 000 432 333" 
	xres = x1 * x2;
	assert(xres == "4959687572540492829269635770639885");
	x1 = "5000000005000000";  //"123 008 123 000 000 545 345"
	x2 = "5000000005000000";  //"115 085 040 320 000 432 333" 
	xres = x1 * x2;
	assert(xres == "25000000050000000025000000000000");
	x1 = "5000019995001999";
	x2 = "5000019995001999";
	xres = x1 * x2;
	assert(xres == "25000199950419790104940013996001");
}
void TestSumAndDifference() {
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

	x = "-1000000000";
	y = 4;
	assert(x + y == "-999999996");

	x = "123000000345";
	y = -34000;
	assert(x + y == "122999966345");



	x = "-123000000000000000345";  //"123 000 000 000 000 000 345"
	y = "123000000000000000001";  //"123 000 000 000 000 000 001"
	assert(x + y == "-344");



	x = "123000000000000000345";  //"123 000 000 000 000 000 345"
	y = "115085000000000000001";  //"115 085 000 000 000 000 001"  
	assert(x - y == "7915000000000000344");

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
	std::cout << "test 1 - operators : succeeded\n";

	TestOperators2();
	std::cout << "test 2 - operators : succeeded\n";

	TestOperators3();
	std::cout << "test 3 - operators : succeeded\n";

	TestOperators4();
	std::cout << "test 4 - operators : succeeded\n";

	TestCopy();
	{
		unsigned long long int k = 999999999999909999;
		BigInt x = k;
		BigInt k2 = std::move(x);
	}
	std::cout << "test 5 - copy and move : succeeded\n";
	TestSumAndDifference();
	std::cout << "test 6 - sum and difference : succeeded\n";

	BigInt w = "-999999999";
	++w;
	std::cout << "test 7 - increment decrement operators : succeeded\n";

	TestMultiplication();
	std::cout << "test 8 - multiplication : succeeded\n";
	//system("PAUSE");
	std::cout << "execution ended";
}