#include <gtest/gtest.h>
#include "../ExpandTemplate.h"

using namespace std;

TEST(ExpandTemplateTest, Valid)
{
    string const tpl = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";
    map<string, string> params;
    params["%USER_NAME%"] = "Ivan Petrov";
    params["{WEEK_DAY}"] = "Friday";
    ASSERT_TRUE(ExpandTemplate(tpl, params) == "Hello, Ivan Petrov. Today is Friday.");
}

TEST(ExpandTemplateTest, ChangeOfTemplate)
{
    string const tpl = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";
    map<string, string> params;
    params["%USER_NAME%"] = "Super %USER_NAME% {WEEK_DAY}";
    params["{WEEK_DAY}"] = "Friday. {WEEK_DAY}";
    ASSERT_TRUE(ExpandTemplate(tpl, params) ==
    "Hello, Super %USER_NAME% {WEEK_DAY}. Today is Friday. {WEEK_DAY}.");
}

TEST(ExpandTemplateTest, AABBBAABABABB)
{
    string const tpl = "-AABBCCCCCABC+";
    map<string, string> params;
    params["A"] = "[a]";
    params["AA"] = "[aa]";
    params["B"] = "[b]";
    params["BB"] = "[bb]";
    params["C"] = "[c]";
    params["CC"] = "[cc]";
    ASSERT_TRUE(ExpandTemplate(tpl, params) ==
    "-[aa][bb][cc][cc][c][a][b][c]+");
}

TEST(ExpandTemplateTest, CatMouse)
{
    string const tpl = "The quick brown fox jumps over the lazy dog.";
    map<string, string> params;
    params["fox"] = "cat";
    params["dog"] = "mouse";
    ASSERT_TRUE(ExpandTemplate(tpl, params) == "The quick brown cat jumps over the lazy mouse.");
}

TEST(ExpandTemplateTest, pi)
{
    string const tpl = "The value of pi is approximately 3.14159.";
    map<string, string> params;
    params["pi"] = "3.14";
    ASSERT_TRUE(ExpandTemplate(tpl, params) == "The value of 3.14 is approximately 3.14159.");
}

TEST(ExpandTemplateTest, FoxCatDog)
{
    string const tpl = "The quick brown fox jumps over the lazy dog.";
    map<string, string> params;
    params["fox"] = "cat";
    params["lazy dog"] = "sleepy cat";
    ASSERT_TRUE(ExpandTemplate(tpl, params) == "The quick brown cat jumps over the sleepy cat.");
}

TEST(ExpandTemplateTest, DogMouse)
{
    string const tpl = "The quick brown fox jumps over the lazy dog.";
    map<string, string> params;
    params["fox"] = "cat";
    params["dog"] = "mouse";
    params["lazy dog"] = "sleepy cat";
    ASSERT_TRUE(ExpandTemplate(tpl, params) == "The quick brown cat jumps over the sleepy cat.");
}

GTEST_API_ int main(int argc, char **argv)
{
    cout << "Running tests \n";
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
