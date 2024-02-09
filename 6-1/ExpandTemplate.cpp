#include "ExpandTemplate.h"
#include "algorithm"
#include "vector"
#include "cstring"
#include "iostream"

using namespace std;

const int K = 26;

//K - размер алфавита
struct BohrNode {
    int nextChild[K], keyNum, suffLink;     // keyNum — номер строки-образца, обозначаемого этой вершиной, suffLink - суффиксная ссылка
    bool success;
    int autoMove[K], parent;                   // autoMove - запоминание перехода автомата, par - вершина-отец в дереве
    char ch;                                // символ на ребре от par к этой вершине
    int suffGLink;                          // suffGLink - "хорошая" суф. ссылка
};


vector<BohrNode> bor;
vector<string> pattern;


BohrNode makeBorVrtx(int p,char c)
{
    BohrNode v{};
                             //(255)=(2^8-1)=(все единицы в каждом байте памяти)=(-1 в дополнительном коде целого 4-байтного числа int)
    memset(v.nextChild, 255, sizeof(v.nextChild));
    memset(v.autoMove, 255, sizeof(v.autoMove));
    v.parent=p;
    v.ch=c;
    v.suffLink = -1;
    v.suffGLink=-1;
    v.success=false;
    return v;
}

void addStringToBor(const string& s)
{
    int num = 0;                            //начинаем с корня
    for (char i : s)
    {
        int ch = i - 'a';               //получаем номер в алфавите
        if (bor[num].nextChild[ch] == -1)  //-1 - признак отсутствия ребра
        {
            bor.push_back(makeBorVrtx(num, i));
            bor[num].nextChild[ch] = bor.size() - 1;
        }
        num=bor[num].nextChild[ch];
    }
    bor[num].success = true;
    pattern.push_back(s);
    bor[num].keyNum = pattern.size() - 1;
}

bool isStringInBor(const string& s)
{
    int num = 0;
    for (char i : s)
    {
        char ch = i - 'a';
        if (bor[num].nextChild[ch] == -1)
        {
            return false;
        }
        num = bor[num].nextChild[ch];
    }
    return bor[num].success;
}

int getAutoMove(int v, char ch);

int getSuffLink(const int v)
{
    if (bor[v].suffLink == -1)             //если еще не считали
    {
        if ((v == 0) || (bor[v].parent == 0)) //если v - корень или предок v - корень
            bor[v].suffLink = 0;
        else
            bor[v].suffLink = getAutoMove(getSuffLink(bor[v].parent), bor[v].ch);
    }
    return bor[v].suffLink;
}

int getAutoMove(int v, char ch)
{
    if (bor[v].autoMove[ch] == -1)
    {
        if (bor[v].nextChild[ch] != -1)
            bor[v].autoMove[ch] = bor[v].nextChild[ch];
        else if (v == 0)
            bor[v].autoMove[ch] = 0;
        else
            bor[v].autoMove[ch] = getAutoMove(getSuffLink(v), ch);
    }
    return bor[v].autoMove[ch];
}

int getSuffGLink(const int v)
{
    if (bor[v].suffGLink == -1)
    {
        int suffLink = getSuffLink(v);
        if (suffLink == 0)                  //либо v - корень, либо суф. ссылка v указывает на корень
            bor[v].suffGLink = 0;
        else
            bor[v].suffGLink = (bor[suffLink].success)? suffLink: getSuffGLink(suffLink);
    }
    return bor[v].suffGLink;
}

pair<string, int> check(const int v, const int i){
    for (int u = v; u != 0; u = getSuffGLink(u)){
        if (bor[u].success)
            return make_pair(pattern[bor[u].keyNum], i-pattern[bor[u].keyNum].length()+1);
    }
    return make_pair("", 0);
}




                                        //    template           key          value
std::string ExpandTemplate(std::string const& tpl, std::map<std::string, std::string> const& params) {
    bor.push_back(makeBorVrtx(0, 0));
    map<string, string> parameters;

    for (auto const& [key, value] : params) {
        if (!key.empty()) {
            addStringToBor(key);
        }
        if (!key.empty()) {
            parameters[key] = value;
        }
    }
    std::string result;

    int autoMove = 0;
    for (int i = 0; i < tpl.length(); i++){
        autoMove = getAutoMove(autoMove, tpl[i] - 'a');
        pair<string, int> checkBor = check(autoMove, i + 1);
        if (checkBor.second > 0) {
            result.replace(checkBor.second - 1, result.length() - checkBor.second + 1, "");
            result += parameters[checkBor.first];
            cout << result << " " << checkBor.second << endl;
        }
        else
            result += tpl[i];
    }

    return result;
}
