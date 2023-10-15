#include "BSI.hpp"

bool BSI::Contains(const std::list<Puzzle*>& open_list, Puzzle* node) {
    for (auto it : open_list) {
        if (it->isSameState(node)) return true;
    }
    return false;
}

void BSI::TraceSolution(Puzzle* node) {
    //Vector para mostrar a solução
    std::vector<Puzzle*> steps;

    //Sai da solução e sobre o grafo até a raiz.
    while (node->m_Parent != nullptr) {
        steps.push_back(node);
        node = node->m_Parent;
    }

    //Coloca a raiz no vetor
    steps.push_back(node);

    //Printa os elementos do vector na ordem contrária, como especificado no TP
    std::cout << steps.size() - 1 << '\n';
    for (int i = steps.size() - 1; i >= 0; i--) {
        steps[i]->PrintState();
    }
    
}

void BSI::BreadthFirstSearch(Puzzle* root) {
    /*Fronteira
    Resolvi usar uma lista pois vou ter que iterar sobre a fronteira, e se ela fosse
    uma queue isso não funcionaria*/
    std::list<Puzzle*> open_list;

    //Nós explorados
    std::set<Puzzle*, decltype(closed_list_cmp)> closed_list;

    //Checa se já está na solução.
    if (root->isGoal()) {
        root->PrintState();
        return;
    }

    //Coloca a raiz como o primeiro elemento da lista
    open_list.push_back(root);

    //Ponteiros auxiliares
    Puzzle* current_node;
    Puzzle* current_child;

    //Enquanto a fronteira ainda possui algum elemento.
    while (!open_list.empty()) {
        //Pega o primeiro elemento da lista como se fosse uma fila
        current_node = open_list.front();

        //Remove o primeiro elemento que acabamos de pegar
        open_list.pop_front();

        //Expande o nó para gerar os próximos estados
        current_node->ExpandNode();

        //Insere na lista fechada.
        closed_list.insert(current_node);

        for (unsigned i = 0; i < current_node->m_Childrens.size(); i++) {
            current_child = current_node->m_Childrens[i];

            //Early Goal Test
            if (current_child->isGoal()) {
                BSI::TraceSolution(current_child);
                return;
            }

            /*is_in_closed_list é um ponteiro para o elemento se ele está no set,
            ou é um ponteiro para list.end() se ele não está no set*/
            auto is_in_closed_list = closed_list.find(current_child);

            //Booleano para verificar se o elemento está na lista aberta
            bool is_in_open_list = BSI::Contains(open_list, current_child);

            //Se ele não estiver na lista aberta e não estiver na lista fechada, adiciona na fronteira
            if ((!is_in_open_list) && (is_in_closed_list == closed_list.end())) {
                open_list.push_back(current_child);
            }

        }
    }
}

Puzzle* BSI::DepthLimitedSearch(Puzzle* root, const int& limit) {
    /*Agora eu uso uma lista como se fosse uma pilha para representar a fronteira.
    Estou usando uma lista para poder iterar sobre ela*/
    std::list<Puzzle*> open_list;

    open_list.push_back(root);
    Puzzle* current_node;
    Puzzle* current_child;

    while (!open_list.empty()) {
        current_node = open_list.back();
        open_list.pop_back();

        /*Também faço o teste aqui pois quando o Depth for >= que o limit eu tenho que
        começar a desempilhar*/
        if (current_node->isGoal()) {  
            return current_node;
        }
        /*Só vou expandir os nós se a sua profundide for menor que o limite.
        Caso contrário apenas passa para a próxima iteração*/
        else if (current_node->Depth() < limit)  {
            current_node->ExpandNode();
            for (unsigned i = 0; i < current_node->m_Childrens.size(); i++) {
                current_child = current_node->m_Childrens[i];
                if (current_child->isGoal()) { //Early Goal Test
                    return current_child;
                }
                else if (!BSI::Contains(open_list, current_child)) {
                    open_list.push_back(current_child);
                }
            }
        }
    }
    //Não achou resposta
    return nullptr;
}

void BSI::IterativeDepeningSearch(Puzzle* root) {

    /* Como estou usando ponteiros, se eu não criar uma cópia da raiz e apagar ela
    logo depois de terminar uma busca em um limite qualquer, os filhos gerados irão
    se manter na memória, o que iria gastar bastante tempo para iterar sobre.
    Deletando logo após a busca, eu consigo apagar todos os filhos gerados e iniciar
    uma nova busca*/

    for (int i = 0; i < LIMIT; i++) {
        Puzzle *root_copy = new Puzzle(root->m_CurrentState, Moves::NONE);
        Puzzle *anwser = BSI::DepthLimitedSearch(root_copy, i);
        if (anwser != nullptr) {
            BSI::TraceSolution(anwser);
            delete root_copy;
            return;
        }
        delete root_copy;
    }
}

void BSI::UniformCostSearch(Puzzle* root) {
    std::list<Puzzle*> open_list;
    std::set<Puzzle*, decltype(closed_list_cmp)> closed_list;

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
        closed_list.insert(current_node);

        for (unsigned i = 0; i < current_node->m_Childrens.size(); i++) {
            current_child = current_node->m_Childrens[i];
            bool is_in_closed_list = closed_list.find(current_child) != closed_list.end(); 
            
        }
    }
}   