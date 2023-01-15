#include "Direction.hpp"

bool Direction::opposingStoneOrLimitInOppositeDirection(
    int x, int y, int boardSize, enum Content stoneContent,
    std::vector<std::vector<Square>>& board, int range, int xAdd, int yAdd)
{
    int xMax = boardSize - 1;
    int yMax = boardSize - 1;

    x += xAdd;
    y += yAdd;
    while (range > 0) {
        if (x < MIN_X || x > xMax) {
            return true;
        }
        if (y < MIN_Y || y > yMax) {
            return true;
        }
        if (board[y][x].content != stoneContent && board[y][x].content != EMPTY) {
            return true;
        }
        x += xAdd;
        y += yAdd;
        range -= 1;
    }
    return false;
}

int Direction::getRight(Square& square, int boardSize,
    std::vector<std::vector<Square>>& board, int& browsed)
{
    int alignment = 1;
    int maxBrowse = 4;
    browsed = 1;
    int xMax = boardSize - 1;
    int x = square.x + 1;
    int y = square.y;

    while (x <= xMax && maxBrowse > 0) {
        if (board[y][x].content == square.content) {
            alignment += 1;
        } else if (board[y][x].content != EMPTY) { // ni square.content, ni EMPTY, donc stone adverse ->
                                                   // bloque l'alignement
            if (alignment < 5 && opposingStoneOrLimitInOppositeDirection(square.x, square.y, boardSize, board[square.y][square.x].content, board, MAX_ALIGNEMENT - browsed, -1, 0)) /* Right donc opposé est Left */
            {
                // vérifie que l'alignement n'est pas encerclé de stones ennemis, si
                // c'est le cas, l'alignement n'a pas de valeur, on return donc un
                // alignement de 1
                return 1;
            }
            return alignment;
        }
        maxBrowse -= 1;
        browsed += 1;
        x += 1;
    }
    if (x > xMax && alignment < 5 && opposingStoneOrLimitInOppositeDirection(square.x, square.y, boardSize, board[square.y][square.x].content, board, MAX_ALIGNEMENT - browsed, -1, 0)) {
        // même logique mais ici l'un des deux côtés est forcément une limite
        return 1;
    }
    return alignment;
}

int Direction::getBotRight(Square& square, int boardSize,
    std::vector<std::vector<Square>>& board, int& browsed)
{
    int alignment = 1;
    int maxBrowse = 4;
    browsed = 1;
    int xMax = boardSize - 1;
    int yMax = boardSize - 1;
    int x = square.x + 1;
    int y = square.y + 1;

    while (x <= xMax && y <= yMax && maxBrowse > 0) {
        if (board[y][x].content == square.content) {
            alignment += 1;
        } else if (board[y][x].content != EMPTY) {
            if (alignment < 5 && opposingStoneOrLimitInOppositeDirection(square.x, square.y, boardSize, board[square.y][square.x].content, board, MAX_ALIGNEMENT - browsed, -1, -1)) {
                return 1;
            }
            return alignment;
        }
        maxBrowse -= 1;
        browsed += 1;
        x += 1;
        y += 1;
    }
    if ((x > xMax || y > yMax) && alignment < 5 && opposingStoneOrLimitInOppositeDirection(square.x, square.y, boardSize, board[square.y][square.x].content, board, MAX_ALIGNEMENT - browsed, -1, -1)) {
        return 1;
    }
    return alignment;
}

int Direction::getBot(Square& square, int boardSize,
    std::vector<std::vector<Square>>& board, int& browsed)
{
    int alignment = 1;
    int maxBrowse = 4;
    browsed = 1;
    int yMax = boardSize - 1;
    int x = square.x;
    int y = square.y + 1;

    while (y <= yMax && maxBrowse > 0) {
        if (board[y][x].content == square.content) {
            alignment += 1;
        } else if (board[y][x].content != EMPTY) {
            if (alignment < 5 && opposingStoneOrLimitInOppositeDirection(square.x, square.y, boardSize, board[square.y][square.x].content, board, MAX_ALIGNEMENT - browsed, 0, -1)) {
                return 1;
            }
            return alignment;
        }
        maxBrowse -= 1;
        browsed += 1;
        y += 1;
    }
    if (y > yMax && alignment < 5 && opposingStoneOrLimitInOppositeDirection(square.x, square.y, boardSize, board[square.y][square.x].content, board, MAX_ALIGNEMENT - browsed, 0, -1)) {
        return 1;
    }
    return alignment;
}

int Direction::getBotLeft(Square& square, int boardSize,
    std::vector<std::vector<Square>>& board, int& browsed)
{
    int alignment = 1;
    int maxBrowse = 4;
    browsed = 1;
    int xMax = boardSize - 1;
    int yMax = boardSize - 1;
    int x = square.x - 1;
    int y = square.y + 1;

    while (x >= MIN_X && y <= yMax && maxBrowse > 0) {
        if (board[y][x].content == square.content) {
            alignment += 1;
        } else if (board[y][x].content != EMPTY) {
            if (alignment < 5 && opposingStoneOrLimitInOppositeDirection(square.x, square.y, boardSize, board[square.y][square.x].content, board, MAX_ALIGNEMENT - browsed, 1, -1)) {
                return 1;
            }
            return alignment;
        }
        maxBrowse -= 1;
        browsed += 1;
        x -= 1;
        y += 1;
    }
    if ((x < MIN_X || y > yMax) && alignment < 5 && opposingStoneOrLimitInOppositeDirection(square.x, square.y, boardSize, board[square.y][square.x].content, board, MAX_ALIGNEMENT - browsed, 1, -1)) {
        return 1;
    }
    return alignment;
}

int Direction::getLeft(Square& square, int boardSize,
    std::vector<std::vector<Square>>& board, int& browsed)
{
    int alignment = 1;
    int maxBrowse = 4;
    browsed = 1;
    int xMax = boardSize - 1;
    int x = square.x - 1;
    int y = square.y;

    while (x >= MIN_X && maxBrowse > 0) {
        if (board[y][x].content == square.content) {
            alignment += 1;
        } else if (board[y][x].content != EMPTY) {
            if (alignment < 5 && opposingStoneOrLimitInOppositeDirection(square.x, square.y, boardSize, board[square.y][square.x].content, board, MAX_ALIGNEMENT - browsed, 1, 0)) {
                return 1;
            }
            return alignment;
        }
        maxBrowse -= 1;
        browsed += 1;
        x -= 1;
    }
    if (x < MIN_X && alignment < 5 && opposingStoneOrLimitInOppositeDirection(square.x, square.y, boardSize, board[square.y][square.x].content, board, MAX_ALIGNEMENT - browsed, 1, 0)) {
        return 1;
    }
    return alignment;
}

int Direction::getTopLeft(Square& square, int boardSize,
    std::vector<std::vector<Square>>& board, int& browsed)
{
    int alignment = 1;
    int maxBrowse = 4;
    browsed = 1;
    int xMax = boardSize - 1;
    int yMax = boardSize - 1;
    int x = square.x - 1;
    int y = square.y - 1;

    while (x >= MIN_X && y >= MIN_Y && maxBrowse > 0) {
        if (board[y][x].content == square.content) {
            alignment += 1;
        } else if (board[y][x].content != EMPTY) {
            if (alignment < 5 && opposingStoneOrLimitInOppositeDirection(square.x, square.y, boardSize, board[square.y][square.x].content, board, MAX_ALIGNEMENT - browsed, 1, 1)) {
                return 1;
            }
            return alignment;
        }
        maxBrowse -= 1;
        browsed += 1;
        x -= 1;
        y -= 1;
    }
    if ((x < MIN_X || y < MIN_Y) && alignment < 5 && opposingStoneOrLimitInOppositeDirection(square.x, square.y, boardSize, board[square.y][square.x].content, board, MAX_ALIGNEMENT - browsed, 1, 1)) {
        return 1;
    }
    return alignment;
}

int Direction::getTop(Square& square, int boardSize,
    std::vector<std::vector<Square>>& board, int& browsed)
{
    int alignment = 1;
    int maxBrowse = 4;
    browsed = 1;
    int yMax = boardSize - 1;
    int x = square.x;
    int y = square.y - 1;

    while (y >= MIN_Y && maxBrowse > 0) {
        if (board[y][x].content == square.content) {
            alignment += 1;
        } else if (board[y][x].content != EMPTY) {
            if (alignment < 5 && opposingStoneOrLimitInOppositeDirection(square.x, square.y, boardSize, board[square.y][square.x].content, board, MAX_ALIGNEMENT - browsed, 0, 1)) {
                return 1;
            }
            return alignment;
        }
        maxBrowse -= 1;
        browsed += 1;
        y -= 1;
    }
    if (y < MIN_Y && alignment < 5 && opposingStoneOrLimitInOppositeDirection(square.x, square.y, boardSize, board[square.y][square.x].content, board, MAX_ALIGNEMENT - browsed, 0, 1)) {
        return 1;
    }
    return alignment;
}

int Direction::getTopRight(Square& square, int boardSize,
    std::vector<std::vector<Square>>& board, int& browsed)
{
    int alignment = 1;
    int maxBrowse = 4;
    browsed = 1;
    int xMax = boardSize - 1;
    int yMax = boardSize - 1;
    int x = square.x + 1;
    int y = square.y - 1;

    while (x <= xMax && y >= MIN_Y && maxBrowse > 0) {
        if (board[y][x].content == square.content) {
            alignment += 1;
        } else if (board[y][x].content != EMPTY) {
            if (alignment < 5 && opposingStoneOrLimitInOppositeDirection(square.x, square.y, boardSize, board[square.y][square.x].content, board, MAX_ALIGNEMENT - browsed, -1, 1)) {
                return 1;
            }
            return alignment;
        }
        maxBrowse -= 1;
        browsed += 1;
        x += 1;
        y -= 1;
    }
    if ((x > xMax || y < MIN_Y) && alignment < 5 && opposingStoneOrLimitInOppositeDirection(square.x, square.y, boardSize, board[square.y][square.x].content, board, MAX_ALIGNEMENT - browsed, -1, 1)) {
        return 1;
    }
    return alignment;
}
