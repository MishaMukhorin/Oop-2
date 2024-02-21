#include <codecvt>
#include "Dictionary.h"

// done using unorderedmap
void ReadDictionary(istream & dictFile, dictType& dictionary)
{
    string line;
    while (getline(dictFile, line))
    {
        size_t separatorIndex = line.find('=');
        if (separatorIndex == string::npos)
        {
            continue;
        }
        string word = line.substr(0, separatorIndex);
        string translation = line.substr(separatorIndex + 1);
        dictionary[word] = translation;
    }
}
//done ostream
void SaveDictionary(ostream& dictFile, const dictType& dictionary)
{
    for (const auto& pair : dictionary)
    {
        dictFile << pair.first << '=' << pair.second << endl;
    }
}

void GetTranslationForNewWord(const string& line, bool& changed, dictType& dictionary)
{
    cout << "Enter translation for " << line << ": ";
    string translation;
    getline(cin, translation);
    if (!translation.empty())
    {
        dictionary[line] = translation;
        dictionary[translation] = line;
        cout << "Added \"" << line.c_str() << "\" = \"" << translation.c_str() << "\" to dictionary" << endl;
        changed = true;
    }
}

bool ExitSaveDictionary(const string& dictFileName, const bool changed, const dictType& dictionary)
{
    if (changed)
    {
        cout << "Save changes to dictionary file \"" << dictFileName << "\"? (y/n): ";
        string response;
        getline(cin, response);
        if (response == "y")
        {
            ofstream dictFileOf(dictFileName);
            if (!dictFileOf)
            {
                cout << "Error: Could not open dictionary file " << dictFileName << " for writing" << endl;
                return false;
            }
            SaveDictionary(dictFileOf, dictionary);
            cout << "Dictionary saved" << endl;
        }
    }
    return true;
}

dictType ReadDictFromFile(const string &dictFileName)
{
    dictType dictionary;
    ifstream dictFileIf(dictFileName);
    if (dictFileIf.is_open())
    {
        if (!dictFileIf.eof())
        {
            ReadDictionary(dictFileIf, dictionary);
            dictFileIf.close();
        }
    }
    return dictionary;
}

// done ??????? main
bool ManageDictionary(const string& dictFileName) //done make bool
{
    std::locale::global(std::locale("")); // Set the global locale to the default system locale

    // Use cout to output narrow characters
    std::cout.imbue(std::locale()); // Set the output stream to use the global locale
    std::cout << "Hello, world!" << std::endl;

    string line;
    bool changed = false;
    dictType dictionary = ReadDictFromFile(dictFileName);
    cout << "Enter a word (or enter \"...\" to exit):" << endl;

    while (getline(cin, line))
    {
        if (line == "...")
        { //done break
            cout << "Exiting program" << endl;
            break;
        }
        if (!dictionary[line].empty())
        {
            cout << "russian words not working" << endl;
            cout << dictionary[line] << endl;
        } else
        { //done func getTranslForNewWord
            GetTranslationForNewWord(line, changed, dictionary);
        }
    }// done func ifsave and save
    return ExitSaveDictionary(dictFileName, changed, dictionary);
}










