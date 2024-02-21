//
// Created by Misha on 18.02.2024.
//

#include "Trie.h"

using namespace std;


void Trie::addStringsToTrie(const map<string, string>& params)
{
    for (const auto& param: params)
    {
        if (!param.first.empty())
        {
            addStringToTrie(param);
        }
    }
}

void Trie::addStringToTrie(const pair<string, string>& param)
{
    TrieNode* currNode = &trie;
    for (char c : param.first)
    {
        if (currNode->children[c] == nullptr)
        {
            currNode->children[c] = new TrieNode;
        }
        currNode->children[c]->parent = currNode;
        currNode = currNode->children[c];
        currNode->selfCh = c;
    }
    currNode->templ = param.second;
    currNode->terminal = true;
}

void Trie::findSuffLinkPrefix(TrieNode* node)
{
    TrieNode* selfNode = node;
    TrieNode* suffNode = node->suffLink;
    string result;

    while (selfNode != &trie)
    {
        if (selfNode->selfCh != suffNode->selfCh)
        {
            result.insert(result.cbegin(), selfNode->selfCh);
        }
        else
        {
            suffNode = suffNode->parent;
        }
        selfNode = selfNode->parent;
    }
    node->suffLinkPrefix = result;
}

bool Trie::isInitialized(const std::map<char, TrieNode*>& myMap, char c) {
    return myMap.find(c) != myMap.end();
}


void Trie::findSuffLink(TrieNode* node)
{
    TrieNode* parent = node->parent;
    TrieNode* parentSuffLink = parent->suffLink;
    while (!hasChild(parentSuffLink, node->selfCh))
    {
        parentSuffLink = parentSuffLink->suffLink;
    }
    node->suffLink = parentSuffLink->children[node->selfCh];
}

void Trie::findAllSuffLinks()
{
    queue<TrieNode*> q;
    for (auto p: trie.children)
    {
        q.push(p.second);
    }
    while (!q.empty())
    {
        TrieNode* curr = q.front();
        q.pop();
        findSuffLink(curr);
        findSuffLinkPrefix(curr);

        for (auto p: curr->children)
        {
            q.push(p.second);
        }
    }
}

void Trie::checkGLink(TrieNode* node)
{

    if (node->suffLink->terminal)
    {
        node->gLink = node->suffLink;
    }
    if (node->suffLink->gLink != nullptr)
    {
        node->gLink = node->suffLink->gLink;
    }
}

void Trie::findAllGLinks()
{
    queue<TrieNode*> q;
    for (auto p: trie.children)
    {
        q.push(p.second);
    }
    while (!q.empty())
    {
        TrieNode* curr = q.front();
        q.pop();
        checkGLink(curr);
        for (auto p: curr->children)
        {
            q.push(p.second);
        }
    }
}

[[maybe_unused]] TrieNode *Trie::getRoot()
{
    return &trie;
}

bool Trie::hasChild(TrieNode* node, char c)
{
    return isInitialized(node->children, c);
}
