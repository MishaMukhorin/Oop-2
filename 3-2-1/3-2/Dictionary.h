#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <cwchar>
#include <locale>
#include <cstdlib>

using namespace std;
using dictType = unordered_map<string, string>;


bool ManageDictionary(const string& dictFileName);
void ReadDictionary(istream& dictFile, dictType& dictionary);
void SaveDictionary(ostream& dictFile, const dictType& dictionary);
