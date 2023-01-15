#include "AI.hpp"

void AI::play(Map& map)
{
    int size = map.getSize();

    // envoi d'un board où c'est à moi de jouer
    Eval evaluation = _tree.minMax(size, map._board, OWN_STONE, 3, 3);
    // evaluation.x et evaluation.y valent -1 si depth est mis à 0 ou moins
    // OU
    // si le board envoyé est un board gameOver
    if (evaluation.x > -1 && evaluation.y > -1) {
        map._board[evaluation.y][evaluation.x].content = OWN_STONE;
    }
    send(std::to_string(evaluation.x) + "," + std::to_string(evaluation.y));
}

void AI::send(std::string output)
{
    std::cout << output << std::endl;
    _myfile << "Moi : " << output << std::endl;
}

std::string AI::receive(void)
{
    std::string input;
    std::getline(std::cin, input);
    _myfile << "Ordi: " << input << std::endl;
    return input;
}
