#include <iostream>
#include <string>
#include "bigInt.h"
#include "time.h"
#include <windows.h>

using namespace std;

//using namespace BigInteger;

int main()
{
	G_CreatePrimeList();

	//BigInteger
	//	A_00_1("100"), B_00_1("100"),
	//	A_00_2("-100"), B_00_2("-100"),
	//	A_10("100"), B_10("-100"),
	//	A_20("-100"), B_20("100"),
	//	A_11_1("100"), B_11_1("-91"),
	//	A_11_2("100"), B_11_2("91"),
	//	A_12_1("-91"), B_12_1("-100"),
	//	A_12_2("91"), B_12_2("-100"),
	//	A_21_1("-100"), B_21_1("-91"),
	//	A_21_2("-100"), B_21_2("91"),
	//	A_22_1("91"), B_22_1("100"),
	//	A_22_2("-91"), B_22_2("100");//测试数据

	//cout << "加法测试:" << endl;
	//cout 
	//	<< A_00_1 + B_00_1 << endl
	//	<< A_00_2 + B_00_2 << endl
	//	<< A_10 + B_10 << endl
	//	<< A_20 + B_20 << endl
	//	<< A_11_1 + B_11_1 << endl
	//	<< A_11_2 + B_11_2 << endl
	//	<< A_12_1 + B_12_1 << endl
	//	<< A_12_2 + B_12_2 << endl
	//	<< A_21_1 + B_21_1 << endl
	//	<< A_21_2 + B_21_2 << endl
	//	<< A_22_1 + B_22_1 << endl
	//	<< A_22_2 + B_22_2 << endl;

	//cout << "减法测试:" << endl;
	//cout
	//	<< A_00_1 - B_00_1 << endl
	//	<< A_00_2 - B_00_2 << endl
	//	<< A_10 - B_10 << endl
	//	<< A_20 - B_20 << endl
	//	<< A_11_1 - B_11_1 << endl
	//	<< A_11_2 - B_11_2 << endl
	//	<< A_12_1 - B_12_1 << endl
	//	<< A_12_2 - B_12_2 << endl
	//	<< A_21_1 - B_21_1 << endl
	//	<< A_21_2 - B_21_2 << endl
	//	<< A_22_1 - B_22_1 << endl
	//	<< A_22_2 - B_22_2 << endl;

	//cout << "乘法测试:" << endl;
	//cout
	//	<< A_00_1 * B_00_1 << endl
	//	<< A_00_2 * B_00_2 << endl
	//	<< A_10 * B_10 << endl
	//	<< A_20 * B_20 << endl
	//	<< A_11_1 * B_11_1 << endl
	//	<< A_11_2 * B_11_2 << endl
	//	<< A_12_1 * B_12_1 << endl
	//	<< A_12_2 * B_12_2 << endl
	//	<< A_21_1 * B_21_1 << endl
	//	<< A_21_2 * B_21_2 << endl
	//	<< A_22_1 * B_22_1 << endl
	//	<< A_22_2 * B_22_2 << endl;

	//cout << "除法测试:" << endl;
	//cout
	//	<< A_00_1 / B_00_1 << endl
	//	<< A_00_2 / B_00_2 << endl
	//	<< A_10 / B_10 << endl
	//	<< A_20 / B_20 << endl
	//	<< A_11_1 / B_11_1 << endl
	//	<< A_11_2 / B_11_2 << endl
	//	<< A_12_1 / B_12_1 << endl
	//	<< A_12_2 / B_12_2 << endl
	//	<< A_21_1 / B_21_1 << endl
	//	<< A_21_2 / B_21_2 << endl
	//	<< A_22_1 / B_22_1 << endl
	//	<< A_22_2 / B_22_2 << endl;

	//cout << endl << endl;

	//BigInteger A(123), B(456), n(533), v;
	/*BigInteger A(-153), B(25);
	cout << A / B;*/
	//for (int i = 0; i < 100; i++)
	//{
	//	BigInteger A(string("7355608999911110111358351"));
	//	auto start = clock();
	//	cout << BigInteger::IsPrime(A) << "  ";
	//	auto end = clock();
	//	cout << end - start << endl;
	//}
	//2152302898747

	cout << BigInteger::Power(BIG_TWO, 64) << endl;
	auto start = clock();
	cout << BigInteger::IsPrime(BigInteger::Power(2, 64) - BigInteger(5)) << endl;
	auto end = clock();
	cout << end - start << endl;
	//cout << BigInteger::MontgomeryX(BigInteger(9), BigInteger(13), BigInteger(15));
	//cout << BigInteger::Inverse(BigInteger(491), BigInteger(1024), &A) << " " << A;
	//cout << BigInteger::MontgomerySimple(A, n, BigInteger(), BigInteger()) << endl;;
	//for (int i = 129; i < 255; i += 2)
	{
		//cout << BigInteger::NegativeInv(16, 18577) << endl;
	}
	/*for (int i = 33; i < 200; i++) {
		cout << i << " mod 32 = ";
		cout << BigInteger::Mod_Bin(BigInteger(i), 5) << endl;;
	}*/

	/*auto start = clock();
	cout << BigInteger::MontgomeryX(BigInteger("123456789"), BigInteger("987654321"), BigInteger("185777777777777777777"));
	auto nd = clock();
	cout << endl << nd - start << endl;
	start = clock();
	cout << BigInteger("123456789") * BigInteger("987654321") % BigInteger("185777777777777777777") << endl;
	nd = clock();
	cout << nd - start;*/

	//cout << BigInteger::IsPrime(73556089);
	/*BigInteger A(98);
	cout << (A & BIG_ONE);*/
	//cout << BigInteger::Inverse(533, 1000, &A) << endl << A << endl;

	/*BigInteger A(56);
	A.DecToBin();
	cout << A.Bin;
*/
	/*BigInteger A(533), B(1000);
	BigInteger::XGcd(1000-533, 1024, &A, &B);
	cout << A << " " << B;*/
	
	//string A("1001001");
	//cout << BigInteger::BinSubOne(A) << endl;

	//cout << BigInteger::MontgomeryX(386, 257, 533);

	//cout << BigInteger::MontgomeryX(1234, 1, 18577);

	//cout << BigInteger::Power(BigInteger(123), BigInteger(4));

	//cout << BigInteger::Sqr(20);

	//cout << (BigInteger(1) != BIG_ONE);

 	system("pause");
	return 0;
}
////////////////////////////
//TODO:
// Montgomery 乘积
// Montgomery 约简
// 改进模幂运算
// 素性测试
// 素数生成