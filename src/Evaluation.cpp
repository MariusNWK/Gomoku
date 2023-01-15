#include "Evaluation.hpp"

void Evaluation::setBoardSize(int boardSize)
{
    _boardSize = boardSize;
}

bool Evaluation::sameStoneInOppositeDirection(int x, int y,
    enum Content stoneContent, std::vector<std::vector<Square>>& board, int range,
    int xAdd, int yAdd)
{
    int xMax = _boardSize - 1;
    int yMax = _boardSize - 1;

    x += xAdd;
    y += yAdd;
    while (range > 0) {
        if (x < MIN_X || x > xMax) {
            return false;
        }
        if (y < MIN_Y || y > yMax) {
            return false;
        }
        if (stoneContent == board[y][x].content) {
            return true;
        } else if (board[y][x].content != EMPTY) {
            return false;
        }
        x += xAdd;
        y += yAdd;
        range -= 1;
    }
    return false;
}

bool Evaluation::grayStonesFromDirection(int x, int y,
    std::vector<std::vector<Square>>& board, std::vector<Square>& greyStones,
    int xAdd, int yAdd, int alignment, int browse)
{
    enum Content content = board[y][x].content;
    int xLimit;
    int yLimit;

    if (xAdd >= 0)
        xLimit = _boardSize - 1;
    else
        xLimit = MIN_X;
    if (yAdd >= 0)
        yLimit = _boardSize - 1;
    else
        yLimit = MIN_Y;

    if (alignment > 1 && sameStoneInOppositeDirection(x, y, board[y][x].content,
            board, MAX_ALIGNEMENT - browse, -xAdd, -yAdd)) {
        // Pour éviter de griser une pierre encerclée de deux autres pierres du même type
        // comme ça les pierres ne sont grisées que lorsqu'en ressort le meilleur alignement
        // Pas besoin de gérer cas où alignement est 5 car ça va direct return false
        return false;
    }
    while (alignment > 0 && ((xAdd >= 0 && x <= xLimit) || (xAdd < 0 && x >= xLimit)) && ((yAdd >= 0 && y <= yLimit) || (yAdd < 0 && y >= yLimit))) {
        if (board[y][x].content == content) {
            greyStones.push_back(board[y][x]);
            alignment -= 1;
        }
        x += xAdd;
        y += yAdd;
    }
    return true;
}

bool Evaluation::grayStonesFromAlignType(int x, int y,
    std::vector<std::vector<Square>>& board, std::vector<Square>& greyStones,
    enum AlignmentType alignType, int alignment, int browse)
{
    switch (alignType) {
    case RIGHT:
        return grayStonesFromDirection(x, y, board, greyStones, 1, 0, alignment, browse);
    case BOTRIGHT:
        return grayStonesFromDirection(x, y, board, greyStones, 1, 1, alignment, browse);
    case BOT:
        return grayStonesFromDirection(x, y, board, greyStones, 0, 1, alignment, browse);
    case BOTLEFT:
        return grayStonesFromDirection(x, y, board, greyStones, -1, 1, alignment, browse);
    case LEFT:
        return grayStonesFromDirection(x, y, board, greyStones, -1, 0, alignment, browse);
    case TOPLEFT:
        return grayStonesFromDirection(x, y, board, greyStones, -1, -1, alignment, browse);
    case TOP:
        return grayStonesFromDirection(x, y, board, greyStones, 0, -1, alignment, browse);
    case TOPRIGHT:
        return grayStonesFromDirection(x, y, board, greyStones, 1, -1, alignment, browse);
    default:
        break;
    }
    return false;
}

enum AlignmentType Evaluation::chooseBestDirection(Square& square,
    std::vector<std::vector<Square>>& board, int alignment, int& browse)
{
    int browsed = 1;

    if (_direction.getRight(square, _boardSize, board, browsed) == alignment) {
        browse = browsed;
        return RIGHT;
    }
    if (_direction.getBotRight(square, _boardSize, board, browsed) == alignment) {
        browse = browsed;
        return BOTRIGHT;
    }
    if (_direction.getBot(square, _boardSize, board, browsed) == alignment) {
        browse = browsed;
        return BOT;
    }
    if (_direction.getBotLeft(square, _boardSize, board, browsed) == alignment) {
        browse = browsed;
        return BOTLEFT;
    }
    if (_direction.getLeft(square, _boardSize, board, browsed) == alignment) {
        browse = browsed;
        return LEFT;
    }
    if (_direction.getTopLeft(square, _boardSize, board, browsed) == alignment) {
        browse = browsed;
        return TOPLEFT;
    }
    if (_direction.getTop(square, _boardSize, board, browsed) == alignment) {
        browse = browsed;
        return TOP;
    }
    if (_direction.getTopRight(square, _boardSize, board, browsed) == alignment) {
        browse = browsed;
        return TOPRIGHT;
    }

    return NONE;
}

bool Evaluation::areAlignedAndEmptyAround(int x, int y,
std::vector<std::vector<Square>>& board, int xAdd, int yAdd, enum Content content)
{
    return (
        board[y][x].content == content &&
        ((x + (xAdd * 4)) < _boardSize) && ((x + (xAdd * 4)) >= MIN_X) &&
        ((y + (yAdd * 4)) < _boardSize) && ((y + (yAdd * 4)) >= MIN_Y) &&
        ((x - xAdd) < _boardSize) && ((x - xAdd) >= MIN_X) &&
        ((y - yAdd) < _boardSize) && ((y - yAdd) >= MIN_Y) &&
        board[y + yAdd][x + xAdd].content == content &&
        board[y + (yAdd * 2)][x + (xAdd * 2)].content == content &&
        board[y + (yAdd * 3)][x + (xAdd * 3)].content == content &&
        board[y + (yAdd * 4)][x + (xAdd * 4)].content == EMPTY &&
        board[y - yAdd][x - xAdd].content == EMPTY
    );
}

bool Evaluation::isOneToVictory(int x, int y,
    std::vector<std::vector<Square>> board, enum AlignmentType alignType, enum Content content)
{
    switch (alignType) {
    case RIGHT:
        return areAlignedAndEmptyAround(x, y, board, 1, 0, content);
    case BOTRIGHT:
        return areAlignedAndEmptyAround(x, y, board, 1, 1, content);
    case BOT:
        return areAlignedAndEmptyAround(x, y, board, 0, 1, content);
    case BOTLEFT:
        return areAlignedAndEmptyAround(x, y, board, -1, 1, content);
    case LEFT:
        return areAlignedAndEmptyAround(x, y, board, -1, 0, content);
    case TOPLEFT:
        return areAlignedAndEmptyAround(x, y, board, -1, -1, content);
    case TOP:
        return areAlignedAndEmptyAround(x, y, board, 0, -1, content);
    case TOPRIGHT:
        return areAlignedAndEmptyAround(x, y, board, 1, -1, content);
    default:
        break;
    }
    return false;
}

std::vector<std::vector<Square>> Evaluation::simulatedBoard(int x, int y, enum Content content,
    std::vector<std::vector<Square>> board)
{
    board[y][x].content = content;
    return board;
}

bool Evaluation::isOneToOneToVictory(int x, int y,
    std::vector<std::vector<Square>> board, enum AlignmentType alignType, enum Content content)
{
    switch (alignType) {
    case RIGHT:
        // OXXXOO OU OOXXXO avec O -> EMPTY et X -> STONE
        return (board[y][x].content == content && board[y][x + 1].content == content && board[y][x + 2].content == content &&
        (((x + 3) < _boardSize && board[y][x + 3].content == EMPTY && isOneToVictory(x, y, simulatedBoard(x + 3, y, content, board), alignType, content)) ||
        ((x - 1) >= MIN_X && board[y][x - 1].content == EMPTY && isOneToVictory(x - 1, y, simulatedBoard(x - 1, y, content, board), alignType, content))))
        || // OXOXXO OU OXXOXO
        ((board[y][x].content == content && board[y][x + 1].content == EMPTY && board[y][x + 2].content == content && board[y][x + 3].content == content && isOneToVictory(x, y, simulatedBoard(x + 1, y, content, board), alignType, content)) ||
        (board[y][x].content == content && board[y][x + 1].content == content && board[y][x + 2].content == EMPTY && board[y][x + 3].content == content && isOneToVictory(x, y, simulatedBoard(x + 2, y, content, board), alignType, content)));
    case BOTRIGHT:
        return (board[y][x].content == content && board[y + 1][x + 1].content == content && board[y + 2][x + 2].content == content &&
        (((x + 3) < _boardSize && (y + 3) < _boardSize && board[y + 3][x + 3].content == EMPTY && isOneToVictory(x, y, simulatedBoard(x + 3, y + 3, content, board), alignType, content)) ||
        ((x - 1) >= MIN_X && (y - 1) >= MIN_Y && board[y - 1][x - 1].content == EMPTY && isOneToVictory(x - 1, y - 1, simulatedBoard(x - 1, y - 1, content, board), alignType, content))))
        ||
        ((board[y][x].content == content && board[y + 1][x + 1].content == EMPTY && board[y + 2][x + 2].content == content && board[y + 3][x + 3].content == content && isOneToVictory(x, y, simulatedBoard(x + 1, y + 1, content, board), alignType, content)) ||
        (board[y][x].content == content && board[y + 1][x + 1].content == content && board[y + 2][x + 2].content == EMPTY && board[y + 3][x + 3].content == content && isOneToVictory(x, y, simulatedBoard(x + 2, y + 2, content, board), alignType, content)));
    case BOT:
        return (board[y][x].content == content && board[y + 1][x].content == content && board[y + 2][x].content == content &&
        (((y + 3) < _boardSize && board[y + 3][x].content == EMPTY && isOneToVictory(x, y, simulatedBoard(x, y + 3, content, board), alignType, content)) ||
        ((y - 1) >= MIN_Y && board[y - 1][x].content == EMPTY && isOneToVictory(x, y - 1, simulatedBoard(x, y - 1, content, board), alignType, content))))
        ||
        ((board[y][x].content == content && board[y + 1][x].content == EMPTY && board[y + 2][x].content == content && board[y + 3][x].content == content && isOneToVictory(x, y, simulatedBoard(x, y + 1, content, board), alignType, content)) ||
        (board[y][x].content == content && board[y + 1][x].content == content && board[y + 2][x].content == EMPTY && board[y + 3][x].content == content && isOneToVictory(x, y, simulatedBoard(x, y + 2, content, board), alignType, content)));
    case BOTLEFT:
        return (board[y][x].content == content && board[y + 1][x - 1].content == content && board[y + 2][x - 2].content == content &&
        (((x - 3) >= MIN_X && (y + 3) < _boardSize && board[y + 3][x - 3].content == EMPTY && isOneToVictory(x, y, simulatedBoard(x - 3, y + 3, content, board), alignType, content)) ||
        ((x + 1) < _boardSize && (y - 1) >= MIN_Y && board[y - 1][x + 1].content == EMPTY && isOneToVictory(x + 1, y - 1, simulatedBoard(x + 1, y - 1, content, board), alignType, content))))
        ||
        ((board[y][x].content == content && board[y + 1][x - 1].content == EMPTY && board[y + 2][x - 2].content == content && board[y + 3][x - 3].content == content && isOneToVictory(x, y, simulatedBoard(x - 1, y + 1, content, board), alignType, content)) ||
        (board[y][x].content == content && board[y + 1][x - 1].content == content && board[y + 2][x - 2].content == EMPTY && board[y + 3][x - 3].content == content && isOneToVictory(x, y, simulatedBoard(x - 2, y + 2, content, board), alignType, content)));
    case LEFT:
        return (board[y][x].content == content && board[y][x - 1].content == content && board[y][x - 2].content == content &&
        (((x - 3) >= MIN_X && board[y][x - 3].content == EMPTY && isOneToVictory(x, y, simulatedBoard(x - 3, y, content, board), alignType, content)) ||
        ((x + 1) < _boardSize && board[y][x + 1].content == EMPTY && isOneToVictory(x + 1, y, simulatedBoard(x + 1, y, content, board), alignType, content))))
        ||
        ((board[y][x].content == content && board[y][x - 1].content == EMPTY && board[y][x - 2].content == content && board[y][x - 3].content == content && isOneToVictory(x, y, simulatedBoard(x - 1, y, content, board), alignType, content)) ||
        (board[y][x].content == content && board[y][x - 1].content == content && board[y][x - 2].content == EMPTY && board[y][x - 3].content == content && isOneToVictory(x, y, simulatedBoard(x - 2, y, content, board), alignType, content)));
    case TOPLEFT:
        return (board[y][x].content == content && board[y - 1][x - 1].content == content && board[y - 2][x - 2].content == content &&
        (((x - 3) >= MIN_X && (y - 3) >= MIN_Y && board[y - 3][x - 3].content == EMPTY && isOneToVictory(x, y, simulatedBoard(x - 3, y - 3, content, board), alignType, content)) ||
        ((x + 1) < _boardSize && (y + 1) < _boardSize && board[y + 1][x + 1].content == EMPTY && isOneToVictory(x + 1, y + 1, simulatedBoard(x + 1, y + 1, content, board), alignType, content))))
        ||
        ((board[y][x].content == content && board[y - 1][x - 1].content == EMPTY && board[y - 2][x - 2].content == content && board[y - 3][x - 3].content == content && isOneToVictory(x, y, simulatedBoard(x - 1, y - 1, content, board), alignType, content)) ||
        (board[y][x].content == content && board[y - 1][x - 1].content == content && board[y - 2][x - 2].content == EMPTY && board[y - 3][x - 3].content == content && isOneToVictory(x, y, simulatedBoard(x - 2, y - 2, content, board), alignType, content)));
    case TOP:
        return (board[y][x].content == content && board[y - 1][x].content == content && board[y - 2][x].content == content &&
        (((y - 3) >= MIN_Y && board[y - 3][x].content == EMPTY && isOneToVictory(x, y, simulatedBoard(x, y - 3, content, board), alignType, content)) ||
        ((y + 1) < _boardSize && board[y + 1][x].content == EMPTY && isOneToVictory(x, y + 1, simulatedBoard(x, y + 1, content, board), alignType, content))))
        ||
        ((board[y][x].content == content && board[y - 1][x].content == EMPTY && board[y - 2][x].content == content && board[y - 3][x].content == content && isOneToVictory(x, y, simulatedBoard(x, y - 1, content, board), alignType, content)) ||
        (board[y][x].content == content && board[y - 1][x].content == content && board[y - 2][x].content == EMPTY && board[y - 3][x].content == content && isOneToVictory(x, y, simulatedBoard(x, y - 2, content, board), alignType, content)));
    case TOPRIGHT:
        return (board[y][x].content == content && board[y - 1][x + 1].content == content && board[y - 2][x + 2].content == content &&
        (((x + 3) < _boardSize && (y - 3) >= MIN_Y && board[y - 3][x + 3].content == EMPTY && isOneToVictory(x, y, simulatedBoard(x + 3, y - 3, content, board), alignType, content)) ||
        ((x - 1) >= MIN_X && (y + 1) < _boardSize && board[y + 1][x - 1].content == EMPTY && isOneToVictory(x - 1, y + 1, simulatedBoard(x - 1, y + 1, content, board), alignType, content))))
        ||
        ((board[y][x].content == content && board[y - 1][x + 1].content == EMPTY && board[y - 2][x + 2].content == content && board[y - 3][x + 3].content == content && isOneToVictory(x, y, simulatedBoard(x + 1, y - 1, content, board), alignType, content)) ||
        (board[y][x].content == content && board[y - 1][x + 1].content == content && board[y - 2][x + 2].content == EMPTY && board[y - 3][x + 3].content == content && isOneToVictory(x, y, simulatedBoard(x + 2, y - 2, content, board), alignType, content)));
    default:
        break;
    }
    return false;
}

int Evaluation::addPoints(int alignement, int x, int y,
    std::vector<std::vector<Square>>& board, enum AlignmentType alignType, enum Content content)
{
    switch (alignement) {
    case 1:
        return 1;
    case 2:
        return 2 * 2;
    case 3:
        if (isOneToOneToVictory(x, y, board, alignType, content)) {
            if (content == _stoneToBePlayed)
                return ONE_TO_VICTORY;
            else
                return 3 * 4;
        }
        return 3 * 3;
    case 4:
        if (content == _stoneToBePlayed)
            return VICTORY;
        if (content == OWN_STONE)
            _fourAlignmentsNbrOwn += 1;
        else
            _fourAlignmentsNbrOpponent += 1;
        if ((_fourAlignmentsNbrOwn > 1 && content == OWN_STONE) ||
            (_fourAlignmentsNbrOpponent > 1 && content == OPPONENT_STONE) ||
            isOneToVictory(x, y, board, alignType, content))
            return ONE_TO_VICTORY;
        return 4 * 4;
    case 5:
        return VICTORY;
    default:
        break;
    }
    return 0;
}

void Evaluation::lookForCombinations(int x, int y,
    std::vector<std::vector<Square>>& board, Score& score, std::vector<Square>& greyStones, int alignment)
{
    Square square = board[y][x];
    int browse = 1;

    enum AlignmentType alignType = chooseBestDirection(square, board, alignment, browse);

    if (alignType == NONE || !grayStonesFromAlignType(x, y, board, greyStones, alignType, alignment, browse)) {
        return;
    }

    // std::string stoneContent = board[y][x].content == OWN_STONE ? "OWN_STONE" : "OPPONENT_STONE";
    // std::string alignStr = alignType == RIGHT ? "RIGHT" : alignType == BOTRIGHT ? "BOTRIGHT" : alignType == BOT ? "BOT" : alignType == BOTLEFT ? "BOTLEFT" : alignType == LEFT ? "LEFT" : alignType == TOPLEFT ? "TOPLEFT" : alignType == TOP ? "TOP" : "TOPRIGHT";
    // _myfile << "Alignment of " << stoneContent << " (" << x << "," << y << ") : " << Alignment << " (align: " << alignStr << ")" << std::endl;
    // _myfile << "number of greyStones : " << greyStones.size() << std::endl;
    // _myfile << std::endl;

    if (square.content == OWN_STONE) {
        score.own += addPoints(alignment, x, y, board, alignType, square.content);
        return;
    }
    // square.content = OPPONENT_STONE
    score.opponent += addPoints(alignment, x, y, board, alignType, square.content);
}

bool Evaluation::isGreyStone(int x, int y, std::vector<Square>& greyStones)
{
    for (Square stone : greyStones) {
        if (stone.x == x && stone.y == y) {
            return true;
        }
    }
    return false;
}

bool Evaluation::isEmptySquare(int x, int y, std::vector<std::vector<Square>>& board)
{
    return board[y][x].content == EMPTY;
}

bool Evaluation::isThereAWinner(Score& score)
{
    if (score.own >= VICTORY || score.opponent >= VICTORY) {
        return true;
    }
    return false;
}

int Evaluation::getScoreFromStone(Score& score, enum Content stone)
{
    if (score.own >= VICTORY) {
        if (stone == OWN_STONE) {
            // _myfile << "score: " << score.own << std::endl;
            // _myfile << "--------------------" << std::endl;
            return score.own;
        }
        // _myfile << "score: " << -score.own << std::endl;
        // _myfile << "--------------------" << std::endl;
        return -score.own;
    }
    // score.opponent >= 100000
    if (stone == OPPONENT_STONE) {
        // _myfile << "score: " << score.opponent << std::endl;
        // _myfile << "--------------------" << std::endl;
        return score.opponent;
    }
    // _myfile << "score: " << -score.opponent << std::endl;
    // _myfile << "--------------------" << std::endl;
    return -score.opponent;
}

int Evaluation::getScore(Score& score, enum Content stone)
{
    int total = 0;

    if (stone == OWN_STONE) {
        total = score.own - score.opponent;
    } else {
        total = score.opponent - score.own;
    }
    // _myfile << "score: " << total << " (score.own: " << score.own << ", score.opponent: " << score.opponent << ")" << std::endl;
    // _myfile << "--------------------" << std::endl;
    return total;
}

void Evaluation::displayMap(std::vector<std::vector<Square>>& board)
{
    for (int y = 0; y < _boardSize; y++) {
        if (y < 10) {
            _myfile << std::to_string(y) + "-";
        } else {
            _myfile << std::to_string(y);
        }
    }
    _myfile << std::endl;
    for (int y = 0; y < _boardSize; y++) {
        std::string line = "";
        for (int x = 0; x < _boardSize; x++) {
            if (board[y][x].content == EMPTY) {
                line += "[]";
            } else if (board[y][x].content == OWN_STONE) {
                line += "<>";
            } else {
                line += "/\\";
            }
        }
        line += "|" + std::to_string(y);
        _myfile << line << std::endl;
    }
}

/**
 * @brief
 * @param board is the simulated board at the current node of the (min-max) tree.
 * @param stone is the type of stone of the player we want the evaluation :
 * - if @param stone is OWN_STONE, return the evaluation of the position for the Brain.
 * - if @param stone is OPPONENT_STONE, return the evaluation of the position for the opponent.
 */
int Evaluation::getFromBoard(int boardSize, std::vector<std::vector<Square>>& board, enum Content stone, enum Content stoneToBePlayed)
{
    std::vector<Square> greyStones; // stones already used

    Score score = { 0, 0 };

    _boardSize = boardSize;
    _stoneToBePlayed = stoneToBePlayed;

    for (int alignment = 5; alignment >= 1; alignment -= 1) {
        _fourAlignmentsNbrOwn = 0;
        _fourAlignmentsNbrOpponent = 0;
        for (int y = 0; y < boardSize; y++) {
            for (int x = 0; x < boardSize; x++) {
                if (!isEmptySquare(x, y, board) && !isGreyStone(x, y, greyStones)) {
                    lookForCombinations(x, y, board, score, greyStones, alignment);
                    if (isThereAWinner(score)) {
                        // displayMap(board);
                        return getScoreFromStone(score, stone);
                    }
                }
            }
        }
    }
    // displayMap(board);
    return getScore(score, stone);
}
