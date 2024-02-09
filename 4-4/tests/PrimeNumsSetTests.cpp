#include "../PrimeNumsSet.h"
#include <gtest/gtest.h>

using namespace std;

TEST (GeneratePrimeNumbersSet_function, primes_for_hundred_mil)
{
    EXPECT_EQ(GeneratePrimeNumbersSet(100000000).size(), 5761455);
}

TEST (GeneratePrimeNumbersSet_function, primes_for_hundred_mil_one)
{
    EXPECT_EQ(GeneratePrimeNumbersSet(100000001).size(), 5761455);
}

TEST (GeneratePrimeNumbersSet_function, primes_for_hundred_mil_7)
{
    EXPECT_EQ(GeneratePrimeNumbersSet(100000007).size(), 5761456);
}

TEST (GeneratePrimeNumbersSet_function, primes_for_one)
{
    EXPECT_EQ(GeneratePrimeNumbersSet(1).size(), 0);
}


TEST (GeneratePrimeNumbersSet_function, primes_for_two)
{
    EXPECT_EQ(GeneratePrimeNumbersSet(2).size(), 1);
}

TEST (GeneratePrimeNumbersSet_function, primes_for_13)
{
    std::vector<int> check = {2, 3, 5, 7, 11, 13};
    EXPECT_EQ(GeneratePrimeNumbersSet(13), check); //check set
}

TEST (GeneratePrimeNumbersSet_function, primes_for_12)
{
    std::vector<int> check = {2, 3, 5, 7, 11};
    EXPECT_EQ(GeneratePrimeNumbersSet(12), check); //check set
}

TEST (GeneratePrimeNumbersSet_function, primes_for_three)
{
    EXPECT_EQ(GeneratePrimeNumbersSet(3).size(), 2);
}

TEST (GeneratePrimeNumbersSet_function, primes_for_zero)
{
    EXPECT_EQ(GeneratePrimeNumbersSet(0).size(), 0);
}

GTEST_API_ int main(int argc, char **argv)
{
    cout << "Running tests \n";
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}