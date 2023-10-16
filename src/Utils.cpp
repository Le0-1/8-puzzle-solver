#include "Utils.hpp"

Puzzle* Utils::FindNodeInList(const std::list<Puzzle*>& list, Puzzle* node) {
    for (Puzzle* it : list) {
        if (it->isSameState(node)) return it;
    }
    return nullptr;
}

void Utils::TraceSolution(Puzzle* node, const bool& print) {
    //Vector para mostrar a solução
    std::vector<Puzzle*> steps;

    //Sai da solução e sobe o grafo até a raiz.
    while (node->m_Parent != nullptr) {
        steps.push_back(node);
        node = node->m_Parent;
    }

    //Coloca a raiz no vetor
    steps.push_back(node);

    //Printa o número de movimentos
    std::cout << steps.size() - 1 << '\n';
    
    //Printa os estados até a solução
    if (print) {
        for (int i = steps.size() - 1; i >= 0; i--) {
            steps[i]->PrintState();
        }
    }
    
}
