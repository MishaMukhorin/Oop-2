#include "PrimeNumsSet.h"

std::set<long long> GeneratePrimeNumbersSet(int upperBound) {
    std::set<long long> primeNumbers;
    std::vector<bool> sieve(upperBound + 1, true);
    sieve[0] = sieve[1] = false;
    std::cout << "Start!\n";

    int sqrtUpperBound = int(std::sqrt(upperBound));
    auto start = std::chrono::high_resolution_clock::now();

    auto startPtr = sieve.begin() + 1;
    auto endPtr = sieve.begin() + sqrtUpperBound;

    int i = 2;
    while (++i, ++startPtr <= endPtr)
        if (*startPtr)
            for (long long j = i * i; j <= upperBound; j += i)
                *startPtr = false;

    startPtr = sieve.begin() + 1;
    endPtr = sieve.end();
    i = 0;
    while (++startPtr < endPtr)
        if (*startPtr)
            primeNumbers.insert(startPtr-sieve.begin());



    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Time taken by function: " << duration.count() << " microseconds" << std::endl;

    return primeNumbers;
}

int main(int argc, char **argv)
{
    std::set<long long> primes;
    primes = GeneratePrimeNumbersSet(100000000);
        std::cout << primes.size() << ", must be 5761455 \n";
    int check = 79147;
    if (primes.find(check) != primes.end()) {
        std::cout << "Element " << check << " is present in the set" << std::endl;
    }
    else {
        std::cout << "Element " << check << " not found" << std::endl;
    }
}
