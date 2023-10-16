#ifndef BSI_H
#define BSI_H

#include "Puzzle.hpp"
#include "Hashtable.hpp"


#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <list>
#include <set>

const int LIMIT = 35;


//Classe que irá conter os algoritmos de BUSCA SEM INFORMAÇÃO (BSI).
class BSI {
    private:
        /*Função que implementa a busca em profundidade limitada.
        Ela é usada pela função IterativeDepeningSearch*/
        static Puzzle* DepthLimitedSearch(Puzzle* root, const int& limit);

        /**
         * @brief Verifica se um elemento já está presenta na lista aberta
         * @param open_list lista a qual eu estou procurando o elemento
         * @param node elemento que quero verificar se está na lista
         * @return Ponteiro para o elemento ou nullptr se não encontrar
        */
        static Puzzle* FindNodeInList(const std::list<Puzzle*>& list, Puzzle* node);

        //Parte do último nó até a raiz para mostrar a solução
        /**
         * @brief Função para alcançar a raiz a partir do nó que atingiu o objetivo.
         * @param node Nó que atingiu o objetivo.
        */
        static void TraceSolution(Puzzle* node);

    public:

        //Como a classe vai ser estática, ela não precisa de um construtor
        BSI() = delete;

        //Executa o algoritmo da Busca em Larguta
        static void BreadthFirstSearch(Puzzle* root);

        //Executa o algoritmo IDS com o auxílio da função DepthLimitedSearch
        static void IterativeDepeningSearch(Puzzle* root);

        //Executa o algoritmo de custo Uniforme ou o Dijkstra
        static void UniformCostSearch(Puzzle* root);

        friend class BCI;

};  



#endif // !BSI_H