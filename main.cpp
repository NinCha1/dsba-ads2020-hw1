#define PY_SSIZE_T_CLEAN

#include "multiplicator.h"
#include <cmath>


void Average(size_t n, std::ostream& out)
{
    std::srand(time(NULL));
    double time1 = 0, time2 = 0, time3 = 0;

    for(int i = 0; i < 3; i++)
    {
        std::pair<Number,Number> P = Multiplicator::generateRandomPair(n);

        double start1 = clock();
        Multiplicator::GradeSchoolMultiplication(P);
        double end1 = clock();
        time1 += ((end1-start1) / CLOCKS_PER_SEC);

        double start2 = clock();
        Multiplicator::DivideAndConquer(P);
        double end2 = clock();
        time2 += ((end2-start2) / CLOCKS_PER_SEC);

        double start3 = clock();
        Multiplicator::Karatsuba(P);
        double end3 = clock();
        time3 += ((end3-start3)/ CLOCKS_PER_SEC);

        time1 /= 3.0;
        time2 /= 3.0;
        time3 /= 3.0;
    }
    out << n << ',' << time1 << ',' << time2 << ',' << time3 << '\n';
}

int main()
{
    Number a, b;
    std::srand(time(NULL));
    std::pair<Number, Number> P;
    P = Multiplicator::generateRandomPair(5);
    std::cout << Multiplicator::GradeSchoolMultiplication(P);
    std::cout << Multiplicator::DivideAndConquer(P);
    std::cout << Multiplicator::Karatsuba(P);
    std::cout << P.first << P.second;


std::ofstream data(R"(C:\Users\ninou\Desktop\HSE2019-2020\BigHW\table.csv)");
for(int i = 1; i < 100; i++)
    Average(i, data);
    return 0;
}