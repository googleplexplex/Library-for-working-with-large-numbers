#pragma once
typedef char byte;
typedef unsigned char ubyte;
#include "strmath.hpp"
#define BYTE_MAX byte(255)
#define BYTE_MIN byte(0)
#define UBYTE_MAX ubyte(255)
#define UBYTE_MIN ubyte(0)
#define BITS_IN_BYTE (8)
#define SIZEOF_BYTE BITS_IN_BYTE

#define SET_MAX bool(true)
#define SET_MIN bool(false)

#define FROM_BIN bool(true)
#define FROM_DEC bool(false)

#ifndef GO_FROM
#define GO_FROM 1e8
#endif
#ifndef SEARCH_MEMORY_COUNT
#define SEARCH_MEMORY_COUNT 255
#endif

#ifndef MAX(f, s)
#define MAX(f, s) ((f >= s)?(f):(s))
#endif
#ifndef MIN(f, s)
#define MIN(f, s) ((f <= s)?(f):(s))
#endif

typedef enum spaceShipResultEnum
{
	fMoreS = 0,
	sMoreF,
	equals
};
#define SPACESHIP(f, s) ((f > s)?(fMoreS):((f < s)?(sMoreF):(equals)))

constexpr inline bool getBit(byte place, byte pos)
{
	return bool((1 << pos) & place);
}

ubyte getIntByte(int number, ubyte pos)
{
	return ((char*)(&number))[pos];
}
ubyte sizeOfInt(int number)
{
	for (int i = sizeof(int) - 1; i >= 0; i--)
	{
		if (getIntByte(number, i) != UBYTE_MIN)
		{
			return i + 1;
		}
	}
	return 0;
}
class uintN
{
public:
	ubyte* num;
	unsigned int size;

	inline void setMin()
	{
		memset(num, UBYTE_MIN, size);
	}
	inline void setMax()
	{
		memset(num, UBYTE_MAX, size);
	}
	uintN()
	{
		num = NULL;
		size = 0;
	};
	uintN(unsigned int _size)
	{
		size = _size;
		num = new ubyte[_size];
		setMin();
	}
	uintN(bool startFill, unsigned int _size)
	{
		size = _size;
		num = new ubyte[_size];
		if (startFill)
			setMax();
		else
			setMin();
	}
	uintN(ubyte startNum, unsigned int _size)
	{
		size = _size;
		if (_size > 0)
		{
			num = new ubyte[_size];
			num[0] = startNum;
			for (int i = 1; i < _size; i++)
			{
				num[i] = 0;
			}
		}
	}
	uintN(unsigned int startNum, unsigned int _size)
	{
		size = _size;
		num = new ubyte[_size];
		memcpy(num, &startNum, (_size > (sizeof(int))) ? (sizeof(int)) : (_size));
		if (_size > (sizeof(int)))
		{
			for (int i = _size - 1; i >= (sizeof(int)); i--)
			{
				num[i] = 0;
			}
		}
	}
	uintN(unsigned long startNum, unsigned int _size)
	{
		size = _size;
		num = new ubyte[_size];
		memcpy(num, &startNum, (_size > (sizeof(long))) ? (sizeof(long)) : (_size));
		if (_size > (sizeof(long)))
		{
			for (int i = (sizeof(long)); i < _size; i++)
			{
				num[i] = 0;
			}
		}
	}
	uintN(unsigned long long startNum, unsigned int _size)
	{
		size = _size;
		num = new ubyte[_size];
		memcpy(num, &startNum, (_size > (sizeof(long long))) ? (sizeof(long long)) : (_size));
		if (_size > (sizeof(long long)))
		{
			for (int i = (sizeof(long long)); i < _size; i++)
			{
				num[i] = 0;
			}
		}
	}
	uintN(uintN &cloner)
	{
		num = new ubyte[cloner.size];
		memcpy(num, cloner.num, cloner.size);
		size = cloner.size;
	}
	uintN(const uintN& cloner)
	{
		num = new ubyte[cloner.size];
		memcpy(num, cloner.num, cloner.size);
		size = cloner.size;
	}
	uintN(char* original, bool inputType) //bin or dec //TODO
	{
		if (inputType)
		{ //bin
			char* presentScanerPos = original;

			while (presentScanerPos[0])
			{

				presentScanerPos++;
			}
		}
		else { //dec
			char* presentScanerPos = original;

			while (presentScanerPos[0])
			{
				num[presentScanerPos - original] = presentScanerPos[0];
				presentScanerPos++;
			}
		}
	}
	uintN(char* original, size_t originalSize, bool inputType) //bin or dec //TODO
	{
		num = new ubyte[originalSize];
		if (inputType)
		{ //bin
			for (int i = 0; i < originalSize; i++)
			{

			}
		}
		else { //dec
			for (int i = 0; i < originalSize; i++)
			{
				num[i] = original[i] - '0';
			}
		}
	}
	uintN(bool _size) //TODO
	{

	}
private:
	uintN(uintN& original, bool toCreateSecondConstructor) //TODO
	{
		size = original.size;
		num = original.num;
	}
	void setPseudoname(uintN& original)
	{
		size = original.size;
		num = original.num;
	}
public:
	//Math methods
	//Uno
	uintN operator=(uintN& right)
	{
		delete[] num;
		num = new ubyte[right.size];
		memcpy(num, right.num, right.size);
		size = right.size;

		return *this;
	}
	uintN operator=(int right)
	{
		delete[] num;
		num = new ubyte[sizeof(int)];
		memset(num, 0, sizeof(int));
		*num = right;
		size = sizeof(int);

		return *this;
	}
	uintN& operator++()
	{
		uintN ret(*this); //use inside constructor to make a pseudoname
		if (num[0] != UBYTE_MAX)
		{
			num[0]++;
			return ret;
		}
		for (int i = 1; i < size; i++)
		{
			if (num[i] != UBYTE_MAX)
			{
				num[i]++;
				return ret;
			}
		}
		setMin();
		return ret;
	}
	uintN& operator++(int a)
	{
		if (num[0] != UBYTE_MAX)
		{
			num[0]++;
			return (*this);
		}
		for (int i = 1; i < size; i++)
		{
			if (num[i] != UBYTE_MAX)
			{
				//setMin();
				for (int j = i - 1; j >= 0; j--)
				{
					num[j] = UBYTE_MIN;
				}
				num[i]++;
				return (*this);
			}
		}
		setMin();
		return (*this);
	}
	uintN& operator--()
	{
		uintN ret(*this);
		if (num[size - 1] > UBYTE_MIN)
		{
			num[size - 1]--;
			return ret;
		}
		for (int i = size - 1; i >= 0; i--)
		{
			if (num[i] > UBYTE_MIN)
			{
				num[i]--;
				return (*this);
			}
		}
		setMin();
		return ret;
	}
	uintN& operator--(int a)
	{
		if (num[size - 1] > UBYTE_MIN)
		{
			num[size - 1]--;
			return (*this);
		}
		for (int i = size - 1; i >= 0; i--)
		{
			if (num[i] > UBYTE_MIN)
			{
				num[i]--;
				return (*this);
			}
		}
		setMin();
		return (*this);
	}
	//Double
	//Logic methods //Not tested
	spaceShipResultEnum spaceShip(uintN& right)
	{
		if ((*this).size > right.size)
		{
			for (int i = (*this).size - 1; i >= right.size; i--)
			{
				if ((*this).num[i] != UBYTE_MIN)
				{
					return fMoreS;
				}
			}
		}
		else if ((*this).size < right.size) {
			for (int i = right.size - 1; i >= (*this).size; i--)
			{
				if (right.num[i] != UBYTE_MIN)
				{
					return sMoreF;
				}
			}
		}

		int minSize = MIN((*this).size, right.size);
		for (int i = minSize - 1; i >= 0; i--)
		{
			if (right.num[i] != (*this).num[i])
			{
				if (right.num[i] > (*this).num[i])
				{
					return sMoreF;
				}
				else { //right.num[i] < (*this).num[i]
					return fMoreS;
				}
			}
		}

		return equals;
	}
	bool operator==(uintN& right)
	{
		spaceShipResultEnum spaceShipResult = (*this).spaceShip(right);

		switch (spaceShipResult)
		{
		case equals:
			return true;
		default:
			return false;
		}
	}
	bool operator>(uintN& right)
	{
		spaceShipResultEnum spaceShipResult = (*this).spaceShip(right);

		switch (spaceShipResult)
		{
		case fMoreS:
			return true;
		default:
			return false;
		}
	}
	bool operator<(uintN& right)
	{
		spaceShipResultEnum spaceShipResult = (*this).spaceShip(right);

		switch (spaceShipResult)
		{
		case sMoreF:
			return true;
		default:
			return false;
		}
	}
	bool operator!=(uintN& right)
	{
		return (!((*this) == right));
	}
	bool operator>=(uintN& right)
	{
		spaceShipResultEnum spaceShipResult = (*this).spaceShip(right);

		switch (spaceShipResult)
		{
		case sMoreF:
		case equals:
			return true;
		default:
			return false;
		}
	}
	bool operator<=(uintN& right)
	{
		spaceShipResultEnum spaceShipResult = (*this).spaceShip(right);

		switch (spaceShipResult)
		{
		case fMoreS:
		case equals:
			return true;
		default:
			return false;
		}
	}
public:
	uintN operator+(uintN& right) //Tested once
	{
		unsigned int maxSize = MAX((*this).size, right.size);
		unsigned int minSize = MIN((*this).size, right.size);
		uintN ret(maxSize + 1);

		bool addNow = false;
		for (int i = 0; i < minSize; i++)
		{
			unsigned short result = (*this).num[i] + right.num[i];

			if (addNow)
				result++;

			switch (SPACESHIP(result, unsigned short(UBYTE_MAX)))
			{
			case fMoreS:
				ret.num[i] = ubyte(result - UBYTE_MAX - ubyte(1));
				addNow = true;
				break;
			default: //equals || sMoreF
				ret.num[i] = ubyte(result);
				addNow = false;
				break;
			}
		}

		uintN& maxNum = (maxSize == (*this).size) ? (*this) : (right);
		if (addNow)
		{
			for (int i = minSize; i < maxSize; i++)
			{
				if (maxNum.num[i] == UBYTE_MAX)
				{
					ret.num[i] = UBYTE_MIN;
				}
				else {
					ret.num[i] = maxNum.num[i] + 1;
					memcpy(ret.num + i + 1, maxNum.num + i + 1, maxSize - i - 1);
					addNow = false;
					break;
				}
			}
		}
		else {
			memcpy(ret.num + minSize, maxNum.num + minSize, maxSize - minSize);
		}

		if (addNow)
			ret.num[ret.size - 1] = ubyte(1);
		else
			ret.num[ret.size - 1] = UBYTE_MIN;

		ret.cutNulls();
		return ret;
	}
	uintN operator-(uintN& right) //Tested once
	{
		const unsigned int maxSize = MAX((*this).size, right.size);
		const unsigned int minSize = MIN((*this).size, right.size);
		uintN ret(*this);

		bool wasIncFlag;
		for (int i = 0; i < minSize; i++)
		{
			switch (SPACESHIP((*this).num[i], right.num[i]))
			{
			case fMoreS:
				ret.num[i] -= right.num[i];
				break;
			case sMoreF:
				wasIncFlag = false;
				for (int j = i; j < maxSize; j++)
				{
					if (ret.num[j] != UBYTE_MIN)
					{
						ret.num[j]--;
						wasIncFlag = true;
						break;
					}
				}
				if (wasIncFlag)
				{
					ret.num[i] = ubyte(short(ret.num[i] + UBYTE_MAX) - right.num[i]);
				} //else Exception
				break;
			default: //equals
				ret.num[i] = UBYTE_MIN;
				break;
			}
		}

		ret.cutNulls();
		return ret;
	}
	uintN operator*(uintN& right) //Tested once
	{
		uintN ret(sizeOfNum() + right.sizeOfNum());

		for (uintN i(right); i > 0; i--)
		{
			ret += (*this);
		}

		return ret;
	}
	uintN operator/(uintN& right) //Tested once
	{
		if (right.isNull())
		{
#ifndef REMOVE_EXCEPTIONS
			throw std::exception("The divisor is zero");
#else
			return uint(SET_MIN);
#endif
		}
		uintN ret(*this);
		uintN i(size);

		for (; ret > right; i++)
		{
			ret -= right;
		}

		return i;
	}
	uintN operator%(uintN& right) //Tested once
	{
		if (right.isNull())
		{
#ifndef REMOVE_EXCEPTIONS
			throw std::exception("The divisor is zero");
#else
			return uint(SET_MIN);
#endif
		}
		uintN ret(*this);

		while (ret > right)
		{
			ret -= right;
		}

		return ret;
	}
	uintN& operator+=(uintN& right)
	{
		uintN sum = (*this) + right;
		*this = sum;
		return sum;
	}
	uintN& operator-=(uintN& right)
	{
		uintN dif = (*this) - right;
		*this = dif;
		return dif;
	}
	uintN& operator*=(uintN& right)
	{
		uintN res = (*this) * right;
		*this = res;
		return res;
	}
	uintN& operator/=(uintN& right)
	{
		uintN res = (*this) / right;
		*this = res;
		return res;
	}
	uintN& operator%=(uintN& right)
	{
		uintN res = (*this) % right;
		*this = res;
		return res;
	}
	uintN operator+(unsigned int right) //Tested once
	{
		spaceShipResultEnum spaceShipResult = SPACESHIP(size, sizeof(int));
		uintN ret(MAX(sizeof(right), size) + 1);
		bool addNow = false;

		switch (spaceShipResult)
		{
		case fMoreS:
			for (int i = 0; i < sizeof(int); i++)
			{
				short result = (*this).num[i] + getIntByte(right, i);

				if (addNow)
					result++;

				switch (SPACESHIP(result, unsigned short(UBYTE_MAX)))
				{
				case fMoreS:
					ret.num[i] = ubyte(result - UBYTE_MAX - ubyte(1));
					addNow = true;
					break;
				default: //equals || sMoreF
					ret.num[i] = ubyte(result);
					addNow = false;
					break;
				}
			}

			if (addNow)
			{
				for (int i = sizeof(int); i < size; i++)
				{
					if ((*this).num[i] != UBYTE_MAX)
					{
						(*this).num[i] = UBYTE_MIN;
					}
					else {
						ret.num[i] = (*this).num[i] + 1;
						memcpy(ret.num + i + 1, (*this).num + i + 1, size - i - 1);
						addNow = false;
						break;
					}
				}
			}
			else {
				memcpy(ret.num + sizeof(int), (*this).num + sizeof(int), (*this).size - sizeof(int));
			}

			if (addNow)
				ret.num[ret.size - 1] = ubyte(1);

			break;
		case sMoreF:
			for (int i = 0; i < (*this).size; i++)
			{
				short result = (*this).num[i] + getIntByte(right, i);

				switch (SPACESHIP(result, UBYTE_MAX))
				{
				case fMoreS:
					ret.num[i] = ubyte(result - UBYTE_MAX - ubyte(1));
					addNow = true;
					break;
				default: //equals || sMoreF
					ret.num[i] = ubyte(result);
					addNow = false;
					break;
				}
			}
			break;
		default: //equals
			ret = (int((*this).num[0]) + right);
			break;
		}
		ret.cutNulls();
		return ret;
	}
	uintN operator-(unsigned int right) //Tested once
	{
		const unsigned int maxSize = MAX((*this).size, sizeof(int));
		const unsigned int minSize = MIN((*this).size, sizeof(int));
		uintN ret(*this);

		bool wasIncFlag;
		for (int i = 0; i < minSize; i++)
		{
			ubyte intByteI = getIntByte(right, i);
			switch (SPACESHIP((*this).num[i], intByteI))
			{
			case fMoreS:
				ret.num[i] -= intByteI;
				break;
			case sMoreF:
				wasIncFlag = false;
				for (int j = i; j < maxSize; j++)
				{
					if (ret.num[j] != UBYTE_MIN)
					{
						ret.num[j]--;
						wasIncFlag = true;
						break;
					}
				}
				if (wasIncFlag)
				{
					ret.num[i] = ubyte(short(ret.num[i] + UBYTE_MAX) - intByteI);
				} //else Exception
				break;
			default: //equals
				break;
			}
		}

		ret.cutNulls();
		return ret;
	}
	uintN operator*(unsigned int right)
	{
		uintN ret(sizeOfNum() + sizeOfInt(right));

		for (uintN i((unsigned int)(right)); i > 0; i--)
		{
			ret += (*this);
		}

		return ret;
	}
	uintN operator/(unsigned int right)
	{
		if (right == 0)
		{
#ifndef REMOVE_EXCEPTIONS
			throw std::exception("The divisor is zero");
#else
			return uint(SET_MIN);
#endif
		}
		uintN ret(*this);
		uintN i(size);

		for (; ret > right; i++)
		{
			ret -= right;
		}

		return i;
	}
	uintN operator%(unsigned int right)
	{
		if (right == 0)
		{
#ifndef REMOVE_EXCEPTIONS
			throw std::exception("The divisor is zero");
#else
			return uint(SET_MIN);
#endif
		}
		uintN ret(*this);

		while (ret > right)
		{
			ret -= right;
		}

		return ret;
	}
	uintN& operator+=(unsigned int right)
	{
		uintN sum = (*this) + right;
		*this = sum;
		return sum;
	}
	uintN& operator-=(unsigned int right)
	{
		uintN sum = (*this) - right;
		*this = sum;
		return sum;
	}
	uintN& operator*=(unsigned int right)
	{
		uintN sum = (*this) * right;
		*this = sum;
		return sum;
	}
	uintN& operator/=(unsigned int right)
	{
		uintN sum = (*this) / right;
		*this = sum;
		return sum;
	}
	uintN& operator%=(unsigned int right)
	{
		uintN sum = (*this) % right;
		*this = sum;
		return sum;
	}
	unsigned int sizeOfNum(unsigned int intNum)
	{
		unsigned int* intNumPtr = &intNum;
		ubyte* numPtr = (ubyte*)intNumPtr;
		for (int i = sizeof(unsigned int) - 1; i >= 0; i--)
		{
			if (numPtr[i] != UBYTE_MIN) //TODO/TOFIX
			{
				return i + 1;
			}
		}
		return 0;
	}
	spaceShipResultEnum spaceShip(unsigned int right) //Not tested
	{
		unsigned int sizeOfNumRes = (*this).sizeOfNum();
		unsigned int sizeOfIntRes = sizeOfNum(right);
		spaceShipResultEnum spaceShipResult = SPACESHIP(sizeOfNumRes, sizeOfIntRes);
		switch (spaceShipResult)
		{
		case equals:
			return spaceShipResult;
		default: //equals
			unsigned int* tempRightNumPtr = &right;
			ubyte* rightPtr = (ubyte*)tempRightNumPtr;

			for (int i = sizeof(unsigned int) - 1; i >= 0; i--)
			{
				spaceShipResult = SPACESHIP(num[i], rightPtr[i]);
				switch (spaceShipResult)
				{
				case equals:
					break;
				default:
					return spaceShipResult;
				}
			}

			return equals;
		}
	}
	bool operator==(unsigned int right)
	{
		spaceShipResultEnum spaceShipResult = (*this).spaceShip(right);
		switch (spaceShipResult)
		{
		case equals:
			return true;
		default:
			return false;
		}
	}
	bool operator>(unsigned int right)
	{
		spaceShipResultEnum spaceShipResult = (*this).spaceShip(right);
		switch (spaceShipResult)
		{
		case fMoreS:
			return true;
		default:
			return false;
		}
	}
	bool operator<(unsigned int right)
	{
		spaceShipResultEnum spaceShipResult = (*this).spaceShip(right);
		switch (spaceShipResult)
		{
		case sMoreF:
			return true;
		default:
			return false;
		}
	}
	bool operator!=(unsigned int right)
	{
		return !((*this) == right);
	}
	bool operator>=(unsigned int right)
	{
		return !((*this) < right);
	}
	bool operator<=(unsigned int right)
	{
		return !((*this) > right);
	}
	int operator[] (int i)
	{
		return num[i];
	}
	//Input\Output methods
	char* ToBinString()
	{
		int retPos = size * BITS_IN_BYTE;
		char* ret = new char[retPos + 1];
		ret[retPos] = NULL;

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < BITS_IN_BYTE; j++)
			{
				ret[--retPos] = (char)('0' + getBit(num[i], j));
			}
		}

		return ret;
	}
	char* sToBinString(char separator)
	{
		int retPos = size * (BITS_IN_BYTE + 1) - 1;
		char* ret = new char[retPos];
		ret[retPos] = NULL;

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < BITS_IN_BYTE; j++)
			{
				ret[--retPos] = (char)('0' + getBit(num[i], j));
			}
			if (i != size - 1)
				ret[--retPos] = separator;
		}

		return ret;
	}
	char* ToString()
	{
		int lastBusyByte = size - 1;
		short lastBusyBit = SIZEOF_BYTE;
		while (!getBit(num[lastBusyByte], lastBusyBit)) //!(bool((1 << lastBusyBit) & num[lastBusyByte]))
		{
			if (lastBusyBit == 0)
			{
				lastBusyByte--;
				lastBusyBit = SIZEOF_BYTE;
			}
			lastBusyBit--;
		} if (lastBusyBit != SIZEOF_BYTE) lastBusyBit++;
		int fullDistanceTolastBusyBit = lastBusyByte * SIZEOF_BYTE + lastBusyBit;

		int countDigits = 0;
		while (fullDistanceTolastBusyBit > 0)
		{
			fullDistanceTolastBusyBit -= 4;
			countDigits++;
			if (fullDistanceTolastBusyBit < 0)
				break;

			fullDistanceTolastBusyBit -= 3;
			countDigits++;
			if (fullDistanceTolastBusyBit < 0)
				break;

			fullDistanceTolastBusyBit -= 3;
			countDigits++;
		}

		char* retString = new char[countDigits]; retString[countDigits] = NULL;
		for (int i = 0; i < countDigits; retString[i++] = '0');

		for (int i = lastBusyBit - 1; i >= 0; i--)
		{
			multiplyTwoStr(retString, countDigits);
			if (getBit(num[lastBusyByte], i))
				incStr(retString, countDigits);
		}
		for (int i = lastBusyByte - 1; i >= 0; i--)
		{
			for (int j = SIZEOF_BYTE - 1; j >= 0; j--)
			{
				multiplyTwoStr(retString, countDigits);
				if (getBit(num[i], j))
					incStr(retString, countDigits);
			}
		}

		if (retString[0] == '0')
			retString++;
		if (countDigits == 0)
		{
			retString = new char[2];
			memcpy(retString, "0", 2);
		}

		return retString;
	}
	void showBytes()
	{
		if ((*this).size == 0)
		{
			cout << 0;
			return;
		}
		for (int i = 0; i < (*this).size - 1; i++)
		{
			cout << short((*this).num[i]);
			cout << '.';
		}
		cout << short((*this).num[(*this).size - 1]);
	}
	unsigned int sizeOfNum()
	{
		for (int i = (*this).size - 1; i >= 0; i--)
		{
			if ((*this).num[i] != UBYTE_MIN)
			{
				return i + 1;
			}
		}

		return 0;
	}
	bool isNull()
	{
		return (sizeOfNum() == 0);
	}
	bool isFull()
	{
		for (int i = 0; i < (*this).size; i++)
		{
			if ((*this).num[i] != UBYTE_MAX)
			{
				return false;
			}
		}
		return true;
	}
	void cutNulls()
	{
		unsigned int sizeOfNumRes = sizeOfNum();
		if (sizeOfNumRes != 0)
		{
			if (sizeOfNumRes == (*this).size)
				return;

			ubyte* oldMemory = num;
			num = new ubyte[sizeOfNumRes];
			memcpy(num, oldMemory, sizeOfNumRes);
			size = sizeOfNumRes;
			delete[] oldMemory;
			return;
		}
		else {
			delete[] num;
			size = 0;
		}
	}
	std::ostream& operator<< (std::ostream &out)
	{
		char* numberString = ToString();
		out << numberString;
		return out;
	}
	std::istream& operator>> (std::istream &in)
	{
		char* inputBuffer = new char[100];
		in >> inputBuffer;
		uintN res(inputBuffer);
		(*this) = res;

		return in;
	}
	//TODO Перегрузка cout
	//TODO Перегрузка cin
	//TODO Функции toInt, toDouble и т.д.
	//TODO Выделение памяти через new, передавая в него наш класс
	//TODO Элемент массива числа нашего класса
};