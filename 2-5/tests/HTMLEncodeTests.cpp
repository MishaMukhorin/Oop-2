#include "../HTMLEncode.h"
#include <gtest/gtest.h>

using namespace std;

// Создает пустой вектор из пустого вектора
TEST (EncodeHTML_function, encodes_html)
{
    std::string str = "Cat <says> \"Meow\". M&M's",
                check = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
    EncodeHTML(str);
    EXPECT_EQ(str, check);
}


GTEST_API_ int main (int argc, char **argv)
{
    cout << "Running tests \n";
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}