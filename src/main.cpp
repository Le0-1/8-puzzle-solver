#include "Puzzle.hpp"
#include "BSI.hpp"

int main(int argc, const char** argv) {
    int teste0[PUZZLE_SIZE] = {1 ,2, 3, 4, 5, 6, 7, 8, 0};
    int teste1[PUZZLE_SIZE] = {1, 2, 3, 4, 5, 6, 7, 0, 8};
    int teste2[PUZZLE_SIZE] = {1, 2, 3, 4, 0, 5, 7, 8, 6};
    int teste3[PUZZLE_SIZE] = {1, 0, 3, 4, 2, 5, 7, 8, 6};
    int teste4[PUZZLE_SIZE] = {1, 5, 2, 4, 0, 3, 7, 8, 6};
    int teste5[PUZZLE_SIZE] = {1, 5, 2, 0, 4, 3, 7, 8, 6};
    int teste6[PUZZLE_SIZE] = {1, 5, 2, 4, 8, 3, 7, 6, 0};
    int teste7[PUZZLE_SIZE] = {1, 5, 2, 4, 8, 0, 7, 6, 3};
    int teste8[PUZZLE_SIZE] = {0, 5, 2, 1, 8, 3, 4, 7, 6};
    int teste9[PUZZLE_SIZE] = {1, 0, 2, 8, 5, 3, 4, 7, 6};
    int teste10[PUZZLE_SIZE] = {5, 8, 2, 1, 0, 3, 4, 7, 6};
    int teste11[PUZZLE_SIZE] = {5, 8, 2, 1, 7, 3, 4, 0, 6};
    int teste12[PUZZLE_SIZE] = {5, 8, 2, 1, 7, 3, 0, 4, 6};
    int teste13[PUZZLE_SIZE] = {5, 8, 2, 0, 7, 3, 1, 4, 6};
    int teste14[PUZZLE_SIZE] = {5, 8, 2, 7, 0, 3, 1, 4, 6};
    int teste15[PUZZLE_SIZE] = {8, 0, 2, 5, 7, 3, 1, 4, 6};
    int teste25[PUZZLE_SIZE] = {8, 4, 7, 5, 6, 0, 1, 3, 2};
    int teste26[PUZZLE_SIZE] = {0, 4, 7, 8, 6, 2, 5, 1, 3};
    int teste27[PUZZLE_SIZE] = {8, 0, 7, 5, 4, 6, 1, 3, 2};
    int teste28[PUZZLE_SIZE] = {8, 4, 7, 6, 2, 3, 5, 1, 0};
    int teste29[PUZZLE_SIZE] = {8, 0, 6, 5, 7, 3, 1, 2 ,4};
    int teste30[PUZZLE_SIZE] = {0, 8, 7, 5, 6 ,4, 1, 2, 3};
    int teste31[PUZZLE_SIZE] = {8, 6, 7, 2, 5, 4, 3, 0, 1};

    Puzzle* root = new Puzzle(teste30, Moves::NONE); // Crie um objeto raiz

    BSI::IterativeDepeningSearch(root);
    
    delete root;
    return 0;
}

