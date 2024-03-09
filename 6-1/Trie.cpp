//
// Created by Misha on 18.02.2024.
//

#include "Trie.h"

using namespace std;


void FindSuffLink(TrieNode* node)
{
    TrieNode* parent = node->parent;
    TrieNode* parentSuffLink = parent->suffLink;
    while (!parentSuffLink->HasChild(node->selfCh))
    {
        parentSuffLink = parentSuffLink->suffLink;
    }
    node->suffLink = parentSuffLink->children[node->selfCh];
}

void GetGLink(TrieNode* node)
{

    if (node->suffLink->templ != nullptr)
    {
        node->gLink = node->suffLink;
    }
    if (node->suffLink->gLink != nullptr)
    {
        node->gLink = node->suffLink->gLink;
    }
}

void GetUniqueChars(const string &line, vector<char>& uniqueSymbols) {
    for(char ch: line)
    {
        if (find(uniqueSymbols.begin(), uniqueSymbols.end(), ch) == uniqueSymbols.end())
        {
            uniqueSymbols.push_back(ch);
        }
    }
}

void Trie::AddStringsToTrie(const unordered_map<string, string> &params)
{
    for (const auto& param: params)
    {
        if (!param.first.empty())
        {
            AddStringToTrie(param.first, param.second);
        }
    }
}

void Trie::AddStringToTrie(const string& templ, const string& value)
{
    TrieNode* currNode = &m_trie;
    for (char c : templ)
    {                                                                       //done передавать два значения ато не пон first second
        if (currNode->children[c] == nullptr)
        {
            m_nodes.emplace_back();
            currNode->children[c] = &m_nodes.back();
        }
        currNode->children[c]->parent = currNode;
        currNode = currNode->children[c];
        currNode->selfCh = c;
    }
    currNode->templ = make_unique<string>(value);
}

// todo rename
void Trie::FillSuffLinkPrefix(TrieNode* node)
{
    TrieNode* selfNode = node;
    TrieNode* suffNode = node->suffLink;
    string result;

    while (selfNode != &m_trie)
    {
        if (selfNode->selfCh != suffNode->selfCh)
        {
            result.push_back(selfNode->selfCh);
        }
        else
        {
            suffNode = suffNode->parent;
        }
        selfNode = selfNode->parent;
    }
    std::reverse(result.begin(), result.end());
    node->suffLinkPrefix = result;
}

// todo rename
void Trie::FillAllSuffLinks()
{
    queue<TrieNode*> q;
    for (auto p: m_trie.children)
    {
        q.push(p.second);
    }
    while (!q.empty())
    {
        TrieNode* curr = q.front();
        q.pop();
        FindSuffLink(curr);
        FillSuffLinkPrefix(curr);
        GetGLink(curr);
        for (auto p: curr->children)
        {
            q.push(p.second);
        }
    }
}

bool TrieNode::HasChild(char c) const
{
    return this->children.contains(c);
}

string ExpandTemplate(const string& line, const unordered_map<string, string>& params)
{
    Trie tri(params);
    return tri.ExpandTemplate(line);
}

pair<const TrieNode*, int> LookAhead(const TrieNode* node, int i, const string& line)
{
    const TrieNode* tempNode = node;

    int j = i + 1;
    char c = line[j];
    while (tempNode->HasChild(c) and (j < line.length()))
    {
        tempNode = tempNode->children.at(c);
        if (tempNode->templ != nullptr)
        {
            node = tempNode;
            i = j;
        }
        j++;
        c = line[j];
    }
    return {node, i};
}

bool Trie::CheckRootAndChildCh(const TrieNode* currNode, char c) const {
    return currNode == &m_trie && !currNode->HasChild(c);
}

string Trie::ExpandTemplate(const string& line) const
{
    auto* currNode = &m_trie;
    string result;


    queue<char> processedChQ;

    for (int i = 0; i < line.size(); i++)
    {
        //todo сложно
        char c = line[i];
        //todo done отдельная функция
        followSuffLinks(c, currNode, result);

        if (CheckRootAndChildCh(currNode, c))
        {
            result += c;
            continue;
        }
        currNode = currNode->children.at(c);
        if (currNode->templ != nullptr)
        {
            auto [node, pos] = LookAhead(currNode, i, line);
            i = pos;
            result += *node->templ;
            currNode = &m_trie;
        }
        else if (currNode->gLink != nullptr)
        {
            auto [node, pos] = LookAhead(currNode->gLink, i, line);
            result += *node->templ;
            i = pos;
            currNode = &m_trie;
        }
    }
    return result;
}

//todo c заглавной буквы
//todo ссылка на конст указатель
//возвращать пару строка и нода выглядит сложно
void Trie::followSuffLinks(char c, const TrieNode *&currNode, string &result) const {
    // todo done передавать константно везде
    while (currNode != &m_trie && !currNode->HasChild(c))
    {
        result += currNode->suffLinkPrefix;
        currNode = currNode->suffLink;
    }
}

void Trie::InitRootParentChildren(const unordered_map<string, string> &params, TrieNode &rootParent)
{
    vector<char> uniqueSymbols{};

    for (const auto& p : params)
    {
        GetUniqueChars(p.first, uniqueSymbols);
    }
    for (char ch: uniqueSymbols)
    {
        rootParent.children[ch] = &m_trie;
    }
}


