#ifndef BIGHWEX_MULTIPLICATOR_H
#define BIGHWEX_MULTIPLICATOR_H

#endif //BIGHWEX_MULTIPLICATOR_H

#include "number.h"

class Multiplicator
{
public:
    static std::pair<Number, Number> generateRandomPair(const int& size)
    {
        Number number1;
        Number number2;
        for(size_t i = 0; i < size; i++)
        {
            UShort a = std::rand() % 10;
            number1.pushBack(a);
        }
        if(number1[0] == 0)
        {
            number1.reverse();
            number1.popBack();
            UShort w = 1 + std::rand() % 9;
            number1.pushBack(w);
            number1.reverse();
        }

        for(size_t i = 0; i < size; i++)
        {
            UShort a = std::rand() % 10;
            number2.pushBack(a);
        }
        if(number2[0] == 0)
        {
            number2.reverse();
            number2.popBack();
            UShort w = 1 + std::rand() % 9;
            number2.pushBack(w);
            number2.reverse();
        }
        return std::make_pair(number1, number2);
    }


    static std::pair<Number, Number> split(Number& num)
    {
        std::pair<Number, Number> newNums;
        for(int i = 0; i < num.size() / 2; i++)
        {
            newNums.first.pushBack(num[i]);
        }
        for(int j = num.size() / 2; j < num.size(); j++)
        {
            newNums.second.pushBack(num[j]);
        }
        return newNums;
    }

    static Number GradeSchoolMultiplication(const std::pair<Number, Number>& multipliers)
    {
        std::pair<Number, Number> num = multipliers;
        Number::makeEqual(num.first, num.second);
        Number answer(2 * num.first.size(), 0); // the size of the product is at most 2*size of multiple
        for(int i = num.second.size() - 1; i > -1; i--)
        {
            for(int j = num.first.size() - 1; j > -1; j--)
            {
                UShort temp = num.first[j] * num.second[i];
                if(temp > 9)
                {
                    answer[answer.size() - 2 - i - j] += temp % 10;
                    answer[answer.size() - 1 - i - j] += temp / 10;
                }
                else
                    answer[answer.size() - 2 - i - j] += temp;
            }
        }
        for(int check = 1; check < answer.size(); check ++)
        {
            if (answer[check] > 9)
            {
                UShort decades = answer[check] / 10;
                answer[check] = answer[check] % 10;
                answer[check + 1] += decades;
            }
        }
        answer.reverse();

        if(answer[0] == 0) //in case we've put "too much" 0's
            answer.popFront();
        return answer;
    }
    static Number DivideAndConquer(const std::pair<Number, Number>& Multiples)
    {
        std::pair<Number, Number> temp = Multiples;

        if(temp.first.size() != temp.second.size())
            Number::makeEqual(temp.first, temp.second);

        int n = temp.first.size();

        if(temp.first.size() <= 1)
            return GradeSchoolMultiplication(temp);


        std::pair<Number, Number> part1 = split(temp.first);
        std::pair<Number, Number>  part2 = split(temp.second);

        Number::makeEqual(part1.first, part1.second);
        Number::makeEqual(part2.first, part2.second);

        Number ac = DivideAndConquer(std::make_pair(part1.first, part2.first));
        Number ad = DivideAndConquer(std::make_pair(part1.first, part2.second));
        Number bc = DivideAndConquer(std::make_pair(part1.second, part2.first));
        Number bd = DivideAndConquer(std::make_pair(part1.second, part2.second));

        Number adbc = ad + bc;

        Number answer = Number::powOften(ac, 2 * (n - n / 2)) + Number::powOften(adbc, (n - n / 2)) + bd;


        for(int i = 0; i < answer.size(); i++) // to delete the 0's that occur due to makeEqual method
        {
            if(answer[0] == 0)
                answer.popFront();
            else
                break;
        }
        return answer;
    }

    static Number Karatsuba(const std::pair<Number, Number>& Multiples)
    {
        std::pair<Number, Number> temp = Multiples;

        for (int i = 0; i < temp.first.size(); i++)
        {
            if(temp.first[0])
                break;
            else
                temp.first.popFront();
        }

        for(int i = 0; i < temp.second.size(); i++)
        {
            if(temp.second[0])
                break;
            else
                temp.second.popFront();
        }

        if(temp.first.size() != temp.second.size())
            Number::makeEqual(temp.first, temp.second);

        if(temp.first.size() <= 1)
            return GradeSchoolMultiplication(Multiples);


        size_t n = temp.first.size();

        std::pair<Number, Number> part1 = split(temp.first);
        std::pair<Number, Number>  part2 = split(temp.second);

        Number::makeEqual(part1.first, part1.second);
        Number::makeEqual(part2.first, part2.second);

        Number ac = Karatsuba(std::make_pair(part1.first, part2.first));
        Number bd = Karatsuba(std::make_pair(part1.second, part2.second));
        Number adbc = Karatsuba(std::make_pair(part1.first + part1.second, part2.first + part2.second)) - ac - bd;

        Number answer = Number::powOften(ac, 2 * (n - n / 2)) + Number::powOften(adbc, n - n / 2) + bd;

        for(size_t i = 0; i < answer.size(); i++)
        {
            if(answer[0] == 0)
                answer.popFront();
            else
                break;
        }
        return answer;
    }
};