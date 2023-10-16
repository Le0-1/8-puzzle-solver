#include "InformedSearch.hpp"

void InformedSearch::AStar(Puzzle* root, const bool& print) {
    /*Comparador personalizado para a fila de prioridade mínima*/
    auto queue_cmp = [](Puzzle* a, Puzzle* b) {
        return a->m_Cost > b->m_Cost;
    };

    //Fronteira ou lista aberta
    std::priority_queue<Puzzle*, std::vector<Puzzle*>, decltype(queue_cmp)> open_list;

    //Nós já expandidos e nós que estão na fronteira
    Hashtable closed_list, generated_nodes;


    //Calcula o custo da raiz.
    root->m_Cost = root->CalculateManhattanCost() + root->Depth();

    Puzzle* current_node;
    Puzzle* current_child;

    open_list.push(root);
    generated_nodes.Insert(root);

    while (!open_list.empty()) {
        //Pega o primeiro da fila e o retira
        current_node = open_list.top(); 
        open_list.pop();           

        //Checa se é o objetivo
        if (current_node->isGoal()) {
            Utils::TraceSolution(current_node, print);
            return;
        }

        //Expande o nó e o adiciona na lista de nós expandidos
        current_node->ExpandNode();
        closed_list.Insert(current_node);


        for (unsigned i = 0; i < current_node->m_Childrens.size(); i++) {
            current_child = current_node->m_Childrens[i];

            //Se o nó não está na lista fechada
            if (closed_list.Find(current_child) == nullptr) {
                /*Checa agora se o nó também não está na lista aberta e se não 
                Se não estiver, adiciona*/
                Puzzle* ptr = generated_nodes.Find(current_child);
                if (ptr == nullptr) {
                    //F(n) = depth + distância da manhattan
                    current_child->m_Cost = current_child->CalculateManhattanCost() + current_child->Depth();
                    open_list.push(current_child);
                    generated_nodes.Insert(current_child);
                }

                //Se já está na lista aberta e o custo na lista é maior que o novo custo, atualize.
                else if (current_child->Depth() < ptr->Depth()) {
                    ptr->m_Cost = current_child->Depth() + ptr->CalculateManhattanCost();
                }
            } 
        }
    }
}

void InformedSearch::GreedySearch(Puzzle* root, const bool& print) {
    
    std::list<Puzzle*> open_list, closed_list;

    //Calcula o custo da raiz.
    root->m_Cost = root->CalculateMisplacedTiles();

    Puzzle* current_node;
    Puzzle* current_child;

    open_list.push_back(root);

    while (!open_list.empty()) {
        current_node = open_list.front();
        open_list.pop_front();

        if (current_node->isGoal()) {
            Utils::TraceSolution(current_node, print);
            return;
        }

        current_node->ExpandNode();
        closed_list.push_back(current_node);

        for (unsigned i = 0; i < current_node->m_Childrens.size(); i++) {
            current_child = current_node->m_Childrens[i];
            if (current_child->isGoal()) {
                Utils::TraceSolution(current_child, print);
                return;
            }

            //Verifica se está na lista fechada.
            if (Utils::FindNodeInList(closed_list, current_child) == nullptr) {

                //Não está na lista aberta, então adiciona nela.
                if (Utils::FindNodeInList(open_list, current_child) == nullptr) {
                    current_child->m_Cost = current_child->CalculateMisplacedTiles();
                    open_list.push_back(current_child);
                }
            }

        }
        //Ordena a lista para simular a fila de prioridade
        open_list.sort([](const Puzzle* a, const Puzzle* b) {
            return a->m_Cost < b->m_Cost;
        });
    }
}