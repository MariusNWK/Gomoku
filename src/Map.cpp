#include "Map.hpp"

void Map::setSize(int size)
{
    _size = size;
    setBoard();
}

void Map::setBoard(void)
{
    Square default_square = { 0, 0, EMPTY };
    for (int y = 0; y < _size; y++) {
        _board.push_back({});
        for (int x = 0; x < _size; x++) {
            default_square.x = x;
            default_square.y = y;
            _board[y].push_back(default_square);
        }
    }
}

int Map::getSize(void)
{
    return _size;
}

Square Map::getSquareFromXY(int x, int y)
{
    if ((x >= MIN_X && x < _size) && (y >= MIN_Y && y < _size)) {
        return _board[y][x];
    }
    // TODO throw Error
    // En attendant, je fais confiance au logiciel d'envoyer de bonnes coordonnées
    return _board[y][x];
}
