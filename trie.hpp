#pragma once

#include <vector>
#include <string>
#include <iterator>
#include <iosfwd>

// Předpokládáme pouze základní ASCII znaky
static const size_t num_chars = 128;

struct trie_node {
    trie_node* children[num_chars] = {}; //!< pole ukazatelů na přímé následovníky daného uzlu
    trie_node* parent = nullptr;         //!< ukazatel na přímého předka daného uzlu
    char payload = 0;                    //!< znak, který tento uzel reprezentuje
    bool is_terminal = false;            //!< označuje, jestli v tomto uzlu končí slovo
    int counter = 1;
};

class trie
{
public:

    trie();
    ~trie();

    /**
     * Vloží řetězec do trie.
     * Vrátí true, pokud byl řetězec vložen (nebyl předtím v trii), jinak false.
     */
    bool insert(const std::string& str);

    /**
     * Vrátí všechny prvky trie, které začínají daným prefixem.
     *
     * Prefixy jsou inkluzivní, tj. search_by_prefix("abc") vrátí mezi výsledky
     * i "abc", pokud je "abc" v trii.
     */
    std::vector <std::pair<std::string, int> > search_by_prefix(const std::string& prefix) const;


private:
//! ukazatel na kořenový uzel stromu
trie_node* m_root = nullptr;

//! počet unikátních slov, které trie obsahuje
size_t m_size = 0;
};
