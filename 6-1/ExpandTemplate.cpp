//
// Created by Misha on 19.02.2024.
//
#include "ExpandTemplate.h"

using namespace std;


void LookAhead(TrieNode*& node, int& i, const string& line, string& result)
{
    TrieNode* tempNode = node;
    string tempResult = result;

    int j = i + 1;
    char c = line[j];
    while (Trie::hasChild(tempNode, c) and (j < line.length()))
    {
        tempNode = tempNode->children[c];
        if (tempNode->terminal)
        {
            result = tempResult;
            node = tempNode;
            i = j;
        }
        j++;
        c = line[j];
    }
}

string ExpandTemplate(const string& line, const map<string, string>& params)
{
    Trie Tri(params);
    TrieNode *currNode = Tri.getRoot();
    string result;

    queue<char> processedChQ;

    for (int i = 0; i < line.size(); i++)
    {
        char c = line[i];
        while (!Trie::hasChild(currNode, c))
        {
            result += currNode->suffLinkPrefix;
            currNode = currNode->suffLink;
        }
        currNode = currNode->children[c];
        if (currNode == Tri.getRoot())
        {
            result += c;
        }
        if (currNode->terminal)
        {
            LookAhead(currNode, i, line, result);
            result += currNode->templ;
            currNode = Tri.getRoot();
        }
        else if (currNode->gLink != nullptr)
        {
            result += currNode->gLink->templ;
            currNode = Tri.getRoot();
        }
    }
    return result;
}
