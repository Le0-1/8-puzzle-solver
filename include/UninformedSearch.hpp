#ifndef UNINFORMEDSEARCH_H
#define UNINFORMEDSEARCH_H

#include "Puzzle.hpp"
#include "Hashtable.hpp"
#include "Utils.hpp"


#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <list>
#include <set>

const int LIMIT = 35;


//Classe que irá conter os algoritmos de BUSCA SEM INFORMAÇÃO (UninformedSearch).
class UninformedSearch {
    private:
        /**
         * @brief Função que implementa a busca em profundidade limitada.
        Ela é usada pela função IterativeDepeningSearch. Não consgui usar a Hashtable
        nessa função de forma apropriada e não consegui descobrir o motivo
        * @param root raiz
        * @param limit limite que vai sendo aumentado
        * @return Ponteiro para a solução ou nullptr
        */
        static Puzzle* DepthLimitedSearch(Puzzle* root, const int& limit);

    public:

        //Como a classe vai ser estática, ela não precisa de um construtor
        UninformedSearch() = delete;

        /**
         * @brief Executa a busca em largura
         * @param root estado inicial/raiz
         * @return Printa a solução se ela existir
        */
        static void BreadthFirstSearch(Puzzle* root, const bool& print);

        
        /**
         * @brief Executa o algoritmo IDS com o auxílio da função DepthLimitedSearch
         * @param root estado inicial/raiz
         * @return Printa a solução se ela existir
        */
        static void IterativeDepeningSearch(Puzzle* root, const bool& print);

        /**
         * @brief Executa o algoritmo de custo Uniforme ou o Dijkstra. Não sabia
         * qual seria o custo então usei apenas a profundidade do nó.
         * @param root estado inicial/raiz
         * @return Printa a solução se ela existir
        */
        static void UniformCostSearch(Puzzle* root, const bool& print);
};  



#endif // !UNINFORMEDSEARCH_H