// =============================================================================
// patricia.cpp — PATRICIA Trie (Radix Tree / Compressed Trie)
// Course  : Data Structures & Algorithms
// Compile : g++ -std=c++17 patricia.cpp -o patricia
// Run     : ./patricia
// =============================================================================
//
// A standard Trie creates one node per character, producing long single-child
// chains wherever words share prefixes. PATRICIA compresses these chains:
// each EDGE stores a string label (the longest shared sequence), and a node
// only exists where a real BRANCH occurs.
//
// Example — storing "apple", "app", "application":
//
//   Standard Trie:  root-a-p-p[end]-l-e[end]
//                                  `-i-c-a-t-i-o-n[end]
//
//   PATRICIA:       root ──"app"──► [end]
//                                     ├──"le"──► [end]        ("apple")
//                                     └──"lication"──► [end]  ("application")
//
// The defining operation is EDGE SPLITTING: a new word that partially matches
// an existing edge causes that edge to split at the divergence point.
//
// Time complexities (L = length of key):
//   Insert — O(L)
//   Search — O(L)
//   Delete — O(L)
// Space: O(n * L) — far fewer nodes than a standard Trie
// =============================================================================

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

// -----------------------------------------------------------------------------
// RadixNode
// Each child edge is keyed by its first character (guaranteed unique per node).
// The value is a pair: {edge_label, child_node_pointer}.
// -----------------------------------------------------------------------------
struct RadixNode {
    std::unordered_map<char, std::pair<std::string, RadixNode*>> children;
    bool is_end = false;

    RadixNode() : is_end(false) {}
};

// -----------------------------------------------------------------------------
// PatriciaTrie
// -----------------------------------------------------------------------------
class PatriciaTrie {
public:
    PatriciaTrie()  { root_ = new RadixNode(); }
    ~PatriciaTrie() { destroy(root_); }

    // -------------------------------------------------------------------------
    // Insert
    // Three cases at each node:
    //   A) No edge starting with word[pos] → create a new leaf edge.
    //   B) Edge label fully consumed       → recurse into child node.
    //   C) Partial match                   → SPLIT the edge.
    //
    // Split example:
    //   Existing edge: "batman"
    //   New word:      "ball"
    //   Common prefix: "ba"  (2 characters)
    //
    //   Before: parent ──"batman"──► child
    //   After:  parent ──"ba"──► mid ──"tman"──► child   (old)
    //                                └──"ll"──► leaf     (new)
    // -------------------------------------------------------------------------
    void insert(const std::string& word) {
        if (search_helper(root_, word, 0)) {
            std::cout << "[PATRICIA] Insert \"" << word << "\": ALREADY EXISTS\n";
            return;
        }
        insert_helper(root_, word, 0);
        std::cout << "[PATRICIA] Inserted: \"" << word << "\"\n";
    }

    // -------------------------------------------------------------------------
    // Search
    // Follow edge labels, consuming the word segment by segment.
    // If an edge label does not fully match → NOT FOUND.
    // After all characters consumed → check is_end.
    // -------------------------------------------------------------------------
    bool search(const std::string& word) const {
        bool found = search_helper(root_, word, 0);
        std::cout << "[PATRICIA] Search \"" << word << "\": "
                  << (found ? "FOUND" : "NOT FOUND") << "\n";
        return found;
    }

    // -------------------------------------------------------------------------
    // Delete
    // 1. Walk to the node where the word ends and clear is_end.
    // 2. Prune: if that node is now a childless leaf, remove it.
    // 3. Merge: if its parent now has only one child and is not itself
    //    a word end, merge the two edges into one (reverse of splitting).
    // -------------------------------------------------------------------------
    bool remove(const std::string& word) {
        bool deleted = remove_helper(root_, word, 0);
        std::cout << "[PATRICIA] Delete \"" << word << "\": "
                  << (deleted ? "DELETED" : "NOT FOUND") << "\n";
        return deleted;
    }

    void print_all() const {
        std::string buf;
        std::cout << "[PATRICIA] Stored words: ";
        collect(root_, buf);
        std::cout << "\n";
    }

private:
    RadixNode* root_;

    // Number of characters edge_label and word[start..] share before diverging
    static int common_prefix_len(const std::string& edge_label,
                                  const std::string& word, int start) {
        int limit = std::min((int)edge_label.size(), (int)word.size() - start);
        int i = 0;
        while (i < limit && edge_label[i] == word[start + i]) i++;
        return i;
    }

    void insert_helper(RadixNode* node, const std::string& word, int pos) {
        if (pos == (int)word.size()) {
            node->is_end = true;
            return;
        }

        char first = word[pos];
        auto it    = node->children.find(first);

        if (it == node->children.end()) {
            // Case A: no matching edge — create a leaf with the full remaining word
            RadixNode* leaf = new RadixNode();
            leaf->is_end    = true;
            node->children[first] = { word.substr(pos), leaf };
            return;
        }

        std::string& label = it->second.first;
        RadixNode*&  child = it->second.second;
        int cp = common_prefix_len(label, word, pos);

        if (cp == (int)label.size()) {
            // Case B: edge label fully consumed — go deeper
            insert_helper(child, word, pos + cp);
        } else {
            // Case C: partial match — split the edge
            RadixNode* mid = new RadixNode();

            // Old child keeps the remaining part of the original label
            std::string old_suffix = label.substr(cp);
            mid->children[old_suffix[0]] = { old_suffix, child };

            // Current edge now only carries the shared prefix
            label = label.substr(0, cp);
            child = mid;

            // Attach the new word's remaining suffix
            int new_pos = pos + cp;
            if (new_pos == (int)word.size()) {
                mid->is_end = true;   // new word ends exactly at the split point
            } else {
                RadixNode* leaf  = new RadixNode();
                leaf->is_end     = true;
                std::string suf  = word.substr(new_pos);
                mid->children[suf[0]] = { suf, leaf };
            }
        }
    }

    bool search_helper(const RadixNode* node,
                        const std::string& word, int pos) const {
        if (pos == (int)word.size()) return node->is_end;

        char first = word[pos];
        auto it    = node->children.find(first);
        if (it == node->children.end()) return false;

        const std::string& label = it->second.first;
        const RadixNode*   child = it->second.second;
        int cp = common_prefix_len(label, word, pos);

        if (cp < (int)label.size()) return false; // label doesn't fully match
        return search_helper(child, word, pos + cp);
    }

    bool remove_helper(RadixNode* node, const std::string& word, int pos) {
        if (pos == (int)word.size()) {
            if (!node->is_end) return false;
            node->is_end = false;
            return true;
        }

        char first = word[pos];
        auto it    = node->children.find(first);
        if (it == node->children.end()) return false;

        std::string& label = it->second.first;
        RadixNode*&  child = it->second.second;
        int cp = common_prefix_len(label, word, pos);

        if (cp < (int)label.size()) return false;

        bool deleted = remove_helper(child, word, pos + cp);
        if (!deleted) return false;

        // Prune: child became a useless leaf
        if (child->children.empty() && !child->is_end) {
            delete child;
            node->children.erase(it);
        }
        // Merge: child has one grandchild and is not a word end
        else if (child->children.size() == 1 && !child->is_end) {
            auto& [grand_label, grandchild] = child->children.begin()->second;
            label = label + grand_label;     // join the two edge labels
            RadixNode* to_delete = child;
            child = grandchild;              // bypass the now-redundant node
            delete to_delete;
        }

        return true;
    }

    void collect(const RadixNode* node, std::string& buf) const {
        if (node->is_end) std::cout << "\"" << buf << "\" ";
        for (auto& [ch, edge] : node->children) {
            buf += edge.first;
            collect(edge.second, buf);
            buf.erase(buf.size() - edge.first.size());
        }
    }

    void destroy(RadixNode* node) {
        for (auto& [ch, edge] : node->children) destroy(edge.second);
        delete node;
    }
};

// =============================================================================
// main
// =============================================================================
int main() {
    std::cout << "=================================================\n";
    std::cout << "  PATRICIA Trie — Insert / Search / Delete\n";
    std::cout << "=================================================\n";

    PatriciaTrie pt;

    std::cout << "\n--- INSERT ---\n";
    pt.insert("apple");
    pt.insert("app");         // splits "apple" edge → "app"[end] + "le" branch
    pt.insert("application"); // splits further at "app" → "le" and "lication"
    pt.insert("bat");
    pt.insert("ball");        // splits "bat" edge → "ba" + "t" and "ll"
    pt.insert("batman");      // splits "bat" → "bat"[end] + "man"
    pt.insert("cat");
    pt.insert("car");         // splits "cat" → "ca" + "t" and "r"
    pt.print_all();

    std::cout << "\n--- SEARCH ---\n";
    pt.search("apple");       // FOUND
    pt.search("app");         // FOUND
    pt.search("bat");         // FOUND
    pt.search("ba");          // NOT FOUND (prefix only, no end marker)
    pt.search("dog");         // NOT FOUND

    std::cout << "\n--- DUPLICATE INSERT ---\n";
    pt.insert("apple");       // ALREADY EXISTS

    std::cout << "\n--- DELETE ---\n";
    pt.remove("app");         // deleted — "apple" and "application" still exist
    pt.search("app");         // NOT FOUND
    pt.search("apple");       // still FOUND

    pt.remove("batman");      // deleted — "bat" node kept
    pt.search("batman");      // NOT FOUND
    pt.search("bat");         // still FOUND

    pt.remove("nonexistent"); // NOT FOUND
    pt.print_all();

    std::cout << "\n=================================================\n";
    std::cout << "  Done.\n";
    std::cout << "=================================================\n";
    return 0;
}