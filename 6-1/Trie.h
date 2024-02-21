//
// Created by Misha on 18.02.2024.
//

#ifndef OOP_2_TRIE_H
#define OOP_2_TRIE_H
#include "map"
#include "vector"
#include "string"
#include "queue"

struct TrieNode {
    bool terminal = false;
    char selfCh{};
    TrieNode* parent{};
    TrieNode* suffLink{};
    std::string suffLinkPrefix;
    TrieNode* gLink{};
    std::map<char, TrieNode*> children;
    std::string templ;
};

class Trie
{
public:

    explicit Trie(const std::map<std::string, std::string>& params)
    {
        trie.parent = new TrieNode;
        TrieNode* temp = trie.parent;
        trie.suffLink = temp;
        for (char c = 32; c <= 126; c++)
        {
            temp->children[c] = &trie;
        }
        addStringsToTrie(params);
        findAllSuffLinks();
        findAllGLinks();
    }

    [[maybe_unused]] static bool isInitialized(const std::map<char, TrieNode*>& myMap, char c);
    [[maybe_unused]] TrieNode* getRoot();
    [[maybe_unused]] static bool hasChild(TrieNode* node, char c);

private:
    TrieNode trie;
    void addStringsToTrie(const std::map<std::string, std::string>& params);
    void addStringToTrie(const std::pair<std::string, std::string>& param);
    void findSuffLinkPrefix(TrieNode* node);
    static void findSuffLink(TrieNode* node);
    void findAllSuffLinks();
    static void checkGLink(TrieNode* node);
    void findAllGLinks();

};


#endif //OOP_2_TRIE_H
