#pragma once

#include "Map.hpp"

const int MAX_ALIGNEMENT = 5;

enum AlignmentType {
    RIGHT,
    BOTRIGHT,
    BOT,
    BOTLEFT,
    LEFT,
    TOPLEFT,
    TOP,
    TOPRIGHT,
    NONE
};

class Direction {
public:
    Direction() { }
    ~Direction() { }
    int getRight(Square& square, int boardSize, std::vector<std::vector<Square>>& board, int& browsed);
    int getBotRight(Square& square, int boardSize, std::vector<std::vector<Square>>& board, int& browsed);
    int getBot(Square& square, int boardSize, std::vector<std::vector<Square>>& board, int& browsed);
    int getBotLeft(Square& square, int boardSize, std::vector<std::vector<Square>>& board, int& browsed);
    int getLeft(Square& square, int boardSize, std::vector<std::vector<Square>>& board, int& browsed);
    int getTopLeft(Square& square, int boardSize, std::vector<std::vector<Square>>& board, int& browsed);
    int getTop(Square& square, int boardSize, std::vector<std::vector<Square>>& board, int& browsed);
    int getTopRight(Square& square, int boardSize, std::vector<std::vector<Square>>& board, int& browsed);
    bool opposingStoneOrLimitInOppositeDirection(int x, int y, int boardSize, enum Content stoneContent, std::vector<std::vector<Square>>& board, int range, int xAdd, int yAdd);

protected:
private:
};
