#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <deque>
#include <fstream>
#include <sstream>

typedef unsigned short UShort;

class Number {

protected:
    std::vector<UShort> _digits;

public:

    Number() {};

    Number(std::vector<UShort> input) : _digits(input) {};

    Number(int size, UShort value) : _digits(size, value) {};

    Number(const Number& a) : _digits(a._digits) //copy constructor
    {
        for (size_t i = 0; i < this->_digits.size(); ++i)
            this->_digits[i] = a._digits[i];
    }

    static void makeEqual(Number& num1, Number& num2)
    {
        if(num1.size() > num2.size())
        {
            num2.reverse();
            for(size_t i = num2.size(); i < num1.size(); i ++)
                num2.pushBack(0);
            num2.reverse();
        }
        if(num1.size() < num2.size())
        {
            num1.reverse();
            for(size_t i = num1.size(); i < num2.size(); i++)
                num1.pushBack(0);
            num1.reverse();
        }
    }

    static Number powOften(Number& num1, int power)
    {
        for(int i = 0; i < power; i++)
        {
            num1.pushBack(0);
        }
        return num1;
    }
public:
    Number& operator=(const Number& num) {
        if (this == &num)
            return *this;
        Number temp(num);
        std::swap(temp._digits, this->_digits);
        return *this;
    }

    friend Number operator+(Number num1, Number num2)
    {
        if (num1.size() != num2.size())
            makeEqual(num1, num2);
        Number result;
        UShort remainder = 0;
        for (int i = num1.size() - 1; i > -1; i--)
        {
            int temp = num1[i] + num2[i] + remainder;
            if (temp > 9) {
                temp -= 10;
                remainder = 1;
            } else
                remainder = 0;
            result.pushBack(temp);
        }
        result.pushBack(remainder);
        result.reverse();
        return result;
    }

    friend Number operator-(Number num1, Number num2)
    {
        if (num1.size() != num2.size())
            makeEqual(num1, num2);
        Number result;
        UShort remainder = 0;
        for (int i = num1.size() - 1; i > -1; i--)
        {
            if (num1[i] < num2[i])
            {
                num1[i] += 10;
                if (num1[i - 1] == 0)
                {
                    int k = 0;
                    while (num1[i - 1 - k] == 0)
                    {
                        num1[i - 1 - k] = 9;
                        k++;
                    }
                    num1[i - 1 - k]--;
                } else
                    num1[i - 1]--;
            }
            int temp = num1[i] - num2[i];
            result.pushBack(temp);
        }
        result.reverse();
        if (result[0] == 0)
            result._digits.erase(result._digits.begin());
        return result;
    }

    friend std::ostream& operator<<(std::ostream& out, const Number& N) {
        for (int _digit : N._digits)
            out << _digit;
        out << '\n';
        return out;
    }

    UShort& operator[](size_t i) {
        return _digits[i];
    }

    UShort operator[](size_t i) const {
        return _digits[i];
    }

    bool operator==(const Number& num) {
        if (this->_digits.size() != num.size())
            return false;
        for (size_t i = 0; i < num.size(); i++)
            if (this->_digits[i] != num[i])
                return false;
        return true;
    }

    void reverse()
    {
        std::reverse(_digits.begin(), _digits.end());
    }

    void pushBack(int a)
    {
        _digits.push_back(a);
    }

    void popBack()
    {
        _digits.pop_back();
    }

    void popFront()
    {
        _digits.erase(_digits.begin());
    }

    size_t size()
    {
        return _digits.size();
    }

    size_t size() const
    {
        return _digits.size();
    }
};
