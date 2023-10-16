#include "BCI.hpp"

void BCI::AStar(Puzzle* root) {
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
        current_node = open_list.top(); //Pega o primeiro da fila
        open_list.pop();            //Retira o primeiro da fila

        //Checa se é o objetivo
        if (current_node->isGoal()) {
            BSI::TraceSolution(current_node);
            return;
        }

        //Expande o nó
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

void BCI::GreedySearch(Puzzle* root) {
    
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
            BSI::TraceSolution(current_node);
            return;
        }

        current_node->ExpandNode();
        closed_list.push_back(current_node);

        for (unsigned i = 0; i < current_node->m_Childrens.size(); i++) {
            current_child = current_node->m_Childrens[i];
            if (current_child->isGoal()) {
                BSI::TraceSolution(current_child);
                return;
            }

            //Verifica se está na lista fechada.
            if (BSI::FindNodeInList(closed_list, current_child) == nullptr) {

                //Não está na lista aberta, então adiciona nela.
                if (BSI::FindNodeInList(open_list, current_child) == nullptr) {
                    current_child->m_Cost = current_child->CalculateMisplacedTiles();
                    open_list.push_back(current_child);
                }
            }

        }
        //Ordena a lista
        open_list.sort([](const Puzzle* a, const Puzzle* b) {
            return a->m_Cost < b->m_Cost;
        });
    }
}


void BCI::HillClimbing(Puzzle* root) {
    //Inicializa o vetor para guardar o caminho da solução
    std::vector<Puzzle*> path;
    path.push_back(root);

    //Assinala o nó atual como a raiz
    Puzzle* current = root;
    int counter = 0;

    //Calcula o custo da raiz
    current->m_Cost = current->CalculateManhattanCost();

    while (HILL_CLIMBING_LIMIT > counter) {
        current->ExpandNode();

        Puzzle* best_child = nullptr;
        int min_cost = current->m_Cost;

        //Calcula os custos para cada filho e já tenta achar o melhor entre eles
        for (Puzzle* child : current->m_Childrens) {
            if (child->isGoal()) {
                path.push_back(child);
                for (int i = 0; i < path.size(); i++) {
                    path[i]->PrintState();
                }
                std::cout << path.size() - 1 << '\n';
                return;
            }
            child->m_Cost = child->CalculateManhattanCost();

            //Esse if serve para procurar por um filho com um valor estritamente menor ou igual
            if (child->m_Cost <= min_cost) {
                best_child = child;
                min_cost = child->m_Cost;
            }
        }
        //Se não existe nenhum filho com um valor estritamente menor, procura por um outro
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
    for (int i = 0; i < path.size(); i++) {
        path[i]->PrintState();
    }
    std::cout << path.size() - 1 << '\n';
}