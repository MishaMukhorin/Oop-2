#include "VectorProcessor.h"
#include "stdafx.h"

using namespace std;
using namespace std::placeholders;

void ProcessVector(std::vector<double>& numbers)
{

    size_t numberOfPositives = 0;

    //
    // функция, суммирующая только положительные числа с подсчетом их количества
    auto addIfPositive = [&numberOfPositives](double acc, double current) {
        if (current > 0)
        {
            ++numberOfPositives;
            return acc + current;
        }
        return acc;
    };

    auto sumOfPositives = accumulate(numbers.begin(), numbers.end(), 0.0, addIfPositive);

    double avg = (numberOfPositives > 0) ? sumOfPositives / static_cast<double>(numberOfPositives) : 0.0;

   // std::sort(numbers.begin(), numbers.end());

    transform(numbers.begin(), numbers.end(), numbers.begin(), [avg](double current){
        return current + avg;
    });
}