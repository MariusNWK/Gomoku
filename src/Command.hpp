#pragma once

#include "AI.hpp"
#include "useful.hpp"

enum Transfer {
    RECEIVE,
    ANSWER
};

enum Name {
    START,
    BEGIN,
    TURN,
    BOARD,
    INFO,
    END,
    ABOUT
};

class Command {
public:
    Command()
    {
        _path = MY_PATH;
        _myfile.open(_path + "final_map.txt", std::ofstream::out | std::ofstream::trunc);
        _myfile.close();
        _myfile.open(_path + "final_map.txt", std::fstream::out | std::fstream::app);
    }
    ~Command() { }
    void start(enum Transfer transfer, Map& map);
    void begin(enum Transfer transfer, Map& map);
    void turn(enum Transfer transfer, Map& map, std::string coords = "");
    void board(enum Transfer transfer, Map& map);
    void info(enum Transfer transfer, std::string key = "", int value = 0);
    void end(enum Transfer transfer, Map& map);
    void about(enum Transfer transfer);

    std::string receive(Map& map);

    enum Name _name;

protected:
private:
    AI _ai;
    std::string _path = "";
    std::ofstream _myfile;
};
