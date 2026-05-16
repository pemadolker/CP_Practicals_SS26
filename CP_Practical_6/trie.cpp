// =============================================================================
// trie.cpp — Basic Trie: Insert, Search, Delete
// Course  : Data Structures & Algorithms
// Compile : g++ -std=c++17 trie.cpp -o trie
// Run     : ./trie
// =============================================================================
//
// A Trie is a tree where each path from the root to a terminal node spells
// out a stored string. Each node holds a map of child pointers (one per
// distinct character at that level) and an is_end_of_word flag.
//
// Time complexities (L = length of key):
//   Insert — O(L)
//   Search — O(L)
//   Delete — O(L)
// Space: O(total characters across all stored words)
// =============================================================================

#include <iostream>
#include <string>
#include <unordered_map>

// -----------------------------------------------------------------------------
// TrieNode
// -----------------------------------------------------------------------------
struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    bool is_end_of_word = false;
};

// -----------------------------------------------------------------------------
// Trie
// -----------------------------------------------------------------------------
class Trie {
public:
    Trie()  { root_ = new TrieNode(); }
    ~Trie() { destroy(root_); }

    // -------------------------------------------------------------------------
    // Insert
    // Walk character-by-character, creating child nodes on demand.
    // Set is_end_of_word = true on the final node.
    // Shared prefixes are stored only once: "app" and "apple" both use the
    // same first three nodes.
    // -------------------------------------------------------------------------
    void insert(const std::string& word) {
        TrieNode* current = root_;
        for (char ch : word) {
            if (current->children.find(ch) == current->children.end())
                current->children[ch] = new TrieNode();
            current = current->children[ch];
        }
        current->is_end_of_word = true;
        std::cout << "[Trie] Inserted: \"" << word << "\"\n";
    }

    // -------------------------------------------------------------------------
    // Search
    // Walk character-by-character. Return false immediately on any missing
    // child. After consuming all characters, check is_end_of_word to
    // distinguish a stored word from a mere prefix ("appl" vs "apple").
    // -------------------------------------------------------------------------
    bool search(const std::string& word) const {
        TrieNode* node  = get_node(word);
        bool      found = node && node->is_end_of_word;
        std::cout << "[Trie] Search \"" << word << "\": "
                  << (found ? "FOUND" : "NOT FOUND") << "\n";
        return found;
    }

    // -------------------------------------------------------------------------
    // Prefix query — bonus utility showing Trie's key advantage over a hash set
    // -------------------------------------------------------------------------
    bool starts_with(const std::string& prefix) const {
        bool found = get_node(prefix) != nullptr;
        std::cout << "[Trie] Prefix \"" << prefix << "\": "
                  << (found ? "EXISTS" : "NOT FOUND") << "\n";
        return found;
    }

    // -------------------------------------------------------------------------
    // Delete
    // Recursive post-order traversal:
    //   1. Walk to the target node.
    //   2. Clear is_end_of_word.
    //   3. On the way back up, prune any node that is now "useless"
    //      (no children AND not the end of another word).
    // This keeps the trie compact and avoids memory leaks.
    // -------------------------------------------------------------------------
    bool remove(const std::string& word) {
        auto [deleted, _prune] = remove_helper(root_, word, 0);
        (void)_prune;
        std::cout << "[Trie] Delete \"" << word << "\": "
                  << (deleted ? "DELETED" : "NOT FOUND") << "\n";
        return deleted;
    }

    // Print every stored word via depth-first traversal
    void print_all() const {
        std::string buffer;
        std::cout << "[Trie] Stored words: ";
        collect(root_, buffer);
        std::cout << "\n";
    }

private:
    TrieNode* root_;

    TrieNode* get_node(const std::string& key) const {
        TrieNode* current = root_;
        for (char ch : key) {
            auto it = current->children.find(ch);
            if (it == current->children.end()) return nullptr;
            current = it->second;
        }
        return current;
    }

    // Returns {was_deleted, should_prune_this_node}
    std::pair<bool, bool> remove_helper(TrieNode* node,
                                        const std::string& word,
                                        size_t depth) {
        if (!node) return {false, false};

        if (depth == word.size()) {
            if (!node->is_end_of_word) return {false, false};
            node->is_end_of_word = false;
            return {true, node->children.empty()};
        }

        char ch = word[depth];
        auto it = node->children.find(ch);
        if (it == node->children.end()) return {false, false};

        auto [deleted, prune_child] = remove_helper(it->second, word, depth + 1);

        if (prune_child) {
            delete it->second;
            node->children.erase(it);
        }

        bool can_prune_self = deleted
                              && node->children.empty()
                              && !node->is_end_of_word;
        return {deleted, can_prune_self};
    }

    void collect(TrieNode* node, std::string& buffer) const {
        if (node->is_end_of_word) std::cout << "\"" << buffer << "\" ";
        for (auto& [ch, child] : node->children) {
            buffer.push_back(ch);
            collect(child, buffer);
            buffer.pop_back();
        }
    }

    void destroy(TrieNode* node) {
        for (auto& [ch, child] : node->children) destroy(child);
        delete node;
    }
};

// =============================================================================
// main
// =============================================================================
int main() {
    std::cout << "=================================================\n";
    std::cout << "  Basic Trie — Insert / Search / Delete\n";
    std::cout << "=================================================\n";

    Trie trie;

    std::cout << "\n--- INSERT ---\n";
    trie.insert("apple");
    trie.insert("app");
    trie.insert("application");
    trie.insert("bat");
    trie.insert("ball");
    trie.insert("batman");
    trie.insert("cat");
    trie.print_all();

    std::cout << "\n--- SEARCH ---\n";
    trie.search("apple");        // FOUND
    trie.search("app");          // FOUND
    trie.search("appl");         // NOT FOUND (prefix only, no end marker)
    trie.search("bat");          // FOUND
    trie.search("zebra");        // NOT FOUND

    std::cout << "\n--- PREFIX QUERY ---\n";
    trie.starts_with("app");     // EXISTS
    trie.starts_with("ba");      // EXISTS
    trie.starts_with("dog");     // NOT FOUND

    std::cout << "\n--- DELETE ---\n";
    trie.remove("app");          // deleted — prefix node kept because "apple" exists
    trie.search("app");          // NOT FOUND
    trie.search("apple");        // still FOUND

    trie.remove("batman");       // deleted — "bat" node kept
    trie.search("batman");       // NOT FOUND
    trie.search("bat");          // still FOUND

    trie.remove("zebra");        // NOT FOUND (never inserted)
    trie.print_all();

    std::cout << "\n--- EDGE CASE: empty string ---\n";
    trie.insert("");
    trie.search("");
    trie.remove("");
    trie.search("");

    std::cout << "\n=================================================\n";
    std::cout << "  Done.\n";
    std::cout << "=================================================\n";
    return 0;
}