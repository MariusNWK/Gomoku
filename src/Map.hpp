#pragma once

#include "useful.hpp"

const int MIN_SIZE_MAP = 5;
const int MAX_SIZE_MAP = 30;
const int MIN_X = 0;
const int MIN_Y = 0;

enum Content {
    EMPTY,
    OWN_STONE,
    OPPONENT_STONE
};

typedef struct Square {
    int x;
    int y;
    enum Content content;
} Square;

class Map {
public:
    Map()
    {
        _board = {};
    }
    ~Map() { }
    void setSize(int size);
    void setBoard(void);
    int getSize(void);

    std::vector<std::vector<Square>> _board;
    Square getSquareFromXY(int x, int y);

protected:
private:
    int _size;
};
