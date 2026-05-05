#include <iostream>
#include <unordered_map>
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
    }
};

class Trie {
private:
    TrieNode* root;

    bool isEmpty(TrieNode* node) {
        return node->children.empty();
    }

    TrieNode* deleteHelper(TrieNode* node, const string& key, int depth) {
        if (!node) return nullptr;

        if (depth == key.size()) {
            if (node->isEndOfWord)
                node->isEndOfWord = false;

            if (isEmpty(node)) {
                delete node;
                node = nullptr;
            }
            return node;
        }

        char ch = key[depth];
        node->children[ch] = deleteHelper(node->children[ch], key, depth + 1);

        if (isEmpty(node) && !node->isEndOfWord) {
            delete node;
            node = nullptr;
        }

        return node;
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& key) {
        TrieNode* curr = root;
        for (char ch : key) {
            if (!curr->children[ch])
                curr->children[ch] = new TrieNode();
            curr = curr->children[ch];
        }
        curr->isEndOfWord = true;
    }

    bool search(const string& key) {
        TrieNode* curr = root;
        for (char ch : key) {
            if (!curr->children[ch])
                return false;
            curr = curr->children[ch];
        }
        return curr->isEndOfWord;
    }

    void remove(const string& key) {
        root = deleteHelper(root, key, 0);
    }
};

// Test
int main() {
    Trie trie;

    trie.insert("cat");
    trie.insert("car");

    cout << "Search cat: " << trie.search("cat") << endl;
    cout << "Search car: " << trie.search("car") << endl;

    trie.remove("cat");

    cout << "Search cat after delete: " << trie.search("cat") << endl;

    return 0;
}