#include "PrimeNumsSet.h"

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

int StringToNum(const std::string& str, int number, bool& wasError)
{
    wasError = false;
    int result = 0;
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
        if (result > (std::numeric_limits<int>::max() - digit) / number)
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
int CheckOutPrimes(std::string input)
{
    bool wasError = false;

    int upperBound = StringToNum(input, 10, wasError);
    if (wasError || upperBound < 0)
    {
        std::cout << "Error: invalid source upper bound.\n";
        return 1;
    }

    std::set<int> primes = GeneratePrimeNumbersSet(upperBound);

    std::set<int>::iterator it, itn;
    int maxDiff = 0, maxs, maxb;
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
