#include "Command.hpp"

void Command::start(enum Transfer transfer, Map& map)
{
    if (transfer == ANSWER) {
        int map_size = map.getSize();
        if (map_size < MIN_SIZE_MAP || map_size > MAX_SIZE_MAP) {
            _ai.send("ERROR message - invalid map size");
            return;
        }
        _ai.send("OK");
    }
}

void Command::begin(enum Transfer transfer, Map& map)
{
    if (transfer == RECEIVE) {
        _name = BEGIN;
    } else if (transfer == ANSWER) {
        _ai.play(map);
    }
}

void Command::turn(enum Transfer transfer, Map& map, std::string coords)
{
    if (transfer == RECEIVE && coords != "") {
        _name = TURN;
        std::vector<std::string> numbers = stringToVector(coords, ",");
        if (numbers.size() == 2) {
            int x = stringToINT(numbers[0]);
            int y = stringToINT(numbers[1]);
            Square tmp = map.getSquareFromXY(x, y);
            if (tmp.content == EMPTY) {
                map._board[y][x].content = OPPONENT_STONE;
            }
        }
    } else if (transfer == ANSWER) {
        _ai.play(map);
    }
}

void Command::board(enum Transfer transfer, Map& map)
{
    if (transfer == RECEIVE) {
        _name = BOARD;
        map._board = {};
        map.setBoard();
        std::string input;
        std::getline(std::cin, input);
        while (input != "DONE") {
            std::vector<std::string> words = stringToVector(input, ",");
            int x = stringToINT(words[0]);
            int y = stringToINT(words[1]);
            int content = stringToINT(words[2]);
            Square square = { x, y, (enum Content)content };
            map._board[y][x] = square;
            std::getline(std::cin, input);
        }
    } else if (transfer == ANSWER) {
        _ai.play(map);
    }
}

void Command::info(enum Transfer transfer, std::string key, int value)
{
    if (transfer == RECEIVE) {
        _name = INFO;
    }
    // Expected answer: none
}

void Command::end(enum Transfer transfer, Map& map)
{
    if (transfer == RECEIVE) {
        int boardSize = map.getSize();
        for (int y = 0; y < boardSize; y++) {
            std::string line = "";
            for (int x = 0; x < boardSize; x++) {
                if (map._board[y][x].content == EMPTY) {
                    line += std::to_string(x);
                    if (x < 10) {
                        line += std::to_string(x);
                    }
                } else if (map._board[y][x].content == OWN_STONE) {
                    line += "<>";
                } else {
                    line += "/\\";
                }
            }
            line += "|";
            _myfile << line << std::endl;
        }
        _name = END;
    }
    // Expected answer: none
}

void Command::about(enum Transfer transfer)
{
    if (transfer == RECEIVE) {
        _name = ABOUT;
    } else if (transfer == ANSWER) {
        std::string response = "name=\"BigBrain\", version=\"1.0\", author=\"MariusNWK\", country=\"FRA\"";
        _ai.send(response);
    }
}

std::string Command::receive(Map& map)
{
    return _ai.receive();
}
