#include "PrimeNumsSet.h"
#include "chrono"



int CharToInt(const char c, bool& wasError)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    else if (c >= 'A' && c <= 'Z')
        return c - 'A' + 10;
    else
        wasError = true;
    return 0;
}

long StringToNum(const std::string& str, long number, bool& wasError)
{
    wasError = false;
    long result = 0;
    int sign = 1;
    for (char c : str)
    {
        if (c == '-')
        {
            sign = -1;
            continue;
        }
        int digit = CharToInt(c, wasError);
        if (digit >= number) {
            wasError = true;
            break;
        }
        long max = std::numeric_limits<long>::max();
        if (result > (max - digit) / number)
        {
            wasError = true;
            break;
        }
        result = result * number + digit;
    }
    if (wasError)
        return 0;
    return result * sign;
}
long CheckOutPrimes(const std::string& input)
{
    bool wasError = false;

    long upperBound = StringToNum(input, 10, wasError);
    if (wasError || upperBound < 0)
    {
        std::cout << "Error: invalid source upper bound.\n";
        return 1;
    }
    auto start1 = std::chrono::high_resolution_clock::now();
    auto start2 = std::chrono::high_resolution_clock::now();
    std::vector<long> primes;

    auto minDur = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::seconds(10));
    auto avDur = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::seconds(0));
    for (int i = 0; i < 103; ++i)
    {
            auto start = std::chrono::high_resolution_clock::now();
            primes = GeneratePrimeNumbersSet(upperBound);
            auto end = std::chrono::high_resolution_clock::now();

        auto duration = duration_cast<std::chrono::microseconds>(end - start);
        if (minDur > duration)
        {
            minDur = duration;
        }
        avDur += duration;
        if (i % 100 == 0)
            std::cout << i << std::endl;
    }

    std::cout << "min: " << minDur.count() / 1000 << " millisecondseconds " << minDur.count() % 1000 << " microseconds for " <<  upperBound << std::endl;
    std::cout << "average: " << avDur.count() / 50000  << " millisecondseconds " << avDur.count() / 50 % 1000 << " microseconds for " <<  upperBound << std::endl;

    std::cout << primes.size() << std::endl;

    std::vector<long>::iterator it, itn;
    long maxDiff = 0, maxs, maxb;
    itn = primes.begin();

    for(it = primes.begin(); it != primes.end(); it++)
    {
        itn++;
        if ((*itn - *it) > maxDiff)
        {
            maxDiff = *itn - *it;
            maxs = *it;
            maxb = *itn;
        }

    }
    std::cout << maxDiff << " " << maxs << " < " << maxb <<"\n";
    return 0;
}

int main(int argc, char **argv)
{
    std::cout << "Check cout primes \n";
    return CheckOutPrimes(argv[1]);
}
