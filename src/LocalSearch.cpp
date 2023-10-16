#include "LocalSearch.hpp"

void LocalSearch::HillClimbing(Puzzle* root, const bool& print) {
    //Inicializa o vetor para guardar o caminho da solução
    std::vector<Puzzle*> path;
    path.push_back(root);

    //Assinala o nó atual como a raiz
    Puzzle* current = root;
    int counter = 0;

    //Calcula o custo da raiz
    current->m_Cost = current->CalculateManhattanCost();

    //Enquanto ainda for permitido fazer movimentos laterais
    while (HILL_CLIMBING_LIMIT > counter) {
        current->ExpandNode();

        //Inicializa as variáveis auxiliares
        Puzzle* best_child = nullptr;
        int min_cost = current->m_Cost;

        //Calcula os custos para cada filho e já tenta achar o melhor entre eles
        for (Puzzle* child : current->m_Childrens) {
            //Teste o filho é o goal
            if (child->isGoal()) {
                path.push_back(child);
                std::cout << path.size() - 1 << '\n';
                if (print) {
                    for (unsigned i = 0; i < path.size(); i++) {
                        path[i]->PrintState();
                    }
                }
                return;
            }
            //Calcula o custo 
            child->m_Cost = child->CalculateManhattanCost();

            //Esse if serve para procurar por um filho com um valor estritamente menor ou igual
            //que o nó pai
            if (child->m_Cost <= min_cost) {
                best_child = child;
                min_cost = child->m_Cost;
            }
        }
        //Se não existe nenhum filho com um valor estritamente menor ou igual, procura por um outro
        //Com no máximo o custo + 1. São os movimentos laterais
        if (best_child == nullptr) {
            //Agora o custo mínimo aceita o ERRO
            min_cost = min_cost + ERRO;
            for (Puzzle* child : current->m_Childrens) {
                if (child->m_Cost <= min_cost) {
                    best_child = child;
                    min_cost = child->m_Cost;
                }
            }
        }

        // Se nenhum melhor filho for encontrado pare.
        if (best_child == nullptr) break;

        // Se o melhor filho tem o mesmo custo ou maior, adiciona como movimento lateral
        if (best_child->m_Cost >= current->m_Cost) counter++;

        //Currente agora é o melhor filho.
        current = best_child;
        path.push_back(current);
    }

    //Printa a solução ou o melhor estado encontrado
    std::cout << path.size() - 1 << '\n';
    if (print) {
        for (unsigned i = 0; i < path.size(); i++) {
            path[i]->PrintState();
        }
    }
}