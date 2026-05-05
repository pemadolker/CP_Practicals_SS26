#include <iostream>
#include <map>
using namespace std;

class PatriciaNode {
public:
    string label;
    bool isEnd;
    map<char, PatriciaNode*> children;

    PatriciaNode(string lbl = "") {
        label = lbl;
        isEnd = false;
    }
};

class PatriciaTrie {
private:
    PatriciaNode* root;

public:
    PatriciaTrie() {
        root = new PatriciaNode();
    }

    void insert(string word) {
        PatriciaNode* curr = root;

        while (true) {
            bool found = false;

            for (auto& child : curr->children) {
                string lbl = child.second->label;

                int i = 0;
                while (i < lbl.size() && i < word.size() && lbl[i] == word[i])
                    i++;

                if (i > 0) {
                    if (i == lbl.size()) {
                        curr = child.second;
                        word = word.substr(i);
                        found = true;
                        break;
                    } else {
                        // split node
                        PatriciaNode* split = new PatriciaNode(lbl.substr(0, i));
                        child.second->label = lbl.substr(i);

                        split->children[child.second->label[0]] = child.second;
                        curr->children[lbl[0]] = split;

                        if (i < word.size()) {
                            PatriciaNode* newNode = new PatriciaNode(word.substr(i));
                            newNode->isEnd = true;
                            split->children[word[i]] = newNode;
                        } else {
                            split->isEnd = true;
                        }

                        return;
                    }
                }
            }

            if (!found) {
                PatriciaNode* newNode = new PatriciaNode(word);
                newNode->isEnd = true;
                curr->children[word[0]] = newNode;
                return;
            }
        }
    }

    bool search(string word) {
        PatriciaNode* curr = root;

        while (true) {
            bool found = false;

            for (auto& child : curr->children) {
                string lbl = child.second->label;

                if (word.substr(0, lbl.size()) == lbl) {
                    word = word.substr(lbl.size());
                    curr = child.second;

                    if (word.empty())
                        return curr->isEnd;

                    found = true;
                    break;
                }
            }

            if (!found) return false;
        }
    }
};


int main() {
    PatriciaTrie trie;

    trie.insert("cat");
    trie.insert("car");

    cout << "Search cat: " << (trie.search("cat") ? "Found" : "Not Found") << endl;
    cout << "Search car: " << (trie.search("car") ? "Found" : "Not Found") << endl;
    cout << "Search cap: " << (trie.search("cap") ? "Found" : "Not Found") << endl;

    return 0;
}