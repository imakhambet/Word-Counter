#include <algorithm>
#include <stack>
#include <iostream>
#include <map>
#include "trie.hpp"

using namespace std;
trie::trie() {
    m_root = new trie_node();
    m_size = 0;
}

void delTrie(trie_node *&node) {
    for (auto &i : node->children) {
        if (i != nullptr) {
            trie_node *nodeCh = i;
            delTrie(nodeCh);
            delete nodeCh;
        }
    }
}

trie::~trie() {
    trie_node *root = m_root;
    if (root != nullptr) {
        delTrie(root);
        delete root;
        m_root = nullptr;
    }
    m_size = 0;
}


bool trie::insert(const std::string &str) {

    trie_node* node = m_root;
    bool unique = false;
    for (char c : str) {
        if (!node->children[(int) c]) {
            auto* new_node = new trie_node();
            trie_node** children = new_node->children;
            for (size_t i = 0; i < num_chars; i++) {
                children[i] = nullptr;
            }
            new_node->payload = c;
            node->children[(int) c] = new_node;
            new_node->parent = node;
            node = new_node;
        } else {
            node = node->children[(int) c];
        }
    }

    if (!node->is_terminal) {
        unique = true;
        node->is_terminal = true;
    }

    if (unique) {
        m_size++;
    }else{
        node->counter++;
    }

    return unique;
}

vector <pair<string, int> > trie::search_by_prefix(const std::string &prefix) const {
    trie_node *node = m_root;

    if (m_root == nullptr) {
        return vector <pair<string, int> > ();
    } else {
        vector <pair<string, int> > str;
        for (auto &c : prefix) {
            if (node->children[c]) {
                node = node->children[c];
            } else {
                return vector <pair<string, int> > ();
            }
        }

        if (node->is_terminal) {
            str.push_back(make_pair(prefix, node->counter));
        }

        for (auto & i : node->children) {
            if (i != nullptr) {
                vector <pair<string, int> > vec = search_by_prefix(prefix + i->payload);
                for (const auto& elem : vec) {
                    str.push_back(elem);
                }
            }
        }
        return str;
    }
}

