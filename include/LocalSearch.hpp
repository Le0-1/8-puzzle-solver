#ifndef LOCALSEARCH_H
#define LOCALSEARCH_H

#include "Puzzle.hpp"
#include "Utils.hpp"

class LocalSearch {
    public:
    //classe estática não vai precisar de contrutor
    LocalSearch() = delete;

    //Função para executar o HillClimbing
    static void HillClimbing(Puzzle* root, const bool& print);
};

#endif // !LOCALSEARCH_H