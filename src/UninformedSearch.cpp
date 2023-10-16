#include "UninformedSearch.hpp"

void UninformedSearch::BreadthFirstSearch(Puzzle* root, const bool& print) {
    /*Fronteira. Resolvi usar uma lista para facilitar*/
    std::list<Puzzle*> open_list;

    //Nós explorados e Nós Gerados para consulta mais rápida na Hashtable
    //Nós gerados são aqueles que estão na fronteira mas não estão na lista fechada
    Hashtable closed_list, generated_nodes;

    //Coloca a raiz como o primeiro elemento da lista e adiciana a raiz aos nós gerados
    open_list.push_back(root);
    generated_nodes.Insert(root);

    //Ponteiros auxiliares
    Puzzle* current_node;
    Puzzle* current_child;

    //Enquanto a fronteira ainda possui algum elemento o while irá rodar.
    while (!open_list.empty()) {
        //Pega o primeiro elemento da lista como se fosse uma fila 
        current_node = open_list.front();
        open_list.pop_front();

        //Verifica se o Nó é o objetivo
        if (current_node->isGoal()) {
            Utils::TraceSolution(current_node, print);
            return;
        }

        //Expande o nó para gerar os próximos estados
        current_node->ExpandNode();

        //Insere na Hashtable que representa a lista fechada.
        closed_list.Insert(current_node);

        /*Para cada filho, testa se é o objetivo e se não for, eu vejo se ele está
        em alguma das listas*/
        for (unsigned i = 0; i < current_node->m_Childrens.size(); i++) {

            //Assinala o primeiro filho à current_child
            current_child = current_node->m_Childrens[i];

            //Early Goal Test
            if (current_child->isGoal()) {
                Utils::TraceSolution(current_child, print);
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

Puzzle* UninformedSearch::DepthLimitedSearch(Puzzle* root, const int& limit) {
    /*Agora eu uso uma lista como se fosse uma pilha para representar a fronteira.*/
    std::list<Puzzle*> open_list;

    open_list.push_back(root); //Add raiz na fronteira
 
    //Ponteiros auxiliares
    Puzzle* current_node;
    Puzzle* current_child;

    while (!open_list.empty()) {
        //"Popa" o primeiro elemento da lista
        current_node = open_list.back();
        open_list.pop_back();

        /*Também faço o teste aqui pois quando o Depth for maior ou igual que o limit 
        eu tenho que começar a desempilhar para para percorre outro caminho*/
        if (current_node->isGoal()) {  
            return current_node;
        }
        /*Só vou expandir os nós se a sua profundide for menor que o limite.
        Caso contrário apenas passa para a próxima iteração*/
        else if (current_node->Depth() < limit)  {
            current_node->ExpandNode();

            //Para cada filho expandido, verificamos se é o objetivo.
            //Se ele não for, e não também não está na lista aberta, nós o adicionamos nela
            for (unsigned i = 0; i < current_node->m_Childrens.size(); i++) {
                current_child = current_node->m_Childrens[i];

                if (current_child->isGoal()) { //Early Goal Test
                    return current_child;
                }

                else if (Utils::FindNodeInList(open_list, current_child) == nullptr) {
                    open_list.push_back(current_child);
                }
            }
        }

    }
    //Não achou resposta
    return nullptr;
}

void UninformedSearch::IterativeDepeningSearch(Puzzle* root, const bool& print) {

    /* Como estou usando ponteiros, se eu não criar uma cópia da raiz e apagar ela
    logo depois de terminar uma busca em um limite qualquer, os filhos gerados irão
    se manter na memória, o que iria gastar bastante tempo para iterar sobre.
    Deletando logo após a busca, eu consigo apagar todos os filhos gerados e iniciar
    uma nova busca, mas isso consome tempo também*/

    for (int i = 0; i < LIMIT; i++) {
        //Copia a raiz 
        Puzzle *root_copy = new Puzzle(root->m_CurrentState, Moves::NONE);
        //Pega o valor de retorno do DepthLimitedSearch
        Puzzle *anwser = UninformedSearch::DepthLimitedSearch(root_copy, i);
        if (anwser != nullptr) {
            Utils::TraceSolution(anwser, print);
            delete root_copy;
            return;
        }
        delete root_copy;
    }
}

void UninformedSearch::UniformCostSearch(Puzzle* root, const bool& print) {

    /*Comparador personalizado para a fila de prioridade mínima*/
    auto queue_cmp = [](Puzzle* a, Puzzle* b) {
        return a->m_Cost > b->m_Cost;
    };

    //Fronteira
    std::priority_queue<Puzzle*, std::vector<Puzzle*>, decltype(queue_cmp)> open_list;

    //Hashtable para guardar os nós gerados e expandidos
    Hashtable closed_list, generated_nodes;

    //Ponteiros auxiliares
    Puzzle* current_node;
    Puzzle* current_child;

    //Custo da raiz é ZERO
    root->m_Cost = root->Depth();
    //Adiciona a raiz na lista aberta e na hashtable de nós gerados.
    open_list.push(root);
    generated_nodes.Insert(root);

    while (!open_list.empty()) {
        //Remove o primeiro elemento da fila
        current_node = open_list.top();
        open_list.pop();

        //Checa se chegamos ao objetivo
        if (current_node->isGoal()) {
            Utils::TraceSolution(current_node, print);
            return;
        }

        //Expande o nó e o coloca na lista de nós expandidos
        current_node->ExpandNode();
        closed_list.Insert(current_node);

        /*Para cada filho testamos se ele não está na lista aberta ou fechada,
        se não estiver adicionamos na lista aberta e calculamos o custo dele*/
        for (unsigned i = 0; i < current_node->m_Childrens.size(); i++) {
            //Pega o filho atual
            current_child = current_node->m_Childrens[i];

            /*Variáveis auxiliares que me dizem se um nó já foi adicionado à lista aberta 
            e fechada.*/
            Puzzle *ptr = closed_list.Find(current_child);
            Puzzle *aux = generated_nodes.Find(current_child);

            //Se não estiver na lista fechada e nem na lista aberta eu adiciono.
            if (ptr == nullptr && aux == nullptr) {
                current_child->m_Cost = current_child->Depth();
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

