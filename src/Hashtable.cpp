#include "Hashtable.hpp"

Hashtable::Hashtable() { 
    for (int i = 0; i < TABLE_SIZE; i++) {
        std::list<Puzzle*> list;
        this->m_Table.push_back(list);
    }
};

std::size_t Hashtable::Hash(Puzzle* node) {
    std::size_t index = node->m_CurrentState[0];

    // Iterate through the state of the puzzle and calculate the hash.
    for (int i = 0; i < PUZZLE_SIZE; ++i) {
        index = index * HASH_NUMBER + node->m_CurrentState[i];
    }
    return index % TABLE_SIZE;
}

void Hashtable::Insert(Puzzle* node) {
    std::size_t index = Hash(node);
    this->m_Table[index].push_back(node);
}

Puzzle* Hashtable::Find(Puzzle* node) {
    std::size_t index = Hash(node);
    for (Puzzle* ptr : this->m_Table[index]) {
        if (ptr->isSameState(node)) return ptr;
    }
    return nullptr;
}