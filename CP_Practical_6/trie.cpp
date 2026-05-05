#include <iostream>
#include <vector>
#include <string>

struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {
        for (int i = 0; i < 26; i++) children[i] = nullptr;
    }
};

class Trie {
private:
    TrieNode* root;

    bool isEmpty(TrieNode* node) {
        for (int i = 0; i < 26; i++)
            if (node->children[i]) return false;
        return true;
    }

    TrieNode* remove(TrieNode* node, std::string word, int depth = 0) {
        if (!node) return nullptr;

        if (depth == word.size()) {
            if (node->isEndOfWord) node->isEndOfWord = false;
            if (isEmpty(node)) {
                delete node;
                node = nullptr;
            }
            return node;
        }

        int index = word[depth] - 'a';
        node->children[index] = remove(node->children[index], word, depth + 1);

        if (isEmpty(node) && !node->isEndOfWord) {
            delete node;
            node = nullptr;
        }
        return node;
    }

public:
    Trie() { root = new TrieNode(); }

    void insert(std::string key) {
        TrieNode* curr = root;
        for (char c : key) {
            int index = c - 'a';
            if (!curr->children[index]) curr->children[index] = new TrieNode();
            curr = curr->children[index];
        }
        curr->isEndOfWord = true;
    }

    bool search(std::string key) {
        TrieNode* curr = root;
        for (char c : key) {
            int index = c - 'a';
            if (!curr->children[index]) return false;
            curr = curr->children[index];
        }
        return (curr != nullptr && curr->isEndOfWord);
    }

    void remove(std::string key) {
        root = remove(root, key);
    }
};

int main() {
    Trie myTrie;
    myTrie.insert("hello");
    std::cout << "Search 'hello': " << (myTrie.search("hello") ? "Found" : "Not Found") << std::endl;
    myTrie.remove("hello");
    std::cout << "Search 'hello' after delete: " << (myTrie.search("hello") ? "Found" : "Not Found") << std::endl;
    return 0;
}