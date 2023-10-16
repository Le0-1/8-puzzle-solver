#ifndef UTILS_H
#define UTILS_H

#include "Puzzle.hpp"
#include "InformedSearch.hpp"
#include "UninformedSearch.hpp"
#include "Hashtable.hpp"

class Utils {
    public:
        /**
         * @brief Verifica se um elemento já está presenta na lista aberta
         * @param list lista a qual eu estou procurando o elemento
         * @param node elemento que quero verificar se está na lista
         * @return Ponteiro para o elemento ou nullptr se não encontrar
        */
        static Puzzle* FindNodeInList(const std::list<Puzzle*>& list, Puzzle* node);

        /**
         * @brief Função para alcançar a raiz a partir do nó que atingiu o objetivo.
         * Parte do último nó até a raiz para mostrar a solução
         * @param node Nó que atingiu o objetivo.
         * @param print Diz se vai precisar printar a solução ou não
        */
        static void TraceSolution(Puzzle* node, const bool& print);
};


#endif // !UTILS_H