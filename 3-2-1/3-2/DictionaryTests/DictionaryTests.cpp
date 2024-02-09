#include "../Dictionary.h"
#include <gtest/gtest.h>


TEST (SaveDictionary_function, saving_dictionary)
{
    ofstream inFile("dict_1.txt");
    dictType dict1;
    dict1["string"] = "строка";
    SaveDictionary(inFile, dict1);
    inFile.close();
    ifstream file("dict_1.txt");
    string str;
    getline(file, str);
    EXPECT_TRUE(str == "string=строка");
}
TEST (ReadDictionary_function, reading_dict)
{
    ofstream inFile("dict_2.txt");
    dictType dict1, dict2;

    dict2["string"] = "строка";
    inFile << "string=строка" << endl;
    inFile.close();
    ifstream file("dict_2.txt");
    ReadDictionary(file, dict1);
    EXPECT_TRUE(dict1 == dict2);
}

GTEST_API_ int main(int argc, char **argv)
{
    cout << "Running tests \n";
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

