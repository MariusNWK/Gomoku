#include "Tree.hpp"

bool Tree::isSquareAlreadyRelevant(int x, int y, std::vector<std::pair<int, int>>& relevantSquares)
{
    for (std::pair<int, int> square : relevantSquares) {
        if (square.first == x && square.second == y) {
            return true;
        }
    }
    return false;
}

void Tree::getSquaresAround(std::vector<std::vector<Square>>& board, Square square,
    std::vector<std::pair<int, int>>& relevantSquares, int boardSize)
{
    int x = square.x;
    int y = square.y;
    int range = RANGE;

    while (x > 0 && range > 0) {
        x -= 1;
        range -= 1;
    }
    range = RANGE;
    while (y > 0 && range > 0) {
        y -= 1;
        range -= 1;
    }

    int xMax = square.x + RANGE;
    int yMax = square.y + RANGE;

    if (xMax > (boardSize - 1)) {
        xMax = boardSize - 1;
    }
    if (yMax > (boardSize - 1)) {
        yMax = boardSize - 1;
    }

    int xMin = x;

    while (y <= yMax) {
        x = xMin;
        while (x <= xMax) {
            if (!isSquareAlreadyRelevant(x, y, relevantSquares) && board[y][x].content == EMPTY) {
                relevantSquares.push_back({ x, y });
            }
            x += 1;
        }
        y += 1;
    }
}

bool Tree::crossCheck(std::vector<std::vector<Square>> simulatedBoard, int boardSize,
    int x, int y, int alignment)
{
    int browsed = 1;
    int browse = 1;

    enum Content content = simulatedBoard[y][x].content;

    Coords right = {x + 2, y};
    Coords botright = {x + 2, y + 2};
    Coords bot = {x, y + 2};
    Coords botleft = {x - 2, y + 2};
    Coords left = {x - 2, y};
    Coords topleft = {x - 2, y - 2};
    Coords top = {x, y - 2};
    Coords topright = {x + 2, y - 2};

    _eval.setBoardSize(boardSize);
    if (_eval.chooseBestDirection(simulatedBoard[y][x], simulatedBoard, alignment, browse) != NONE) {
        return true;
    }
    if ((right.x < boardSize && simulatedBoard[right.y][right.x].content == content && _direction.getLeft(simulatedBoard[right.y][right.x], boardSize, simulatedBoard, browsed) == alignment) ||
        ((right.x - 1) < boardSize && simulatedBoard[right.y][right.x - 1].content == content && _direction.getLeft(simulatedBoard[right.y][right.x - 1], boardSize, simulatedBoard, browsed) == alignment)) {
        return true;
    }
    if ((botright.x < boardSize && botright.y < boardSize && simulatedBoard[botright.y][botright.x].content == content && _direction.getTopLeft(simulatedBoard[botright.y][botright.x], boardSize, simulatedBoard, browsed) == alignment) ||
        ((botright.x - 1) < boardSize && (botright.y - 1) < boardSize && simulatedBoard[botright.y - 1][botright.x - 1].content == content && _direction.getTopLeft(simulatedBoard[botright.y - 1][botright.x - 1], boardSize, simulatedBoard, browsed) == alignment)) {
        return true;
    }
    if ((bot.y < boardSize && simulatedBoard[bot.y][bot.x].content == content && _direction.getTop(simulatedBoard[bot.y][bot.x], boardSize, simulatedBoard, browsed) == alignment) ||
        ((bot.y - 1) < boardSize && simulatedBoard[bot.y - 1][bot.x].content == content && _direction.getTop(simulatedBoard[bot.y - 1][bot.x], boardSize, simulatedBoard, browsed) == alignment)) {
        return true;
    }
    if ((botleft.x >= MIN_X && botleft.y < boardSize && simulatedBoard[botleft.y][botleft.x].content == content && _direction.getTopRight(simulatedBoard[botleft.y][botleft.x], boardSize, simulatedBoard, browsed) == alignment) ||
        ((botleft.x + 1) >= MIN_X && (botleft.y - 1) < boardSize && simulatedBoard[botleft.y - 1][botleft.x + 1].content == content && _direction.getTopRight(simulatedBoard[botleft.y - 1][botleft.x + 1], boardSize, simulatedBoard, browsed) == alignment)) {
        return true;
    }
    if ((left.x >= MIN_X && simulatedBoard[left.y][left.x].content == content && _direction.getRight(simulatedBoard[left.y][left.x], boardSize, simulatedBoard, browsed) == alignment) ||
        ((left.x + 1) >= MIN_X && simulatedBoard[left.y][left.x + 1].content == content && _direction.getRight(simulatedBoard[left.y][left.x + 1], boardSize, simulatedBoard, browsed) == alignment)) {
        return true;
    }
    if ((topleft.x >= MIN_X && topleft.y >= MIN_Y && simulatedBoard[topleft.y][topleft.x].content == content && _direction.getBotRight(simulatedBoard[topleft.y][topleft.x], boardSize, simulatedBoard, browsed) == alignment) ||
        ((topleft.x + 1) >= MIN_X && (topleft.y + 1) >= MIN_Y && simulatedBoard[topleft.y + 1][topleft.x + 1].content == content && _direction.getBotRight(simulatedBoard[topleft.y + 1][topleft.x + 1], boardSize, simulatedBoard, browsed) == alignment)) {
        return true;
    }
    if ((top.y >= MIN_Y && simulatedBoard[top.y][top.x].content == content && _direction.getBot(simulatedBoard[top.y][top.x], boardSize, simulatedBoard, browsed) == alignment) ||
        ((top.y + 1) >= MIN_Y && simulatedBoard[top.y + 1][top.x].content == content && _direction.getBot(simulatedBoard[top.y + 1][top.x], boardSize, simulatedBoard, browsed) == alignment)) {
        return true;
    }
    if ((topright.x < boardSize && topright.y >= MIN_Y && simulatedBoard[topright.y][topright.x].content == content && _direction.getBotLeft(simulatedBoard[topright.y][topright.x], boardSize, simulatedBoard, browsed) == alignment) ||
        ((topright.x - 1) < boardSize && (topright.y + 1) >= MIN_Y && simulatedBoard[topright.y + 1][topright.x - 1].content == content && _direction.getBotLeft(simulatedBoard[topright.y + 1][topright.x - 1], boardSize, simulatedBoard, browsed) == alignment)) {
        return true;
    }
    return false;
}

void Tree::addSquareOfAlignment(std::vector<std::vector<Square>>& board, int boardSize,
std::vector<std::pair<int, int>>& relevantSquares, std::vector<std::pair<int, int>>& theBest, int alignment)
{
    std::vector<std::vector<Square>> simulatedBoard;

    for (std::pair<int, int> square : relevantSquares) {
        simulatedBoard = childBoard(board, square, OWN_STONE);
        if (crossCheck(simulatedBoard, boardSize, square.first, square.second, alignment)) {
            theBest.push_back(square);
        } else {
            simulatedBoard = childBoard(board, square, OPPONENT_STONE);
            if (crossCheck(simulatedBoard, boardSize, square.first, square.second, alignment)) {
                theBest.push_back(square);
            }
        }
    }
}

std::vector<std::pair<int, int>> Tree::getRelevantSquares(std::vector<std::vector<Square>>& board, int boardSize)
{
    std::vector<std::pair<int, int>> relevantSquares;

    for (int y = 0; y < boardSize; y++) {
        for (int x = 0; x < boardSize; x++) {
            if (board[y][x].content != EMPTY) {
                getSquaresAround(board, board[y][x], relevantSquares, boardSize);
            }
        }
    }

    if (relevantSquares.size() == 0) {
        relevantSquares.push_back({ boardSize / 2, boardSize / 2 });
        return relevantSquares;
    }

    std::vector<std::pair<int, int>> theBest;

    for (int alignment = 5; alignment >= 3; alignment -= 1) {
        addSquareOfAlignment(board, boardSize, relevantSquares, theBest, alignment);
    }

    if (theBest.size() < 20) {
        addSquareOfAlignment(board, boardSize, relevantSquares, theBest, 2);
    }

    int theBestSize = static_cast<int>(theBest.size());
    if (theBestSize < 20) {
        for (std::pair<int, int> square : relevantSquares) {
            if (!isSquareAlreadyRelevant(square.first, square.second, theBest)) {
                theBest.push_back({ square.first, square.second });
                if (++theBestSize >= 20) {
                    break;
                }
            }
        }
    }

    return theBest;
}

bool Tree::isGameOver(int boardSize, std::vector<std::vector<Square>>& board)
{
    int browsed = 1;

    for (int y = 0; y < boardSize; y++) {
        for (int x = 0; x < boardSize; x++) {
            if (board[y][x].content != EMPTY) {
                if (_direction.getRight(board[y][x], boardSize, board, browsed) == 5) {
                    return true;
                }
                if (_direction.getBotRight(board[y][x], boardSize, board, browsed) == 5) {
                    return true;
                }
                if (_direction.getBot(board[y][x], boardSize, board, browsed) == 5) {
                    return true;
                }
                if (_direction.getBotLeft(board[y][x], boardSize, board, browsed) == 5) {
                    return true;
                }
                if (_direction.getLeft(board[y][x], boardSize, board, browsed) == 5) {
                    return true;
                }
                if (_direction.getTopLeft(board[y][x], boardSize, board, browsed) == 5) {
                    return true;
                }
                if (_direction.getTop(board[y][x], boardSize, board, browsed) == 5) {
                    return true;
                }
                if (_direction.getTopRight(board[y][x], boardSize, board, browsed) == 5) {
                    return true;
                }
            }
        }
    }
    return false;
}

std::vector<std::vector<Square>> Tree::childBoard(std::vector<std::vector<Square>> board,
    std::pair<int, int> coord, enum Content stone)
{
    board[coord.second][coord.first].content = stone;
    return board;
}

Eval Tree::minMax(int boardSize, std::vector<std::vector<Square>> board,
    enum Content stone, int depth, int curDepth, int alpha, int beta, int x, int y, int xPlay, int yPlay)
{
    if (curDepth <= 0 || isGameOver(boardSize, board)) {
        _nb_eval += 1;
        return { xPlay, yPlay, _eval.getFromBoard(boardSize, board, OWN_STONE, stone) * (curDepth + 1) };
    }

    Eval eval;

    if (stone == OWN_STONE) {
        Eval maxEval = { -1, -1, -100000000 };
        for (std::pair<int, int> coord : getRelevantSquares(board, boardSize)) {
            if (curDepth == depth) {
                eval = minMax(boardSize, childBoard(board, coord, stone), OPPONENT_STONE, depth, curDepth - 1, alpha, beta, coord.first, coord.second, coord.first, coord.second);
            } else {
                eval = minMax(boardSize, childBoard(board, coord, stone), OPPONENT_STONE, depth, curDepth - 1, alpha, beta, coord.first, coord.second, xPlay, yPlay);
            }
            maxEval = getMaxEval(maxEval, eval);
            alpha = getMax(alpha, eval.value);
            if (beta <= alpha) {
                break;
            }
        }
        return maxEval;
    } else {
        Eval minEval = { -1, -1, 100000000 };
        for (std::pair<int, int> coord : getRelevantSquares(board, boardSize)) {
            eval = minMax(boardSize, childBoard(board, coord, stone), OWN_STONE, depth, curDepth - 1, alpha, beta, coord.first, coord.second, xPlay, yPlay);
            minEval = getMinEval(minEval, eval);
            beta = getMin(beta, eval.value);
            if (beta <= alpha) {
                break;
            }
        }
        return minEval;
    }
}
