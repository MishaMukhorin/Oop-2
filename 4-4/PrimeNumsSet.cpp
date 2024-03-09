#include <array>
#include "PrimeNumsSet.h"

using namespace std;

std::vector<long> GeneratePrimeNumbersSet(long upperBound)
{
    if (upperBound < 2)
        return {};

    std::vector<bool> sieve(upperBound + 1, true);  // +1 потому что в векторах исчисление начинается с нуля, соответственно количество на один больше.
    sieve[0] = sieve[1] = false;
    auto sqrtUpperBound = std::sqrt(upperBound);
    int step;
    int j;

    for (int i = 2; i <= sqrtUpperBound + 1; ++i)
        if (sieve[i])
        {
            for (j = i * i, step = i != 2 ? i + i : i; j <= upperBound; j += step)
            {
                sieve[j] = false;  //10 000 000 000
            }
        }

    std::vector<long> primeNumbers{};
    primeNumbers.reserve(upperBound / 10 + 2);

    primeNumbers.push_back(2);

    for (int i = 3; i <= upperBound; i += 2)
        if (sieve[i])
            primeNumbers.push_back(i);

    return primeNumbers;
}
