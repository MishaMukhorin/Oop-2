#include <gtest/gtest.h>
#include "../Trie.h"

using namespace std;

TEST(ExpandTemplateTest, Valid)
{
    string const tpl = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";
    
    unordered_map<string, string> params;
    params["%USER_NAME%"] = "Ivan Petrov";
    params["{WEEK_DAY}"] = "Friday";
    EXPECT_EQ(ExpandTemplate(tpl, params), "Hello, Ivan Petrov. Today is Friday.");
}

TEST(ExpandTemplateTest, ChangeOfTemplate)
{
    string const tpl = "Hello, %USER_NAME%. Today is {WEEK_DAY}.";
    
    unordered_map<string, string> params;
    params["%USER_NAME%"] = "Super %USER_NAME% {WEEK_DAY}";
    params["{WEEK_DAY}"] = "Friday. {WEEK_DAY}";
    EXPECT_EQ(ExpandTemplate(tpl, params),
    "Hello, Super %USER_NAME% {WEEK_DAY}. Today is Friday. {WEEK_DAY}.");
}

TEST(ExpandTemplateTest, AABBBAABABABB)
{
    string const tpl = "-AABBCCCCCABC+";
    unordered_map<string, string> params;
    params["A"] = "[a]";
    params["AA"] = "[aa]";
    params["B"] = "[b]";
    params["BB"] = "[bb]";
    params["C"] = "[c]";
    params["CC"] = "[cc]";
    EXPECT_EQ(ExpandTemplate(tpl, params),
    "-[aa][bb][cc][cc][c][a][b][c]+");
}

TEST(ExpandTemplateTest, BBXB)
{
    string const tpl = "bbxb";
    unordered_map<string, string> params;
    params["bbxk"] = "[o]";
    params["bx"] = "[z]";
    EXPECT_EQ(ExpandTemplate(tpl, params), "b[z]b");
}

TEST(ExpandTemplateTest, TestLookAhead)
{
    
    string const tpl = "-AAAAAAABBCCCCCABC+";
    
    unordered_map<string, string> params;
    params["A"] = "[a]";
    params["AA"] = "[aa]";
    params["AAA"] = "[aaa]";
    params["AAAA"] = "[aaaa]";
    params["AAAA"] = "[aaaa]";
    params["B"] = "[b]";
    params["BB"] = "[bb]";
    params["C"] = "[c]";
    params["CC"] = "[cc]";
    EXPECT_EQ(ExpandTemplate(tpl, params), "-[aaaa][aaa][bb][cc][cc][c][a][b][c]+");
}

TEST(ExpandTemplateTest, TestPosLookAhead)
{

    string const tpl = "-AAAAAAABBCCCCCABC+";

    unordered_map<string, string> params;
    params["A"] = "[a]";
    params["AA"] = "[aa]";
    params["AAAA"] = "[aaaa]";
    params["AAAAA"] = "[aaaaa]";
    params["B"] = "[b]";
    params["BB"] = "[bb]";
    params["C"] = "[c]";
    params["CC"] = "[cc]";
    EXPECT_EQ(ExpandTemplate(tpl, params), "-[aaaaa][aa][bb][cc][cc][c][a][b][c]+");
}

TEST(ExpandTemplateTest, TEstGLinkLook)
{

    string const tpl = "ababcde";

    unordered_map<string, string> params;
    params["ab"] = "x";
    params["abc"] = "y";
    params["bcde"] = "z";
    params["bc"] = "AA";
    EXPECT_EQ(ExpandTemplate(tpl, params), "xyde");
}


TEST(ExpandTemplateTest, CatMouse)
{
    string const tpl = "The quick brown fox jumps over the lazy dog.";
    
    unordered_map<string, string> params;
    params["fox"] = "cat";
    params["dog"] = "mouse";
    EXPECT_EQ(ExpandTemplate(tpl, params), "The quick brown cat jumps over the lazy mouse.");
}

TEST(ExpandTemplateTest, pi)
{
    string const tpl = "The value of pi is approximately 3.14159.";
    
    unordered_map<string, string> params;
    params["pi"] = "3.14";
    EXPECT_EQ(ExpandTemplate(tpl, params), "The value of 3.14 is approximately 3.14159.");
}

TEST(ExpandTemplateTest, FoxCatDog)
{
    string const tpl = "The quick brown fox jumps over the lazy dog.";
    
    unordered_map<string, string> params;
    params["fox"] = "cat";
    params["lazy dog"] = "sleepy cat";
    EXPECT_EQ(ExpandTemplate(tpl, params), "The quick brown cat jumps over the sleepy cat.");
}

TEST(ExpandTemplateTest, DogMouse)
{
    string const tpl = "The quick brown fox jumps over the lazy dog.";
    
    unordered_map<string, string> params;
    params["fox"] = "cat";
    params["dog"] = "mouse";
    params["lazy dog"] = "sleepy cat";
    EXPECT_EQ(ExpandTemplate(tpl, params), "The quick brown cat jumps over the sleepy cat.");
}

TEST(ExpandTemplateTest, test_suff_glink_lookahead)
{
    string const tpl = "-AAABBBCCCCCABC+";
    
    unordered_map<string, string> params;
    params["A"] = "[a]";
    params["AB"] = "[ab]";
    params["ABBB"] = "[abbb]";
    params["AABBC"] = "[aabbc]";
    params["B"] = "[b]";
    params["BB"] = "[bb]";
    params["C"] = "[c]";
    params["CC"] = "[cc]";
    EXPECT_EQ(ExpandTemplate(tpl, params), "-[a][a][abbb][cc][cc][c][ab][c]+");
}


TEST(ExpandTemplateTest, test_empty)
{
    string const tpl;
    
    unordered_map<string, string> params;
    params[""] = "A";
    EXPECT_EQ(ExpandTemplate(tpl, params), "");

}

GTEST_API_ int main(int argc, char **argv)
{
    cout << "Running tests \n";
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
