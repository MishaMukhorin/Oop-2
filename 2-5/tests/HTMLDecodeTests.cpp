#include "../HTMLDecode.h"
#include <gtest/gtest.h>

using namespace std;

TEST (DecodeHTML_function, mt_str)
{
    EXPECT_EQ(DecodeHTML(""), "");
}

TEST (DecodeHTML_function, decodes_html)
{
    EXPECT_EQ(DecodeHTML("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s"),
              "Cat <says> \"Meow\". M&M's");
}

TEST (DecodeHTML_function, wrong_ending_entity)
{
    EXPECT_EQ(DecodeHTML("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&aposs"),
              "Cat <says> \"Meow\". M&M&aposs");
}

TEST (DecodeHTML_function, wrong_ending_entity_before_right)
{
    EXPECT_EQ(DecodeHTML("Cat &lt;says&gt; &quot;Meow&quot;. M&amp&apos;s"),
              "Cat <says> \"Meow\". M&amp's");
}

TEST (DecodeHTML_function, wrong_double_semicolon)
{
    EXPECT_EQ(DecodeHTML("Cat &lt;says&gt; &quot;Meow&quot;. M&amp &apos;;"),
              "Cat <says> \"Meow\". M&amp ';");
}

TEST (DecodeHTML_function, wrong_double_ending_entity)
{
    EXPECT_EQ(DecodeHTML("Cat &lt;says&gt; &quot;Meow&quot;. M&amp&aposs"),
              "Cat <says> \"Meow\". M&amp&aposs");
}

TEST (DecodeHTML_function, decode_semicolon)
{
    EXPECT_EQ(DecodeHTML(";"), ";");
}

TEST (DecodeHTML_function, decode_amp)
{
    EXPECT_EQ(DecodeHTML("&"), "&");
}


GTEST_API_ int main (int argc, char **argv)
{
    cout << "Running tests \n";
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
