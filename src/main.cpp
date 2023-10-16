#include "Puzzle.hpp"
#include "BSI.hpp"
#include "BCI.hpp"
#include "Hashtable.hpp"


#include <unordered_set>
#include <vector>
#include <algorithm>

std::size_t CalculateUniqueKey(const std::vector<int>& state) {
    std::size_t hashValue = state[0];

    // Iterate through the state of the puzzle and calculate the hash.
    for (int i = 0; i < PUZZLE_SIZE; ++i) {
        hashValue = hashValue * 9 + state[i];
    }
    return hashValue;
}

bool AreAllStatesUnique() {
    std::unordered_set<std::size_t> uniqueKeysSet;
    std::vector<int> puzzleState(9);

    for (int i = 0; i < 9; ++i) {
        puzzleState[i] = i;
    }

    do {
        // Create a unique key for the current state and insert it into the set.
        std::size_t key = CalculateUniqueKey(puzzleState);
        if (uniqueKeysSet.find(key) != uniqueKeysSet.end()) {
            // Found a duplicate key, so not all states are unique.
            return false;
        }
        uniqueKeysSet.insert(key);
    } while (std::next_permutation(puzzleState.begin(), puzzleState.end()));

    // All possible states have unique keys.
    return true;
}



int main(int argc, const char** argv) {
    std::vector<int> teste0 = {1 ,2, 3, 4, 5, 6, 7, 8, 0};
    std::vector<int> teste1 = {1, 2, 3, 4, 5, 6, 7, 0, 8};
    std::vector<int> teste2 = {1, 2, 3, 4, 0, 5, 7, 8, 6};
    std::vector<int> teste3 = {1, 0, 3, 4, 2, 5, 7, 8, 6};
    std::vector<int> teste4 = {1, 5, 2, 4, 0, 3, 7, 8, 6};
    std::vector<int> teste5 = {1, 5, 2, 0, 4, 3, 7, 8, 6};
    std::vector<int> teste6 = {1, 5, 2, 4, 8, 3, 7, 6, 0};
    std::vector<int> teste7 = {1, 5, 2, 4, 8, 0, 7, 6, 3};
    std::vector<int> teste8 = {0, 5, 2, 1, 8, 3, 4, 7, 6};
    std::vector<int> teste9 = {1, 0, 2, 8, 5, 3, 4, 7, 6};
    std::vector<int> teste10 = {5, 8, 2, 1, 0, 3, 4, 7, 6};
    std::vector<int> teste11 = {5, 8, 2, 1, 7, 3, 4, 0, 6};
    std::vector<int> teste12 = {5, 8, 2, 1, 7, 3, 0, 4, 6};
    std::vector<int> teste13 = {5, 8, 2, 0, 7, 3, 1, 4, 6};
    std::vector<int> teste14 = {5, 8, 2, 7, 0, 3, 1, 4, 6};
    std::vector<int> teste15 = {8, 0, 2, 5, 7, 3, 1, 4, 6};
    std::vector<int> teste20 = {8, 7, 0, 5, 4, 2, 1, 6, 3};
    std::vector<int> teste25 = {8, 4, 7, 5, 6, 0, 1, 3, 2};
    std::vector<int> teste26 = {0, 4, 7, 8, 6, 2, 5, 1, 3};
    std::vector<int> teste27 = {8, 0, 7, 5, 4, 6, 1, 3, 2};
    std::vector<int> teste28 = {8, 4, 7, 6, 2, 3, 5, 1, 0};
    std::vector<int> teste29 = {8, 0, 6, 5, 7, 3, 1, 2 ,4};
    std::vector<int> teste30 = {0, 8, 7, 5, 6 ,4, 1, 2, 3};
    std::vector<int> teste31 = {8, 6, 7, 2, 5, 4, 3, 0, 1};

    std::vector<std::vector<int>> testes;
    testes.push_back(teste0);
    testes.push_back(teste1);
    testes.push_back(teste2);
    testes.push_back(teste3);
    testes.push_back(teste4);
    testes.push_back(teste5);
    testes.push_back(teste6);
    testes.push_back(teste7);
    testes.push_back(teste8);
    testes.push_back(teste9);
    testes.push_back(teste10);
    testes.push_back(teste11);
    testes.push_back(teste12);
    testes.push_back(teste13);
    testes.push_back(teste14);
    testes.push_back(teste15);
    testes.push_back(teste20);
    testes.push_back(teste25);
    testes.push_back(teste26);
    testes.push_back(teste27);
    testes.push_back(teste28);
    testes.push_back(teste29);
    testes.push_back(teste30);
    testes.push_back(teste31);


    //std::cout << AreAllStatesUnique();

    Puzzle* root = new Puzzle(teste20, Moves::NONE);
    BCI::HillClimbing(root);
    delete root;
    
    
    return 0;
}

