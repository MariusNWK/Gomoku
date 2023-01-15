#pragma once

#include "../path.hpp"
#include "Direction.hpp"

const int VICTORY = 5000000;
const int ONE_TO_VICTORY = 50000;

typedef struct Score {
    int own;
    int opponent;
} Score;

class Evaluation {
public:
    Evaluation()
        : _path("")
    {
        _path = MY_PATH;
        _myfile.open(_path + "mapAndScore.txt", std::ofstream::out | std::ofstream::trunc);
        _myfile.close();
        _myfile.open(_path + "mapAndScore.txt", std::fstream::out | std::fstream::app);
    }
    ~Evaluation()
    {
        _myfile.close();
    }
    int getFromBoard(int boardSize, std::vector<std::vector<Square>>& board, enum Content stone, enum Content stoneToBePlayed);
    enum AlignmentType chooseBestDirection(Square& square, std::vector<std::vector<Square>>& board, int alignment, int& browse);
    void setBoardSize(int boardSize);

protected:
private:
    Direction _direction;
    std::ofstream _myfile;
    std::string _path;
    int _fourAlignmentsNbrOwn;
    int _fourAlignmentsNbrOpponent;
    int _boardSize;
    enum Content _stoneToBePlayed;

    bool isGreyStone(int x, int y, std::vector<Square>& greyStones);
    bool isEmptySquare(int x, int y, std::vector<std::vector<Square>>& board);
    void lookForCombinations(int x, int y, std::vector<std::vector<Square>>& board, Score& score, std::vector<Square>& greyStones, int alignment);
    bool grayStonesFromAlignType(int x, int y, std::vector<std::vector<Square>>& board, std::vector<Square>& greyStones, enum AlignmentType alignType, int alignment, int browse);
    bool grayStonesFromDirection(int x, int y, std::vector<std::vector<Square>>& board, std::vector<Square>& greyStones, int xAdd, int yAdd, int alignment, int browse);
    bool sameStoneInOppositeDirection(int x, int y, enum Content stoneContent, std::vector<std::vector<Square>>& board, int range, int xAdd, int yAdd);
    int addPoints(int alignment, int x, int y, std::vector<std::vector<Square>>& board, enum AlignmentType alignType, enum Content content);
    bool isOneToVictory(int x, int y, std::vector<std::vector<Square>> board, enum AlignmentType alignType, enum Content content);
    bool areAlignedAndEmptyAround(int x, int y, std::vector<std::vector<Square>>& board, int xAdd, int yAdd, enum Content content);
    bool isOneToOneToVictory(int x, int y, std::vector<std::vector<Square>> board, enum AlignmentType alignType, enum Content content);
    std::vector<std::vector<Square>> simulatedBoard(int x, int y, enum Content content, std::vector<std::vector<Square>> board);
    bool isThereAWinner(Score& score);
    int getScoreFromStone(Score& score, enum Content stone);
    int getScore(Score& score, enum Content stone);
    void displayMap(std::vector<std::vector<Square>>& board);
};
