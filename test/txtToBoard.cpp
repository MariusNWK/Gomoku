#include <time.h>
#include "../src/Evaluation.hpp"
#include "../src/Tree.hpp"

int getBoardSize(std::string insidefile)
{
    int size = 0;

    for (int i = 0; insidefile[i] != '|'; i += 2) {
        size += 1;
    }
    return size;
}

std::vector<std::vector<Square>> txtToBoard(std::string insidefile)
{
    std::vector<std::vector<Square>> board = {};
    int boardSize = getBoardSize(insidefile);

    Square default_square = { 0, 0, EMPTY };
    for (int y = 0, k = 0; y < boardSize; y++, k += 1) {
        board.push_back({});
        for (int x = 0; x < boardSize; x++, k += 2) {
            default_square.x = x;
            default_square.y = y;
            if (insidefile[k] == '<') {
                default_square.content = OWN_STONE;
            } else if (insidefile[k] == '/') {
                default_square.content = OPPONENT_STONE;
            } else {
                default_square.content = EMPTY;
            }
            board[y].push_back(default_square);
        }
    }
    return board;
}

bool isRelevantSquare(int x, int y, std::vector<std::pair<int, int>> coords)
{
    for (std::pair<int, int> coord : coords) {
        if (x == coord.first && y == coord.second) {
            return true;
        }
    }
    return false;
}

void displayRelevantSquares(std::vector<std::vector<Square>>& board,
    std::vector<std::pair<int, int>> coords, int boardSize)
{
    for (int y = 0; y < boardSize; y++) {
        std::string line = "";
        for (int x = 0; x < boardSize; x++) {
            if (isRelevantSquare(x, y, coords) || board[y][x].content != EMPTY) {
                if (board[y][x].content == EMPTY) {
                    line += "[]";
                } else if (board[y][x].content == OWN_STONE) {
                    line += "<>";
                } else {
                    line += "/\\";
                }
            } else {
                line += "{}";
            }
        }
        line += "|";
        std::cout << line << std::endl;
    }
}

int main(int ac, char** av)
{
    if (ac != 2) {
        std::cerr << "./a.out file" << std::endl;
        return 84;
    }
    std::ifstream myfile(av[1]);

    if (!myfile.is_open()) {
        std::cerr << "invalid file" << std::endl;
        return 84;
    }

    std::string insidefile;
    std::string line;
    while (myfile) {
        myfile >> line;
        insidefile += line;
    }
    std::vector<std::vector<Square>> board = txtToBoard(insidefile);
    int boardSize = static_cast<int>(board.size());

    std::cout << "boardSize: " << boardSize << std::endl;

    Tree tree;

    clock_t begin = clock();

    Eval eval = tree.minMax(boardSize, board, OWN_STONE, 3, 3);

    clock_t end = clock();

    unsigned long milliseconds = (end - begin) * 1000 / CLOCKS_PER_SEC;

    std::cout << "nb evals: " << tree._nb_eval << std::endl;

    std::cout << "play x: " << eval.x << ", y: " << eval.y << std::endl;

    std::cout << "eval: " << eval.value << std::endl;

    std::cout << "time: " << milliseconds << " ms" << std::endl;

    // Tree algo;
    // displayRelevantSquares(board, algo.getRelevantSquares(board, boardSize), boardSize);

    // Evaluation eval;
    // int score = eval.getFromBoard(board, OWN_STONE);
    // std::cout << "score: " << score << std::endl;
    return 0;
}
