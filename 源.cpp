#include <iostream>
#include <string>
#include "bigInt.h"
#include "time.h"
#include <windows.h>

using namespace std;

//using namespace BigInteger;

int main()
{
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
	//	A_22_2("-91"), B_22_2("100");//≤‚ ‘ ˝æ›

	//cout << "º”∑®≤‚ ‘:" << endl;
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

	//cout << "ºı∑®≤‚ ‘:" << endl;
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

	//cout << "≥À∑®≤‚ ‘:" << endl;
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

	//cout << "≥˝∑®≤‚ ‘:" << endl;
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

	BigInteger A(2), B(5), C;

	for (int i = 0; i < 100; i++)
	{
		cin >> A;
		auto start = clock();
		cout << BigInteger::IsPrime(A) << "  ";
		auto end = clock();
		cout << end - start << endl;
	}
	//2152302898747
 	system("pause");
	return 0;
}