#include <queue>
#include "ExpandTemplate.h"
#include "algorithm"
#include "vector"
#include "cstring"
#include "iostream"

using namespace std;

const int K = 26;

//K - размер алфавита
struct BohrNode {
    int nextChild[K];
    int keyNum;
    int suffLink;     // keyNum — номер строки-образца, обозначаемого этой вершиной, suffLink - суффиксная ссылка
    int parent;                   // autoMove - запоминание перехода автомата, par - вершина-отец в дереве
    int depth;
    bool success;
    char ch;                                // символ на ребре от parent к этой вершине
};


vector<BohrNode> bor;


BohrNode makeBorVrtx(int p,char c)
{
    BohrNode v{};
                             //(255)=(2^8-1)=(все единицы в каждом байте памяти)=(-1 в дополнительном коде целого 4-байтного числа int)
    memset(v.nextChild, -1, sizeof(v.nextChild));
    v.parent=p;
    v.depth = 0;
    v.ch=c;
    v.suffLink = -1;
    v.success=false;
    return v;
}

void addStringToBor(const string& s, const int& n)
{
    int num = 0;                            //начинаем с корня
    for (int i = 0; i < s.length(); i++)
    {
        int ch = s[i] - 'a';               //получаем номер в алфавите

        if (bor[num].nextChild[ch] == -1)  //-1 - признак отсутствия ребра
        {
            bor.push_back(makeBorVrtx(num, s[i]));
            bor[num].nextChild[ch] = bor.size() - 1;
            bor[num].depth = i;
        }
        num=bor[num].nextChild[ch];
    }
    bor[num].success = true;
    bor[num].keyNum = n;
}

bool isStringInBor(const string& s)
{
    int num = 0;
    for (char i : s)
    {
        int ch = i - 'a';
        if (bor[num].nextChild[ch] == -1)
            return false;
        num = bor[num].nextChild[ch];
    }
    return bor[num].success;
}

void getSuffLink(const int v)
{
    if (bor[v].suffLink == -1)             //если еще не считали
    {
        if ((v == 0) || (bor[v].parent == 0)) //если v - корень или предок v - корень
            bor[v].suffLink = 0;
        else{
            int suffLink = -1, i = v;

            while (suffLink == -1 ) {
                suffLink = bor[bor[bor[i].parent].suffLink].nextChild[bor[v].ch - 'a'];
                i = bor[i].parent;
            }
            bor[v].suffLink = suffLink;
        }
    }
}

void getAllSuffLinks(int root)
{
    queue<int> q;
    q.push(root);
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        getSuffLink(curr);
        for (int i : bor[curr].nextChild)
        {
            if (i != -1)
                q.push(i);
        }
    }
}

void clearQueue(queue<char> &q, string &result) {
    while (!q.empty()) {
        result += q.front();
        q.pop();
    }
}

void checkSuccess(int i, queue<char> &q, string &result, const vector<string> &values) {
    if (bor[i].success)
    {
        clearQueue(q, result);
        result += values[bor[i].keyNum];
    }
}

std::string expand(const string& tpl, map<string, string> const& params)
{
    bor.push_back(makeBorVrtx(0, '`'));
    int i = 0;
    queue<char> q;
    string result;

    vector<string> values;
    for (auto & [key, value] : params) {
        if (!key.empty()) {
            addStringToBor(key, i);
            values.push_back(value);
            ++i;
        }
    }
    cout << "Em" << endl;
    getAllSuffLinks(0);

    i = 0;
    for (char c: tpl)
    {
        while (bor[i].nextChild[c - 'a'] == -1 and i > 0)
        {
            i = bor[i].suffLink;
            int k = bor[i].depth - bor[bor[i].suffLink].depth;
            for (int j = 0; j < k; ++j) {
                result += q.front();
                q.pop();
            }
            cout << "em " << c << endl;
            checkSuccess(i, q, result, values);
        }
        if (bor[i].nextChild[c - 'a'] != -1){
            i = bor[i].nextChild[c - 'a'];
            q.push(c);
            checkSuccess(i, q, result, values);
        } else
        {
            clearQueue(q, result);
            result += c;
        }

    }
    return result;
}

int main() {

    map<string, string> params;
    params["aab"] = "TTTT";
    params["ab"] = "RRRR";
    params["bba"] = "SSSS";

    string tpl = "aabbababbaaasandkml";


    string result = expand(tpl, params);
    tpl = "TTTTbRRRRaSSSSaasandkml";

    if (result == tpl) cout << "SUCCESS" << endl; else cout << result << endl;
    cout << result << endl;
    return 0;
}


                                        //    template           key          value
//std::string EexpandTemplate(std::string const& tpl, std::map<std::string, std::string> const& params) {
//    bor.push_back(makeBorVrtx(0, 0));
//    map<string, string> parameters;
//
//    for (auto const& [key, value] : params) {
//        if (!key.empty()) {
//            addStringToBor(key);
//        }
//        if (!key.empty()) {
//            parameters[key] = value;
//        }
//    }
//    std::string result;
//
//    int autoMove = 0;
//    for (int i = 0; i < tpl.length(); i++){
//        autoMove = getAutoMove(autoMove, tpl[i] - 'a');
//        pair<string, int> checkBor = check(autoMove, i + 1);
//        if (checkBor.second > 0) {
//            result.replace(checkBor.second - 1, result.length() - checkBor.second + 1, "");
//            result += parameters[checkBor.first];
//            cout << result << " " << checkBor.second << endl;
//        }
//        else
//            result += tpl[i];
//    }
//
//    return result;
//}
