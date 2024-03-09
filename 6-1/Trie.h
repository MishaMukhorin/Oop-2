//
// Created by Misha on 18.02.2024.
//

#ifndef OOP_2_TRIE_H
#define OOP_2_TRIE_H

#include <algorithm>
#include "unordered_map"
#include "vector"
#include <string>
#include <cstring>
#include "queue"
#include "optional"
#include "deque"
#include "memory"


struct TrieNode {
    //todo ���������� �� ��������
    char selfCh{};
    TrieNode* parent{};
    TrieNode* suffLink{};
    std::string suffLinkPrefix;
    TrieNode* gLink{};
    std::unordered_map<char, TrieNode*> children; // done unique ������ - ������ ����� deque
    std::unique_ptr<std::string> templ{};    //done �������� ��� ��������������

    // todo done node.haschild
    bool HasChild(char c) const;

};
// done ������� ���� ������ ���� � dequeue

std::string ExpandTemplate(const std::string& line, const std::unordered_map<std::string, std::string>& params); //done  ��� ������

class Trie
{
public:
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;

    explicit Trie(const std::unordered_map<std::string, std::string> &params)
    {
        m_nodes.emplace_back();

        m_trie.parent = &m_nodes.back();
        TrieNode* rootParent = m_trie.parent;
        m_trie.suffLink = rootParent;

        InitRootParentChildren(params, *rootParent); // todo done ��������� ������ � �� ���������

        AddStringsToTrie(params); // �������� �� ������������ ������ � �� �� ����� ���������������������� ������� ������
        FillAllSuffLinks();
    }

   // done ��� ������ ���� �����������, ��� ������������� ���� ����� ������� ��������� �������,
   //
   std::string ExpandTemplate(const std::string& line) const; // done const ����� todo done
private:
                                                            // done ������� m � ��������������
    TrieNode m_trie;
                                                            //done ������� ���� �� �������� � �� �� unique_ptr
    std::deque<TrieNode> m_nodes;          // done unique ������
    void AddStringsToTrie(const std::unordered_map<std::string, std::string> &params);
    void AddStringToTrie(const std::string& templ, const std::string& value);
    void FillSuffLinkPrefix(TrieNode* node);
    void FillAllSuffLinks();
    bool CheckRootAndChildCh(const TrieNode* currNode, char c) const;

    void InitRootParentChildren(const std::unordered_map<std::string, std::string> &params, TrieNode &rootParent);

    void followSuffLinks(char c, const TrieNode *&currNode, std::string &result) const;
};


#endif //OOP_2_TRIE_H
