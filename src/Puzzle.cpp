#include "Puzzle.hpp"

Puzzle::Puzzle(const int values[], const Moves& last_move) {
    this->m_Parent = nullptr;
    this->m_LastMove = last_move;
    this->m_Cost = 0; //Vou usar essa variável apenas nos algoritmos que envolvem custo
    for (int i = 0; i < PUZZLE_SIZE; i++) {
        if (values[i] == ZERO) this->m_ZeroIndex = i; //Pega o index do ZERO
        this->m_CurrentState[i] = values[i];
    }
}

Puzzle::Puzzle(const std::vector<int>& values, const Moves& last_move) {
    this->m_Parent = nullptr;
    this->m_LastMove = last_move;
    this->m_Cost = 0; //Vou usar essa variável apenas nos algoritmos que envolvem custo
    for (int i = 0; i < PUZZLE_SIZE; i++) {
        if (values[i] == ZERO) this->m_ZeroIndex = i; //Pega o index do ZERO
        this->m_CurrentState[i] = values[i];
    }
}

Puzzle::~Puzzle() {
    for (Puzzle* child : m_Childrens) delete child;
}


//-----------Exemplos de como o ZERO pode se mover no vetor--------//

//index:    //values:
//0 1 2     //4 5 8
//3 4 5     //6 0 7 --> ZERO pode se mover em todas as direções
//6 7 8     //6 4 3

//index:    //values:
//0 1 2     //4 0 8
//3 4 5     //6 5 7 --> ZERO Não pode se mover para cima
//6 7 8     //6 4 3
bool Puzzle::isMovementValid(const Moves& movement) {
    /*Checa se eu estou fazendo o movimento contrário ao que eu tinha feito para chegar nesse estado.
    Exemplo: Se eu fizer o movimento UP e alcançar um próximo estado eu não posso fazer o movimento DOWN 
    pois eu apenas retornaria ao último estado. O menos(-) antes do this->m_LastMove serve para verificar 
    isso*/
    if (movement == -(this->m_LastMove)) {
        return false;
    }
    else if (movement == Moves::UP) {
        if (this->m_ZeroIndex > 2) return true;
    }
    else if (movement == Moves::DOWN) {
        if (this->m_ZeroIndex < 6) return true;
    }
    else if (movement == Moves::LEFT) {
        if (this->m_ZeroIndex != 0 && this->m_ZeroIndex != 3 && this->m_ZeroIndex != 6)
            return true;
    }
    else if (movement == Moves::RIGHT) {
        if (this->m_ZeroIndex != 2 && this->m_ZeroIndex != 5 && this->m_ZeroIndex != 8)
            return true;
    }
    return false;
}

Puzzle* Puzzle::DoMovement(const Moves& movement) {
    //Checa se o movimento é valido
    if (this->isMovementValid(movement)) {
        //Pega o index do zero atual para depois voltar ao estado original
        int old_zero_pos = this->m_ZeroIndex;

        //Pega a nova posição que o zero irá ocupar no vetor e faz a troca
        int new_zero_pos = (this->m_ZeroIndex) + (movement);
        this->SwapZero(new_zero_pos);

        //Cria o filho com base no novo estado do vetor e no movimento
        Puzzle* child = new Puzzle(this->m_CurrentState, movement);

        //Retorna o ZERO à posição original para que o pai se mantenha correto.
        this->SwapZero(old_zero_pos); 

        //Retorna filho recém criado
        return child;
    }
    //Se movimento é ilegal, retorna nulo
    return nullptr;
}

void Puzzle::SwapZero(const int& pos) {
    this->m_CurrentState[m_ZeroIndex] = this->m_CurrentState[pos];
    this->m_CurrentState[pos] = ZERO;
    this->m_ZeroIndex = pos;
}

void Puzzle::ExpandNode() {
    this->AddChild(DoMovement(Moves::UP));
    this->AddChild(DoMovement(Moves::DOWN));
    this->AddChild(DoMovement(Moves::LEFT));
    this->AddChild(DoMovement(Moves::RIGHT));
}

void Puzzle::AddChild(Puzzle* child) { 
    if (child != nullptr) {
        child->m_Parent = this;
        this->m_Childrens.push_back(child);
    }
};

bool Puzzle::isGoal() {
    for (int i = 0; i < PUZZLE_SIZE - 1; i++) {
        if (this->m_CurrentState[i] != i + 1)
            return false;
    }
    //Checa se o último valor do vetor é o ZERO
    if (this->m_CurrentState[PUZZLE_SIZE - 1] != ZERO) return false;
    return true;
}

void Puzzle::PrintState() {
    for (int i = 0; i < PUZZLE_SIZE; i++) {
        //Esse if é para apenas saltar uma linha e printar o 8-puzzle como uma matriz
        if (i % 3 == 0) std::cout << '\n'; 
        std::cout << this->m_CurrentState[i] << ' ';
    }
    std::cout << '\n';
}

int Puzzle::Depth() {
    int i = 0;
    Puzzle* ptr = this->m_Parent;
    while (ptr != nullptr) {
        i++;
        ptr = ptr->m_Parent;
    }
    return i;
}

int Puzzle::CalculateManhattanCost() {
    int distance = 0;
    
    for (int i = 0; i < PUZZLE_SIZE; i++) {
        if (this->m_CurrentState[i] != 0) { //Pula o Zero
            int row_goal = i / 3;
            int col_goal = i % 3;
            
            int value = this->m_CurrentState[i];
            int row_current = (value - 1) / 3;
            int col_current = (value - 1) % 3;
            
            int row_distance = abs(row_goal - row_current);
            int col_distance = abs(col_goal - col_current);
            
            distance += row_distance + col_distance;
        }
    }
    
    return distance;
}

int Puzzle::CalculateMisplacedTiles() {
    int misplaced_tiles = 0;
    for (int i = 0; i < PUZZLE_SIZE; i++) {
        if (this->m_CurrentState[i] != ZERO) {
            if (this->m_CurrentState[i] != i + 1) misplaced_tiles++;
        }
    }
    return misplaced_tiles;
}

bool Puzzle::isSameState(Puzzle* node) {
    for (int i = 0; i < PUZZLE_SIZE; i++) {
        if (this->m_CurrentState[i] != node->m_CurrentState[i]) {
            return false;
        }
    }
    return true;
}
