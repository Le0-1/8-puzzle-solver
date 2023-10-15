#ifndef BSI_H
#define BSI_H

#include "Puzzle.hpp"


#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <set>

const int LIMIT = 35;

/*Comparador personalizado para o set que representa a lista fechada. Fiz
isso pois vai me permitir procurar se um estado está presente no set mais rápido
em O(log N)
Referência: https://stackoverflow.com/questions/2620862/using-custom-stdset-comparator*/
auto closed_list_cmp = [](Puzzle* a, Puzzle* b) {
    int i = 0;
    while (a->m_CurrentState[i] == b->m_CurrentState[i]) i++;
    return a->m_CurrentState[i] < b->m_CurrentState[i];
};

class BSI {
    private:
        /*Função que implementa a busca em profundidade limitada.
        Ela é usada pela função IterativeDepeningSearch*/
        static Puzzle* DepthLimitedSearch(Puzzle* root, const int& limit);

        /**
         * @brief Verifica se um elemento já está presenta na lista aberta
         * @param open_list Fronteira ou lista aberta a qual eu estou procurando o elemento
         * @param node elemento que quero verificar se está na lista
        */
        static bool Contains(const std::list<Puzzle*>& open_list, Puzzle* node);

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

};  



#endif // !BSI_H