#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Puzzle.hpp"

#include <list>

//Número de estados que existem no 8-puzzle
const std::size_t TABLE_SIZE = 500000; 

const std::size_t HASH_NUMBER = 11;

class Hashtable {
    private:

        //Inicializa tudo como nullptr
        std::vector<std::list<Puzzle*>> m_Table;
    public:

        //Construtor da Hashtable
        Hashtable();

        //Função que retorna o hash do elemento
        std::size_t Hash(Puzzle* node);

        /*Retorna um ponteiro para o elemento se ele está presente na Hashtable.
        Retorna nullptr caso contrário*/
        Puzzle* Find(Puzzle* node);

        //Insere um elemento
        void Insert(Puzzle* node);
};

#endif // !HASHTABLE_H