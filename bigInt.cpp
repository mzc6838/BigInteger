#include "bigInt.h"
#include <string>
#include <Windows.h>
#include <math.h>
using namespace std;

#define BIG_ZERO BigInteger(0)
#define BIG_ONE BigInteger(1)
#define BIG_TWO BigInteger(2)

//构造函数
BigInteger::BigInteger(string num)
{
	this->isNegative = false;
	if (num[0] == '0' && (num[1] == 'x' || num[1] == 'X'))
	{
		this->conversion = BIGINT_HEX;
		num.erase(0, 2);
		this->num = num;
	}
	else if (num[0] == '0' && num[1] == 'B')
	{
		this->conversion = BIGINT_BIN;
		num.erase(0, 2);
		this->num = num;
	}
	else
	{
		this->conversion = BIGINT_DEC;
		if (num[0] == '-')
		{
			this->isNegative = true;
			num.erase(0, 1);
		}
		this->num = num;
	}
	this->num = BigInteger::SubZero(num);
	this->numLength = this->num.length();
}

BigInteger::BigInteger(int num)
{
	if (num < 0)
	{
		this->isNegative = true;
		num = 0 - num;
	}
	this->setEmpty();
	char temporary;
	while (num != 0)
	{
		temporary = '0' + (num % 10);
		this->num = temporary + this->num;
		num = num / 10;
	}
	this->num = SubZero(this->num);
	this->numLength = this->num.length();
}

//复制
void BigInteger::setData(BigInteger input)
{
	this->num = input.num;
	this->isNegative = input.isNegative;
	this->isError = input.isError;
	this->numLength = input.numLength;
	this->conversion = input.conversion;
}

//置空
void BigInteger::setEmpty()
{
	this->num = "";
	this->Bin = "";
	this->numLength = 0;
}

//转二进制
void BigInteger::DecToBin()
{
	BigInteger NUM(this->num);
	BigInteger reminder;
	while (NUM != BIG_ZERO)
	{
		this->Bin = (NUM % BIG_TWO).num + this->Bin;
		NUM = NUM / BIG_TWO;
	}
}
//转十进制
void BigInteger::BinToDec()
{
	BigInteger temporary;
	for (int i = this->Bin.length() - 1, j = 0; i >= 0; i--, j++)
	{
		if (this->Bin[i] == '1') 
		{
			temporary = temporary + BigInteger::Power(BIG_TWO, j);
		}
	}
	this->num = temporary.num;
}

/*
最基本加法 两个正数相加
输入： 两个正数A， B
return： 运算结果
*/
BigInteger BigInteger::_BaseAddition(BigInteger numA, BigInteger numB)
{
	string A = numA.num;
	string B = numB.num;
	BigInteger result;
	result.setEmpty();

	if (numA.numLength > numB.numLength)
	{
		A = numA.AddZeroFront(1);
		B = numB.AddZeroFront(numA.numLength - numB.numLength + 1);
	}
	else if (numA.numLength < numB.numLength)
	{
		B = numB.AddZeroFront(1);
		A = numA.AddZeroFront(numB.numLength - numA.numLength + 1);
	}
	else {
		A = numA.AddZeroFront(1);
		B = numB.AddZeroFront(1);
	}

	for (int i = A.length() - 1; i >= 0; i--)
	{
		if (A[i] - '0' + B[i] - '0' > 9)
		{
			char sum = A[i] - '0' + B[i] - '0' - 10 + '0';
			result.num = sum + result.num;
			A[i - 1]++;
		}
		else
		{
			result.num = (char)(A[i] + B[i] - '0') + result.num;
		}
	}
	result.num = BigInteger::SubZero(result.num);
	result.numLength = result.num.length();
	return result;
}

/*
最基本减法 真值大数减小数 均为正数
输入： 被减数， 减数
return： 运算结果

可用负号变换减法次序
*/
BigInteger BigInteger::_BaseSubtraction(BigInteger minuend, BigInteger meiosis)
{
	//minuend > meiosis
	string A = minuend.num;
	string B = meiosis.AddZeroFront(minuend.numLength - meiosis.numLength);
	BigInteger result;
	result.setEmpty();

	for (int i = A.length() - 1; i >= 0; i--)
	{
		if (A[i] < B[i])
		{
			A[i - 1]--;
			char temporary = '0' + (A[i] + 10 - B[i]);
			result.num = temporary + result.num;
		}
		else if (A[i] == B[i])
		{
			result.num = '0' + result.num;
		}
		else
		{
			char temporary = '0' + (A[i] - B[i]);
			result.num = temporary + result.num;
		}
	}

	result.num = BigInteger::SubZero(result.num);
	result.numLength = result.num.length();
	return result;
}

/*
大整数加法
输入：两个大整数A，B
输出：result
status参照BigInteger::Compare()
*/
int BigInteger::Addition(BigInteger numA, BigInteger numB, BigInteger *result)
{
	if (&numA == NULL || &numB == NULL || result == NULL)
	{
		return E_BIGINT_NPT;
	}
	result->setEmpty();
	int status;
	status = BigInteger::Compare(numA, numB);
	//BigInteger *result = new BigInteger;
	switch (status)
	{
	case(0): {
		result->setData(BigInteger::_BaseAddition(numA, numB));
		if (numA.isNegative)
		{
			result->isNegative = true;
			result->numLength++;
		}
		break;
	}case(10): {
		result->num = "0";
		result->numLength++;
		break;
	}case(20): {
		result->num = "0";
		result->numLength++;
		break;
	}case(11): {
		if (!numA.isNegative && numB.isNegative)
		{
			result->setData(BigInteger::_BaseSubtraction(numA, numB));
		}
		else if(!numA.isNegative && !numB.isNegative)
		{
			result->setData(BigInteger::_BaseAddition(numA, numB));
		}
		break;
	}case(12): {
		if (numA.isNegative && numB.isNegative)
		{
			result->setData(BigInteger::_BaseAddition(numA, numB));
			result->isNegative = true;
		}
		else if (!numA.isNegative && numB.isNegative)
		{
			result->setData(BigInteger::_BaseSubtraction(numB, numA));
			result->isNegative = true;
		}
		break;
	}case(21): {
		if (numA.isNegative && numB.isNegative)
		{
			result->setData(BigInteger::_BaseAddition(numA, numB));
			result->isNegative = true;
		}
		else if (numA.isNegative && !numB.isNegative)
		{
			result->setData(BigInteger::_BaseSubtraction(numA, numB));
			result->isNegative = true;
		}
		break;
	}case(22): {
		if (!numA.isNegative && !numB.isNegative)
		{
			result->setData(BigInteger::_BaseAddition(numA, numB));
		}
		else if (numA.isNegative && !numB.isNegative)
		{
			result->setData(BigInteger::_BaseSubtraction(numB, numA));
		}
		break;
	}
	}

	return E_BIGINT_OK;
}

/*
大整数减法
输入：两个整数A, B
输出： result
status参照BigInteger::Compare()
*/
int BigInteger::Subtraction(BigInteger numA, BigInteger numB, BigInteger *result)
{
	if (&numA == NULL || &numB == NULL || result == NULL)
	{
		return E_BIGINT_NPT;
	}
	result->setEmpty();
	int status = BigInteger::Compare(numA, numB);
	switch (status)
	{
	case(0): {
		result->num = "0";
		break;
	}case(10): {
		result->setData(BigInteger::_BaseAddition(numA, numB));
		break;
	}case(20): {
		result->setData(BigInteger::_BaseAddition(numA, numA));
		result->isNegative = true;
		break;
	}case(11): {
		if (!numA.isNegative && numB.isNegative)
		{
			result->setData(BigInteger::_BaseAddition(numA, numB));
		}
		else if (!numA.isNegative && !numB.isNegative)
		{
			result->setData(BigInteger::_BaseSubtraction(numA, numB));
		}
		break;
	}case(12): {
		if (numA.isNegative && numB.isNegative)
		{
			result->setData(BigInteger::_BaseSubtraction(numB, numA));
		}
		else if (!numA.isNegative && numB.isNegative)
		{
			result->setData(BigInteger::_BaseAddition(numA, numB));
		}
		break;
	}case(21): {
		if (numA.isNegative && numB.isNegative)
		{
			result->setData(BigInteger::_BaseSubtraction(numA, numB));
			result->isNegative = true;
		}
		else if (numA.isNegative && !numB.isNegative)
		{
			result->setData(BigInteger::_BaseAddition(numA, numB));
			result->isNegative = true;
		}
		break;
	}case(22): {
		if (!numA.isNegative && !numB.isNegative)
		{
			result->setData(BigInteger::_BaseSubtraction(numB, numA));
			result->isNegative = true;
		}
		else if (numA.isNegative && !numB.isNegative)
		{
			result->setData(BigInteger::_BaseAddition(numA, numB));
			result->isNegative = true;
		}
		break;
	}
	}
	return E_BIGINT_OK;
}

/*
最基本乘法
输入： 
	A  ： 任意整数
	num： 单一整数
输出：result
*/
string BigInteger::_BaseMultiplication(BigInteger numA, char num)
{
	string result = "";
	string A = numA.AddZeroFront(1);
	int _num = num - '0';

	int carry = 0; //进位

	for (int i = numA.numLength; i >= 0; i--)
	{
		int temporary = (A[i] - '0') * _num;
		if (temporary < 10)
		{
			if (temporary + carry >= 10)
			{
				result = (char)(((temporary + carry) % 10) + '0') + result;
				carry = (temporary + carry) / 10;
			}
			else 
			{
				result = (char)((temporary + carry) + '0') + result;
				carry = 0;
			}
		}
		else
		{
			result = (char)(((temporary + carry) % 10) + '0') + result;
			carry = (temporary + carry) / 10;
		}
	}
	result = BigInteger::SubZero(result);
	return result;
}

/*
大整数乘法
输入：两个整数A, B
输出：result
*/
int BigInteger::Multiplication(BigInteger numA, BigInteger numB, BigInteger *result)
{
	if (&numA == NULL || &numB == NULL || result == NULL)
	{
		return E_BIGINT_NPT;
	}
	result->setEmpty();
	string A = numA.num;
	string B = numB.num;
	BigInteger *temporary = new BigInteger[numB.numLength];

	for (int i = 0, j = numB.numLength - 1; i < numB.numLength; i++, j--)
	{
		/**
		*i: 记录temporary数组的下标，后补零个数 
		*j: 记录numB中乘数的下标
		*/
		temporary[i] = BigInteger::_BaseMultiplication(numA, numB.num[j]);
		temporary[i] = BigInteger::AddZeroRear(&temporary[i], i);
	}
	for (int i = 0; i < numB.numLength; i++)
	{
		result->setData((*result) + temporary[i]);//
	}
	if ((numA.isNegative && !numB.isNegative) || (!numA.isNegative && numB.isNegative))
	{
		result->isNegative = true;
	}
	return E_BIGINT_OK;
}

/**
大整数除法
输入： 大整数被除数， 除数
输出： 运算结果result
*/
int BigInteger::Division(BigInteger dividend, BigInteger divisor, BigInteger *Remainder, BigInteger *result)
{
	if (&dividend == NULL || &divisor == NULL || Remainder == NULL || result == NULL)
	{
		return E_BIGINT_NPT;
	}
	if (divisor.num == "0")
	{
		return E_BIGINT_DBZ;
	}
	result->setEmpty();

	BigInteger A, B;
	A.setData(dividend);
	B.setData(divisor);
	Remainder->num = "0";

	if (divisor.num == "1") //除数为1
	{
		result->setData(dividend);
		return E_BIGINT_OK;
	}

	int status = BigInteger::Compare(A, B);

	switch (status)
	{
	case(0): {
		result->num = "1";
		break;
	}case(10):
	{
		result->num = "1";
		result->isNegative = true;
		break;
	}case(20): {
		result->num = "1";
		result->isNegative = true;
		break;
	}
	case(11): {
		BigInteger temporary;
		BigInteger _divisor;
		for (int i = 0; i < dividend.numLength; i++)
		{
			temporary.num += dividend.num[i];
			temporary.num = BigInteger::SubZero(temporary.num);
			temporary.numLength = temporary.num.length();
			int _status = BigInteger::Compare(temporary, divisor) % 10;
			if (_status == 0)
			{
				temporary.num = BigInteger::_BaseMultiplication(temporary, '0');
				temporary.numLength = 1;
				result->num += '1';
				result->numLength++;
				Remainder->num = "0";
			}
			else if (_status == 1)
			{
				char j = '1';
				while(1)
				{
					_divisor.num = BigInteger::_BaseMultiplication(divisor, j);
					_divisor.numLength = _divisor.num.length();
					if (BigInteger::Compare(temporary, _divisor) % 10 == 2)
					{
						j--;
						break;
					}
					j++;
				}
				_divisor.num = BigInteger::_BaseMultiplication(divisor, j);
				_divisor.numLength = _divisor.num.length();
				result->num += j;
				result->numLength++;
				temporary = temporary - _divisor;
				Remainder->num = temporary.num;
			}
			else if (_status == 2)
			{
				result->num += '0';
				result->numLength++;
			}
		}
		break;
	}case(12): {
		BigInteger temporary;
		BigInteger _divisor;
		for (int i = 0; i < dividend.numLength; i++)
		{
			temporary.num += dividend.num[i];
			temporary.num = BigInteger::SubZero(temporary.num);
			temporary.numLength = temporary.num.length();
			int _status = BigInteger::Compare(temporary, divisor) % 10;
			if (_status == 0)
			{
				temporary.num = BigInteger::_BaseMultiplication(temporary, '0');
				temporary.numLength = 1;
				result->num += '1';
				result->numLength++;
				Remainder->num = "0";
			}
			else if (_status == 1)
			{
				char j = '1';
				while (1)
				{
					_divisor.num = BigInteger::_BaseMultiplication(divisor, j);
					_divisor.numLength = _divisor.num.length();
					if (BigInteger::Compare(temporary, _divisor) % 10 == 2)
					{
						j--;
						break;
					}
					j++;
				}
				_divisor.num = BigInteger::_BaseMultiplication(divisor, j);
				_divisor.numLength = _divisor.num.length();
				result->num += j;
				result->numLength++;
				temporary = temporary - _divisor;
				Remainder->num = temporary.num;
			}
			else if (_status == 2)
			{
				result->num += '0';
				result->numLength++;
			}
		}
		if (!dividend.isNegative && divisor.isNegative)
		{
			result->isNegative = true;
		}
		break;
	}case(21):
	{
		result->num = "0";
		if (dividend.isNegative && !divisor.isNegative)
		{
			result->isNegative = true;
		}
		break;
	}case(22): {
		result->num = "0";
		if (dividend.isNegative && !divisor.isNegative)
		{
			result->isNegative = true;
		}
		break;
	}
	}

	result->num = BigInteger::SubZero(result->num);
	result->numLength = result->num.length();
	if ((dividend.isNegative && !divisor.isNegative) || (!dividend.isNegative && divisor.isNegative))
	{
		result->isNegative = true;
	}
	result->numLength = result->num.length();
	return E_BIGINT_OK;
}
//按位与
BigInteger BigInteger::AND_Big(BigInteger numA, BigInteger numB)
{
	if(numA.Bin == "")
	numA.DecToBin();
	if(numB.Bin == "")
	numB.DecToBin();

	BigInteger result;
	string A(numA.Bin), B(numB.Bin);
	if (A.length() < B.length())
	{
		A = BigInteger::AddZeroFront(A, B.length() - A.length());
	}
	else if (A.length() > B.length())
	{
		B = BigInteger::AddZeroFront(B, A.length() - B.length());
	}

	for (int i = A.length() - 1; i >= 0; i--)
	{
		if (A[i] == '1' && B[i] == '1')
		{
			result.Bin = "1" + result.Bin;
		}
		else
		{
			result.Bin = "0" + result.Bin;
		}
	}
	result.BinToDec();
	result.numLength = result.num.length();
	return result;
}

/*
幂运算
输入： 整数 numA， 幂 num
输出： result
*/
BigInteger BigInteger::Power(BigInteger numA, int num)
{
	BigInteger result;
	result.setEmpty();

	switch (num)
	{
	case(0): {
		if (numA.num == "0")
		{
			result.isError = true;
			return result;
		}
		result.num = "1";
		result.numLength = 1;
		break;
	}case(1): {
		result.setData(numA);
		break;
	}default: {
		result.setData(numA);
		for (int i = 1; i < num; i++)
		{
			result = (result * (numA));
		}
	}
	}

	return result;
}

BigInteger BigInteger::Power(BigInteger numA, BigInteger num)
{
	BigInteger result;

	if (numA.num == "0" && num.num == "0")
	{
		result.isError = true;
		return result;
	}
	result.num = "1";
	while (num.num != "0")
	{
		result = result * numA;
		num--;
	}
	result.numLength = result.num.length();
	return result;
}

//字符串前补零
string BigInteger::AddZeroFront(int number)
{

	string result = "";
	for (int i = 0; i < number; i++)
	{
		result += '0';
	}
	result += this->num;
	return result;
}


//static 字符串前补零
std::string BigInteger::AddZeroFront(std::string A, int number)
{
	string result = "";
	for (int i = 0; i < number; i++)
	{
		result += '0';
	}
	result += A;
	return result;
}

//static BigInteger后补零
BigInteger BigInteger::AddZeroRear(BigInteger *A, int number)
{
	string temporary = "";
	BigInteger *result = new BigInteger;
	for (int i = 0; i < number; i++)
	{
		temporary += '0';
	}
	result->num = A->num + temporary;
	result->numLength = result->num.length();
	return *result;
}



//消去起始的0
std::string BigInteger::SubZero(string input)
{
	string result = "";
	int i = 0;
	while (input[i] == '0')
	{
		i++;
	}
	for (; i < input.length(); i++)
	{
		result += input[i];
	}
	if (result.length() == 0)
	{
		result = "0";
	}
	return result;
}

/*
用途： 两数的绝对值比较
输入： 两个整数
输出：
	 0： A的绝对值等于B
	 1： A的绝对值大于B
	 2： A的绝对值小于B
	0x： A的真值等于B
	1x： A的真值大于B
	2x： A的真值小于B
所有可能状态：0, 11, 12, 21, 22, 10, 20
*/
int BigInteger::Compare(BigInteger numA, BigInteger numB)
{
	if (numA.numLength > numB.numLength) //A绝对值大于B
	{
		if ((numA.isNegative && numB.isNegative) || (numA.isNegative && !numB.isNegative)) {
			return 21;
		}
		else if ((!numA.isNegative && numB.isNegative) || (!numA.isNegative && !numB.isNegative)) {
			return 11;
		}
	}
	else if (numA.numLength < numB.numLength) //A绝对值小于B
	{
		if ((numA.isNegative && numB.isNegative) || (!numA.isNegative && numB.isNegative)) {
			return 12;
		}
		else if ((!numA.isNegative && !numB.isNegative) || (numA.isNegative && !numB.isNegative)) {
			return 22;
		}
	}
	else {
		for (int i = 0; i < numA.numLength; i++)
		{
			if (numA.num[i] > numB.num[i]) //A绝对值大于B
			{
				if ((numA.isNegative && numB.isNegative) || (numA.isNegative && !numB.isNegative)) {
					return 21;
				}
				else if ((!numA.isNegative && numB.isNegative) || (!numA.isNegative && !numB.isNegative)) {
					return 11;
				}
			}
			else if (numA.num[i] < numB.num[i]) //A绝对值小于B
			{
				if ((numA.isNegative && numB.isNegative) || (!numA.isNegative && numB.isNegative)) {
					return 12;
				}
				else if ((!numA.isNegative && !numB.isNegative) || (numA.isNegative && !numB.isNegative)) {
					return 22;
				}
			}
		}
		if ((numA.isNegative && numB.isNegative) || (!numA.isNegative && !numB.isNegative))
		{
			return 0;
		}
		else if (numA.isNegative && !numB.isNegative)
		{
			return 20;
		}
		else
		{
			return 10;
		}
	}
}
//Mod
BigInteger BigInteger::Mod(BigInteger numA, BigInteger numB)
{
	BigInteger *result = new BigInteger;
	BigInteger *useless = new BigInteger;
	int status = BigInteger::Compare(numA, numB) % 10;
	switch (status)
	{
	case(0):
	{
		result->num = "0";
		result->numLength = 1;
		break;
	}case(1): {
		BigInteger::Division(numA, numB, result, useless);
		break;
	}case(2): {
		result->setData(numA);
		break;
	}
	}
	result->numLength = result->num.length();
	return *result;
}
//最大公约数
BigInteger BigInteger::Gcd(BigInteger numA, BigInteger numB)
{
	BigInteger result;
	BigInteger swap;
	BigInteger A;
	A.setData(numA);
	BigInteger B;
	B.setData(numB);
	if (A < B)
	{
		swap.setData(A);
		A.setData(B);
		B.setData(swap);
	}
	while (1)
	{
		if (B.num == "0")
		{
			break;
		}
		swap.setData(BigInteger::Mod(A, B));
		A.setData(B);
		B.setData(swap);
	}
	result.setData(A);
	return result;
}

BigInteger BigInteger::Random(BigInteger Down, BigInteger Up)
{
	BigInteger result;

	if (Down >= Up)
	{
		result.isError = true;
		return result;
	}

	LARGE_INTEGER nFrequency;
	if (QueryPerformanceFrequency(&nFrequency))
	{
		LARGE_INTEGER nStartCounter;
		QueryPerformanceCounter(&nStartCounter);
		srand((unsigned)nStartCounter.LowPart);
	}
	char temporary;
	while (result > Up || result < Down)
	{
		result.setEmpty();
		int length = (rand() % (Up.numLength - Down.numLength + 1)) + Down.numLength;
		for (int i = 0; i < length; i++)
		{
			temporary = '0' + rand() % 10;
			result.num += temporary;
		}
		result.num = BigInteger::SubZero(result.num);
		result.numLength = result.num.length();
	}
	result.numLength = result.num.length();
	
	return result;
}

//素性测试
bool BigInteger::MR_algorithm(BigInteger num, int k, BigInteger q)
{
	BigInteger K(k);
	BigInteger a = BigInteger::Random(BIG_TWO, num - BIG_TWO);
	if (BigInteger::Mod(a * q, num) == BIG_ONE)
	{
		return true;
	}
	BigInteger temporary, result;
	for (int j = 0; j <= k; j++)
	{
		temporary = BigInteger::Power(BIG_TWO, j) * q;
		result = BigInteger::Mod(BigInteger::Power(a, temporary), num);
		if ((result == (num - BIG_ONE)) || result == BIG_ONE)
		{
			return true;
		}
	}
	return false;
}

bool BigInteger::IsPrime(BigInteger input)
{
	if ((input % BIG_TWO) == BIG_ZERO)
	{
		return false;
	}
	int k = 0;
	BigInteger q(input);
	q--;
	while ((q % BIG_TWO) == BIG_ZERO)
	{
		q = q / BIG_TWO;
		k++;
	}
	bool result;
	for (int i = 0; i < 3; i++)
	{
		result = BigInteger::MR_algorithm(input, k, q);
		if (!result)
		{
			return false;
		}
	}
	return true;
}

//重载= int赋值
void BigInteger::operator=(int &num)
{
	if (num < 0)
	{
		this->isNegative = true;
		num = 0 - num;
	}
	this->setEmpty();
	char temporary;
	while (num != 0)
	{
		temporary = '0' + (num % 10);
		this->num = temporary + this->num;
		num = num / 10;
	}
	this->num = SubZero(this->num);
	this->numLength = this->num.length();

}
//重载++
BigInteger BigInteger::operator++(int)
{
	*this = (*this) + BIG_ONE;
	return *this;
}
BigInteger BigInteger::operator++()
{
	*this = (*this) + BIG_ONE;
	return *this;
}

//重载--
BigInteger BigInteger::operator--(int)
{
	*this = (*this) - BIG_ONE;
	return *this;
}
BigInteger BigInteger::operator--()
{
	*this = (*this) - BIG_ONE;
	return *this;
}


//重载+
BigInteger operator +(BigInteger& numA, BigInteger& numB)
{
	BigInteger *result = new BigInteger;
	if (BigInteger::Addition(numA, numB, result))
	{
		return *result;
	}
}
//重载-
BigInteger  operator-(BigInteger &numA, BigInteger &numB)
{
	BigInteger *result = new BigInteger;
	if (BigInteger::Subtraction(numA, numB, result))
	{
		return *result;
	}
}
//重载*
BigInteger operator *(BigInteger &numA, BigInteger &numB)
{
	BigInteger *result = new BigInteger;
	if (BigInteger::Multiplication(numA, numB, result))
	{
		return *result;
	}
}
//重载/
BigInteger operator /(BigInteger &numA, BigInteger &numB)
{
	BigInteger *remainder = new BigInteger;
	BigInteger *result = new BigInteger;
	if (BigInteger::Division(numA, numB, remainder, result))
	{
		return *result;
	}
}
//重载%
BigInteger operator %(BigInteger &numA, BigInteger &numB)
{
	BigInteger result;
	result = BigInteger::Mod(numA, numB);
	return result;
}
BigInteger operator&(BigInteger &numA, BigInteger &numB)
{
	BigInteger result;
	result = BigInteger::AND_Big(numA, numB);
	return result;
}
//重载 <
bool operator<(BigInteger &numA, BigInteger &numB)
{
	int status = BigInteger::Compare(numA, numB) / 10;
	if (status == 2)
	{
		return true;
	}
	return false;
}
//重载 <=
bool operator<=(BigInteger &numA, BigInteger &numB)
{
	int status = BigInteger::Compare(numA, numB) / 10;
	if (status == 2 || status == 0)
	{
		return true;
	}
	return false;
}
//重载 >
bool operator>(BigInteger &numA, BigInteger &numB)
{
	int status = BigInteger::Compare(numA, numB) / 10;
	if (status == 1)
	{
		return true;
	}
	return false;
}
//重载 >=
bool operator>=(BigInteger &numA, BigInteger &numB)
{
	int status = BigInteger::Compare(numA, numB) / 10;
	if (status == 1 || status == 0)
	{
		return true;
	}
	return false;
}
//重载 ==
bool operator==(BigInteger &numA, BigInteger &numB)
{
	int status = BigInteger::Compare(numA, numB);
	if (status == 0)
	{
		return true;
	}
	return false;
}
//重载!=
bool operator!=(BigInteger &numA, BigInteger &numB)
{
	if (BigInteger::Compare(numA, numB) != 0)
	{
		return true;
	}
	return false;
}
//重载 <<
ostream & operator << (ostream &out, BigInteger &num)
{
	if (num.isError)
	{
		out << "error!";
		return out;
	}
	if (num.isNegative)
	{
		if (num.num == "0")
		{
			out << num.num;
			num.isNegative = false;
		}
		else {
			out << '-' << num.num;
		}
	}
	else
	{
		out << num.num;
	}
	return out;
}
//重载 <<
std::ostream & operator<<(std::ostream & out, BigInteger * num)
{
	if (num->isError)
	{
		out << "error!";
		return out;
	}
	if (num->isNegative)
	{
		if (num->num == "0")
		{
			out << num->num;
			num->isNegative = false;
		}
		else {
			out << '-' << num->num;
		}
	}
	else
	{
		out << num->num;
	}
	return out;
}
//重载 >>
std::istream & operator >> (std::istream &in, BigInteger &numA)
{
	string num = "";
	if (num[0] == '0' && (num[1] == 'x' || num[1] == 'X'))
	{
		numA.conversion = BIGINT_HEX;
		num.erase(0, 2);
		numA.num = num;
	}
	else if (num[0] == '0' && num[1] == 'B')
	{
		numA.conversion = BIGINT_BIN;
		num.erase(0, 2);
		numA.num = num;
	}
	else
	{
		if (num[0] == '-')
		{
			numA.isNegative = true;
			num.erase(0, 1);
		}
		numA.num = num;
	}
	numA.num = BigInteger::SubZero(num);
	numA.numLength = numA.num.length();
	return in;
}
//重载 >>
std::istream & operator >> (std::istream & in, BigInteger * numA)
{
	string num = "";
	if (num[0] == '0' && (num[1] == 'x' || num[1] == 'X'))
	{
		numA->conversion = BIGINT_HEX;
		num.erase(0, 2);
		numA->num = num;
	}
	else if (num[0] == '0' && num[1] == 'B')
	{
		numA->conversion = BIGINT_BIN;
		num.erase(0, 2);
		numA->num = num;
	}
	else
	{
		if (num[0] == '-')
		{
			numA->isNegative = true;
			num.erase(0, 1);
		}
		numA->num = num;
	}
	numA->num = BigInteger::SubZero(num);
	numA->numLength = numA->num.length();
	return in;
}
