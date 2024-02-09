#include "..\VectorProcessor.h"
#include <gtest/gtest.h>

using namespace std;

bool VectorsAreEqual(vector<double> const& x, vector<double> const& y)
{
    return x == y;
}

// Создает пустой вектор из пустого вектора
TEST (ProcessVector_function, makes_empty_vector_from_empty_vector)
{
    vector<double> emptyVector, checkVector;
    ProcessVector(emptyVector);
    EXPECT_EQ(emptyVector, checkVector);
}

// Проверяет вектор который не должен измениться так как без положительных чисел
TEST (ProcessVector_function, does_not_change_vector_containing_no_positive_numbers)
{
    vector<double> numbers = { -4, -3, 0 };
    auto copy(numbers); // аналог vector<double> copy(numbers);
    ProcessVector(numbers);
    EXPECT_TRUE(VectorsAreEqual(numbers, copy));
}

// при обработке вектора с одним положительным числом должна добавить это число ко всем элементам вектора
TEST (ProcessVector_function, should_add_this_number_to_each_element)
{
    vector<double> numbers = { -1, 3.5 };
    ProcessVector(numbers);
    EXPECT_TRUE(VectorsAreEqual( numbers, {(-1 + 3.5), (3.5 + 3.5)}));
}

// при обработке вектора с несколькими положительными элементами должен добавить их среднее арифметическое к каждому элементу
TEST (ProcessVector_function, should_add_their_average_to_each_element)
{
    vector<double> numbers = { -1, 1, 2, 3 };
    ProcessVector(numbers);
    const double average = (1.0 + 2.0 + 3.0) / 3;
    EXPECT_TRUE(VectorsAreEqual( numbers,
                            { (-1 + average), (1 + average), (2 + average), (3 + average) } ));
}

//// должно проделать предыдущий тест, но с сортировкой элементов по возрастанию
//TEST (ProcessVector_function, should_sort)
//{
//    vector<double> numbers = { 2, 3, -1, 1 };
//    ProcessVector(numbers);
//    const double average = (1.0 + 2.0 + 3.0) / 3;
//    EXPECT_TRUE(VectorsAreEqual( numbers,
//                            { (-1 + average), (1 + average), (2 + average), (3 + average) } ));
//}

GTEST_API_ int main (int argc, char **argv)
{
    cout << "Running tests /n";
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}