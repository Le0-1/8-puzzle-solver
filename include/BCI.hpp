#ifndef BCI_H
#define BCI_H

#include "Puzzle.hpp"
#include "BSI.hpp" //Vou usa essa classe apenas para usar as funções auxiliares

#include <set>
#include <list>

//Permite até 1000 movimentos laterais
const int HILL_CLIMBING_LIMIT = 20000;

//Erro permitido para explorar estados piores no HillClimbing
const int ERRO = 1;
//Classe para representar a BUSCA COM INFORMAÇÃO
class BCI {
    public:
        //Classe estática não vai precisar de destrutor
        BCI() = delete;

        /*Função para executar o algoritmo A. 
        G(n) = depth e H(n) = distância de manhattan*/
        static void AStar(Puzzle* root); 

        /*Busca gulosa Greedy best-first search*/
        static void GreedySearch(Puzzle* root);

        //Função para executar o HillClimbing com 
        static void HillClimbing(Puzzle* root);

};  



#endif // !BCI_H