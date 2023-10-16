#include "Puzzle.hpp"
#include "InformedSearch.hpp"
#include "UninformedSearch.hpp"
#include "LocalSearch.hpp"
#include "Utils.hpp"
#include "Hashtable.hpp"


int main(int argc, const char** argv) {
    if (argc >= 11) {
        //Algoritmo passado na linha de comando
        std::string algorithm = argv[1];
        bool print = 0; 

        std::vector<int> initial_state;
        for (int i = 2; i < 11; i++) {
            int valor = std::stoi(argv[i]);
            initial_state.push_back(valor);
        }

        //Significa que o PRINT foi passado como parâmetro
        if (argc > 11) {
            print = 1;
        }

        //Inicializa a raiz
        Puzzle* root = new Puzzle(initial_state, Moves::NONE);

        if (algorithm == "A") {
            InformedSearch::AStar(root, print);
        }
        else if (algorithm == "B") {
            UninformedSearch::BreadthFirstSearch(root, print);
        }
        else if (algorithm == "G") {
            InformedSearch::GreedySearch(root, print);
        }
        else if (algorithm == "H") {
            LocalSearch::HillClimbing(root, print);
        }
        else if (algorithm == "I") {
            UninformedSearch::IterativeDepeningSearch(root, print);
        }
        else if (algorithm == "U") {
            UninformedSearch::UniformCostSearch(root, print);
        }
        else {
            std::cout << "Algoritmo não conhecido passado na linha de comando" << '\n';
        }

        delete root;
        return 0;
    }
    return 0;
}

