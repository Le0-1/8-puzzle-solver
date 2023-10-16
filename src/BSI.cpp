#include "BSI.hpp"

Puzzle* BSI::FindNodeInList(const std::list<Puzzle*>& list, Puzzle* node) {
    for (Puzzle* it : list) {
        if (it->isSameState(node)) return it;
    }
    return nullptr;
}

void BSI::TraceSolution(Puzzle* node) {
    //Vector para mostrar a solução
    std::vector<Puzzle*> steps;

    //Sai da solução e sobe o grafo até a raiz.
    while (node->m_Parent != nullptr) {
        steps.push_back(node);
        node = node->m_Parent;
    }

    //Coloca a raiz no vetor
    steps.push_back(node);

    //Printa os elementos do vector na ordem contrária, como especificado no TP
    std::cout << steps.size() - 1 << '\n';
    // for (int i = steps.size() - 1; i >= 0; i--) {
    //     steps[i]->PrintState();
    // }
    
}

void BSI::BreadthFirstSearch(Puzzle* root) {
    /*Fronteira. Resolvi usar uma lista para facilitar*/
    std::list<Puzzle*> open_list;

    //Nós explorados e Nós Gerados para consulta mais rápida na Hashtable
    Hashtable closed_list, generated_nodes;

    //Checa se já está na solução.
    if (root->isGoal()) {
        BSI::TraceSolution(root);
        return;
    }

    //Coloca a raiz como o primeiro elemento da lista e adiciano a raiz aos nós gerados
    open_list.push_back(root);
    generated_nodes.Insert(root);

    //Ponteiros auxiliares
    Puzzle* current_node;
    Puzzle* current_child;

    //Enquanto a fronteira ainda possui algum elemento o while irá rodar.
    while (!open_list.empty()) {
        //Pega o primeiro elemento da lista como se fosse uma fila
        current_node = open_list.front();

        //Remove o primeiro elemento que acabamos de pegar
        open_list.pop_front();

        //Verifica se o Nó é o objetivo
        if (current_node->isGoal()) {
            BSI::TraceSolution(current_node);
            return;
        }

        //Expande o nó para gerar os próximos estados
        current_node->ExpandNode();

        //Insere na Hashtable que representa a lista fechada.
        closed_list.Insert(current_node);

        for (unsigned i = 0; i < current_node->m_Childrens.size(); i++) {
            current_child = current_node->m_Childrens[i];

            //Early Goal Test
            if (current_child->isGoal()) {
                BSI::TraceSolution(current_child);
                return;
            }

            /*Se o filho não estiver na lista fechada e nem foi gerado ainda, eu
            adiciono ele na lista aberta*/
            if (closed_list.Find(current_child) == nullptr) {
                if (generated_nodes.Find(current_child) == nullptr) {
                    open_list.push_back(current_child);
                    generated_nodes.Insert(current_child);
                }
            }

        }
    }
}

Puzzle* BSI::DepthLimitedSearch(Puzzle* root, const int& limit) {
    /*Agora eu uso uma lista como se fosse uma pilha para representar a fronteira.*/
    std::list<Puzzle*> open_list;

    open_list.push_back(root); //Add raiz na fronteira
 
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

                else if (BSI::FindNodeInList(open_list, current_child) == nullptr) {
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

    /*Comparador personalizado para a fila de prioridade mínima*/
    auto queue_cmp = [](Puzzle* a, Puzzle* b) {
        return a->m_Cost > b->m_Cost;
    };

    //Fronteira
    std::priority_queue<Puzzle*, std::vector<Puzzle*>, decltype(queue_cmp)> open_list;
    
    //Hashtable para guardar os nós gerados e expandidos
    Hashtable closed_list, generated_nodes;

    Puzzle* current_node;
    Puzzle* current_child;

    //Custo da raiz é ZERO
    root->m_Cost = root->Depth();
    open_list.push(root);
    generated_nodes.Insert(root);

    while (!open_list.empty()) {
        current_node = open_list.top();
        open_list.pop();


        if (current_node->isGoal()) {
            BSI::TraceSolution(current_node);
            return;
        }
        current_node->ExpandNode();
        closed_list.Insert(current_node);

        for (unsigned i = 0; i < current_node->m_Childrens.size(); i++) {
            //Pega o filho atual e calcula o custo dele.
            current_child = current_node->m_Childrens[i];
            current_child->m_Cost = current_child->Depth();

            //Variáveis auxiliares que me dizem se um nó está na lista aberta ou fechada
            Puzzle *ptr = closed_list.Find(current_child);
            Puzzle *aux = generated_nodes.Find(current_child);

            //Se não estiver na lista fechada e nem na lista aberta eu adiciono.
            if (ptr == nullptr && aux == nullptr) {
                open_list.push(current_child);
                generated_nodes.Insert(current_child);
            } 
            
            //Se Está na lista aberta com um custo maior, atualiza o custo
            else if (aux != nullptr && (aux->m_Cost > current_child->m_Cost)) {
                aux->m_Cost = current_child->m_Cost;
            }
        }
    }
}

