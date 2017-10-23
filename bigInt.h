#pragma once
#include <iostream>
#ifndef _BIG_INT_H_
#define _BIG_INT_H_

/**
*返回值各种情况的分类
*/
#define E_BIGINT_OK  1 //成功计算
#define E_BIGINT_DBZ 0 //除数为零
#define E_BIGINT_MAL 2 //内存分配错误
#define E_BIGINT_NPT 3 //空指针作为参数传递
#define E_BIGINT_OFL 4 //上溢
#define E_BIGINT_UFL 5 //下溢
#define E_BIGINT_POW 6 //以0为底数的0次方

/**
*进制标志
*/
#define BIGINT_DEC 1 //10进制
#define BIGINT_BIN 2 //2进制
#define BIGINT_HEX 3 //16进制

/**
*三个特殊的数
*/
#define BIG_ZERO BigInteger(0)
#define BIG_ONE BigInteger(1)
#define BIG_TWO BigInteger(2)

/**
*@class  BigInteger  \bigInt.h
*@author mzc6838
*@brief  提供大整数的生成，表示，运算功能
*@notice 仅是整数运算，负数幂不包含在内
*/
class BigInteger
{
public:

	std::string num;                     //原始字符串(DEC)
	int         numLength;	             //数值长度
	bool        isNegative = false;      //负数判断
	bool        isError = false;         //错误判断，用于除数为0检测
	int         conversion;              //进制
	std::string Bin;                     //原始字符串(BIN)
	
public:

	/**
	*@brief 默认构造函数
	*/
	BigInteger() { this->num = "0"; this->numLength = 1; this->isNegative = false; this->conversion = BIGINT_DEC; this->Bin = ""; }

	/**
	*@brief 大整数的定义，赋值构造函数
	*@param s 字符串常量，表示一个超长整数
	*/
	BigInteger(std::string);

	/**
	*@brief 大整数的定义，赋值构造函数
	*@param i 整形常量，表示一个int整数
	*/
	BigInteger(int);

	/**
	*@brief 析构函数
	*/
	~BigInteger() {};

	/**
	*@brief 成员方法 复制函数
	*@param BigInteger* 被复制的大整数
	*/
	inline void setData(BigInteger);

	/**
	*@brief 成员方法 对象置空
	*@waring 此方法会将数据清除
	*/
	inline void setEmpty();

	/********************
	*进制转换
	********************/

	/**
	*@brief 十进制转换为二进制 存放于成员Bin中
	*@notice 前提是十进制有数
	*/
	inline void DecToBin();

	/**
	*@TODO 二进制转十进制
	*/
	inline void BinToDec();

	/******************
	******静态函数******
	*******************/

	/**
	*@brief 基本加法
	*@param[1] BigInteger* 第一个正整数
	*@param[2] BigInteger* 第二个正整数
	*@return BigInteger*  运算结果
	*@notice 仅支持两个正整数的加法
	*/
	inline BigInteger static _BaseAddition(BigInteger, BigInteger);

	/**
	*@brief 基本减法
	*@param[1] BigInteger* 被减数
	*@param[2] BigInteger* 减数
	*@return BigInteger*  运算结果
	*@notice 仅支持两个正数的减法，并且[被减数]大于[减数]
	*/
	inline BigInteger static _BaseSubtraction(BigInteger minuend, BigInteger meiosis);

	/**
	*@brief 大整数加法运算
	*@param[1] BigInteger* 第一个任意整数
	*@param[2] BigInteger* 第二个任意整数
	*@output   BigInteger* 加法结果
	*@return
		E_BIGINT_OK  成功
		E_BIGINT_NPT 空指针作为参数传递
	*/
	int static Addition(BigInteger, BigInteger, BigInteger*);

	/**
	*@brief 大整数减法运算
	*@param[1] BigInteger* 被减数
	*@param[2] BigInteger* 减数
	*@output   BigInteger* 减法结果
	*@return
		E_BIGINT_OK  成功
		E_BIGINT_NPT 空指针作为参数传递
	*/
	int static Subtraction(BigInteger, BigInteger, BigInteger*);
	
	/**
	*@brief 基本乘法
	*@param[1] BigInteger* 被乘数，为任意正整数
	*@param[2] c           乘数，单一[0-9]的字符
	*@return   s           运算结果
	*@notice 此方法仅限于任意正数乘10以内的数
	*/
	inline std::string static  _BaseMultiplication(BigInteger, char);

	/**
	*@brief 大整数乘法运算
	*@param[1] BigInteger* 被乘数
	*@param[2] BigInteger* 乘数
	*@output   BigInteger* 运算结果
	*@return 
		E_BIGINT_OK  成功
		E_BIGINT_NPT 空指针作为参数传递
	*/
	int static Multiplication(BigInteger, BigInteger, BigInteger*);

	/**
	*@brief 大整数除法运算
	*@param[1]  BigInteger* 被除数
	*@param[2]  BigInteger* 除数
	*@output[1] BigInteger* 余数
	*@output[2] BigInteger* 除法结果
	*@return
		E_BIGINT_OK  成功
		E_BIGINT_NPT 空指针作为参数传递
		E_BIGINT_DBZ 除数为零
	*/
	int static Division(BigInteger dividend, BigInteger divisor, BigInteger *Remainder, BigInteger*);

	/**
	*@TODO 按位与
	*/
	BigInteger static AND_Big(BigInteger, BigInteger);


	/**
	*@brief 大整数幂运算
	*@param[1] BigInteger     底数
	*@param[2] i / BigInteger 幂
	*@return   BigInteger     运算结果
	*/
	BigInteger static Power(BigInteger, int);
	BigInteger static Power(BigInteger, BigInteger);

	/**
	*@brief    成员变量num前补零
	*@param  i 补零个数
	*@return s 补零后的字符串
	*@notice   此方法不会对数值造成影响
	*/
	inline std::string AddZeroFront(int); 

	/**
	*@brief static 前补零
	*@param[1] s 需要补零的整数
	*@param[2] i 需要补零的个数
	*@return s 返回补零后的字符串代表整数
	*@notice 此方法不会对数值造成影响
	*/
	inline std::string static AddZeroFront(std::string, int);

	/**
	*@brief static 后补零
	*@param[1] BigInteger* 需要补零的大整数
	*@param[2] i 需要补零的个数
	*@return BigInteger 返回补零之后的大整数
	*@warning 此方法势必会改变数值大小
	*/
	inline BigInteger static AddZeroRear(BigInteger*, int);

	/**
	*@brief 消去任意字符串前的0
	*@param s 需要被处理的字符串
	*@return s 处理过的字符串
	*/
	inline std::string static SubZero(std::string);

	/**
	*@brief 对两个大整数进行真值以及绝对值的比较
	*@param[1] BigInteger* 第一个整数
	*@param[2] BigInteger* 第二个整数
	*@return i:
		 0： A的绝对值等于B
		 1： A的绝对值大于B
		 2： A的绝对值小于B
		0x： A的真值等于B
		1x： A的真值大于B
		2x： A的真值小于B
	*@notice 此方法对A和B的输入顺序有关
	*/
	inline int static Compare(BigInteger, BigInteger);

	/**
	*@brief 两个大整数的求模运算
	*@param[1] BigInteger* 第一个整数
	*@param[2] BigInteger* 第二个整数
	*@return   BigInteger* 两数求模的运算结果
	*/
	BigInteger static Mod(BigInteger, BigInteger);

	/**
	*@brief 求两数的最大公约数（欧几里得算法）
	*@param[1] BigInteger* 第一个数
	*@param[2] BigInteger* 第二个数
	*@return   BigInteger* 两数的最大公约数
	*/
	BigInteger static Gcd(BigInteger, BigInteger);

	/**
	*@TODO 扩展欧几里得算法
	*/
	int static *XGcd(BigInteger, BigInteger, BigInteger*, BigInteger*);

	/**
	*@brief 在范围内生成随机数
	*@param[1] BigInteger 范围下界
	*@param[2] BigInteger 范围上界
	*@return BigInteger 所生成的随机数
	*@notice 仅提供正数的随机数生成
	*/
	BigInteger static Random(BigInteger, BigInteger);

	/**
	*@brief MR素性测试算法
	*@param[1] BigInteger 需要判断的大整数
	*@param[2] i          MR算法中的k
	*@param[3] BigInteger MR算法中的q（奇数）
	*@return b 
		true: 不确定
		false: 是一个合数
	*/
	bool static MR_algorithm(BigInteger, int, BigInteger);

	/**
	*@TODO 素性测试
	*/
	bool static IsPrime(BigInteger);

	/**
	*@TODO Montgomery模幂运算
	*/
	inline BigInteger static Montgomery(BigInteger, BigInteger, BigInteger);

	/********************
	*各运算符和操作符的重载
	********************/

	void operator=(int &);
	BigInteger operator++(int);//后缀
	BigInteger operator++();
	BigInteger operator--(int);//后缀
	BigInteger operator--();
	friend BigInteger operator >> (BigInteger&, int);
	BigInteger operator >>= (int);
	friend BigInteger operator +(BigInteger&, BigInteger&);
	friend BigInteger operator -(BigInteger&, BigInteger&);
	friend BigInteger operator *(BigInteger&, BigInteger&);
	friend BigInteger operator /(BigInteger&, BigInteger&);
	friend BigInteger operator %(BigInteger&, BigInteger&);
	friend BigInteger operator &(BigInteger&, BigInteger&);
	friend bool operator <(BigInteger&, BigInteger&);
	friend bool operator <=(BigInteger&, BigInteger&);
	friend bool operator >(BigInteger&, BigInteger&);
	friend bool operator >=(BigInteger&, BigInteger&);
	friend bool operator == (BigInteger&, BigInteger&);
	friend bool operator != (BigInteger&, BigInteger&);
	friend std::ostream & operator << (std::ostream &out, BigInteger &num);	
	friend std::istream & operator >> (std::istream &in, BigInteger &num);

};//class BigInteger


#endif // !_BIG_INT_H_

