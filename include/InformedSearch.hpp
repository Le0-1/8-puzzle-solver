#ifndef INFORMEDSEARCH_H
#define INFORMEDSEARCH_H

#include "Puzzle.hpp"
#include "Utils.hpp" //Vou usa essa classe apenas para usar as funções auxiliares

//Permite até esse número de movimentos laterais
const int HILL_CLIMBING_LIMIT = 20000;

//Erro permitido para explorar estados piores no HillClimbing
const int ERRO = 1;


//Classe para representar a BUSCA COM INFORMAÇÃO
class InformedSearch {
    public:
        //Classe estática não vai precisar de destrutor
        InformedSearch() = delete;

        /*Função para executar o algoritmo A. 
        G(n) = depth e H(n) = distância de manhattan*/
        static void AStar(Puzzle* root, const bool& print); 

        /*Busca gulosa Greedy best-first search
        f(n) = "misplaced tiles". Não usei a Hashtable nessa função pois ela
        não apresentou melhora depois de usar.*/
        static void GreedySearch(Puzzle* root, const bool& print);
};  

#endif // !INFORMEDSEARCH_H