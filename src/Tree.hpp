#pragma once

#include <iostream>
#include <math.h>
#include <vector>
#include "Evaluation.hpp"
#include "Map.hpp"

const int RANGE = 1;

typedef struct Coords {
    int x;
    int y;
} Coords;

class Tree {
public:
    Tree() {}
    ~Tree() {}
    std::vector<std::pair<int, int>> getRelevantSquares(std::vector<std::vector<Square>>& board, int boardSize);
    void getSquaresAround(std::vector<std::vector<Square>>& board, Square square, std::vector<std::pair<int, int>>& relevantSquares, int boardSize);
    Eval minMax(int boardSize, std::vector<std::vector<Square>> board, enum Content stone, int depth, int curDepth, int alpha = -100000000, int beta = 100000000, int x = -1, int y = -1, int xPlay = -1, int yPlay = -1);

    int _nb_eval = 0;

private:
    int _id = 0;
    std::vector<int> _values;
    Evaluation _eval;
    Direction _direction;

    bool isSquareAlreadyRelevant(int x, int y, std::vector<std::pair<int, int>>& relevantSquares);
    bool isGameOver(int boardSize, std::vector<std::vector<Square>>& board);
    std::vector<std::vector<Square>> childBoard(std::vector<std::vector<Square>> board, std::pair<int, int> coord, enum Content stone);
    void addSquareOfAlignment(std::vector<std::vector<Square>>& board, int boardSize, std::vector<std::pair<int, int>>& relevantSquares, std::vector<std::pair<int, int>>& theBest, int alignment);
    bool crossCheck(std::vector<std::vector<Square>> simulatedBoard, int boardSize, int x, int y, int alignment);
};
