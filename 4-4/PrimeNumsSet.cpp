#include <array>
#include "PrimeNumsSet.h"

using namespace std;

std::vector<int> GeneratePrimeNumbersSet(int upperBound)
{
    if (upperBound < 2)
        return {};

    std::vector<int> primeNumbers{};

    std::vector<bool> sieve(upperBound + 1, true);  // +1 потому что в векторах исчисление начинается с нуля,
                                                            // соответственно количество на один больше.
    sieve[0] = sieve[1] = false;
    int sqrtUpperBound = int(std::sqrt(upperBound));

    for (int i = 2; i <= sqrtUpperBound + 1; ++i)
        if (sieve[i]){
            int step = i != 2 ? i + i : i;
            for (int j = i * i; j <= upperBound; j += step)
                sieve[j] = false;
        }

    primeNumbers.push_back(2);

    for (int i = 3; i <= upperBound; i += 2)
        if (sieve[i])
            primeNumbers.push_back(i);

    return primeNumbers;
}
