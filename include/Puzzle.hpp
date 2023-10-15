#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>
#include <memory>
#include <vector>

const int PUZZLE_SIZE = 9;
const int ZERO = 0;

//Enum para representar os movimentos legais no vetor
//Up : Diminui 3 no vetor
//Down: Aumenta 3 no vetor
//Left: Diminui 1 no vetor
//Right: Aumenta 1 no vetor
enum Moves {
    NONE = 0,
    UP = -3,
    DOWN = +3,
    LEFT = -1,
    RIGHT = +1
};

//Classe para representar o estado do 8-puzzle.
class Puzzle {
    public:
        //---------------- Membros Privados ----------------------//

        //Pai do nó
        Puzzle* m_Parent;

        //Filhos do nó
        std::vector<Puzzle*> m_Childrens;

        //Vetor em uma dimensão que representa o estado atual do nó
        int m_CurrentState[PUZZLE_SIZE] = { -1 };

        //Index do ZERO no CurrentState
        int m_ZeroIndex;

        //Último movimento executado
        Moves m_LastMove;

        //Custo para chegar da raiz ao nó.
        int m_Cost;

        //---------------- Métodos Privados ----------------------//

        //Função para adicionar um filho à 'm_Childrens'.
        void AddChild(Puzzle* child);

        /**
         * @brief Função para trocar o ZERO de posição
         * @param pos Index para o qual o ZERO vai se mover.
        */
        void SwapZero(const int& pos);

        //Função que checa se o movimento do ZERO no vetor é legal.
        //Se for fazer um movimento para cima e o ZERO estiver em um index menor que 2
        //esse movimento é ilegal, pois para mover para cima preciso diminuir o index em 3.
        //O mesmo racíocinio se aplica aos outros movimentos, resguardada suas particularidades.
        bool isMovementValid(const Moves& movement);

        //Função que vai efetivamente fazer o movimento do ZERO no vetor e criar o filho.
        void DoMovement(const Moves& movement);


    public:
        //---------------- Métodos Públicos ----------------------//
        
        /**
         * @brief Construtor para inicializar o estado inicial do nó
         * @param values Estado inicial do vetor do 8-puzzle
         * @param last_move Último movimento executado para chegar ao estado atual. A raiz tem como último movimento o NONE, que é representado pelo zero.
        */
        Puzzle(const int values[], const Moves& last_move);

        /**
         * @brief Destrutor da classe que usa a função auxiliar ClearRecursive
         * para apagar todos os nós. Quando percorro os filhos e chamo o delete,
         * ele vai chamar o destrutor novamente para os filhos desses filhos e indo
         * até não ter mais filhos. É chamada de destruição recursiva.
         * 
        */
        ~Puzzle();

        //Expande o nó atual para encontrar os próximos estados
        void ExpandNode();
        
        //Função para testar se chegamos ao "Goal State"
        //Goal State : [1 2 3 4 5 6 7 8 0]
        bool isGoal();

        //Printa o estado do nó
        void PrintState();

        /*Função que vai ser usada para comparar se um estado é igual ao outro.
        Ela vai ser usada na classe BSI (Busca sem Informação) para verificar se um
        estado já se encontra na lista aberta*/
        bool isSameState(Puzzle* node);

        /*Função que retorna a profundidade que o nó se encontra na árvore.
        Vou usar essa função no algoritmo IDS*/
        int Depth();

        /*Calcula o custo do caminho da raiz até o nó. Ele faz a soma do 'n'primeiros
        números da raiz até esse nó em questão*/
        int CalculateCost();

        //Permissão para os algoritmos de busca sem informação acessar os membros privados
        friend class BSI;
};

#endif // !PUZZLE_H