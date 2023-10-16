#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Puzzle.hpp"

#include <list>

//Número arbitrário
const std::size_t TABLE_SIZE = 500000; 

const std::size_t HASH_NUMBER = 11;

class Hashtable {
    private:

        //Cada posição no vetor é uma lista para permitir colisão
        std::vector<std::list<Puzzle*>> m_Table;
        
        //Função que retorna o hash do elemento. Peguei uma arbitrária
        std::size_t Hash(Puzzle* node);
    public:

        //Construtor da Hashtable. Inicializa todas as listas
        Hashtable();


        /**
         * @brief Função para procurar se um elemento está na hashtable
         * @param node Nó a verificar
         * @return Ponteiro para o elemento se achar ou nullptr caso contrário
        */
        Puzzle* Find(Puzzle* node);

        //Insere um elemento
        void Insert(Puzzle* node);
};

#endif // !HASHTABLE_H