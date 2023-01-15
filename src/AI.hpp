#pragma once

#include "Tree.hpp"

class AI {
public:
    AI()
        : _path("")
    {
        _path = MY_PATH;
        _myfile.open(_path + "debug.txt", std::ofstream::out | std::ofstream::trunc);
        _myfile.close();
        _myfile.open(_path + "debug.txt", std::fstream::out | std::fstream::app);
    }
    ~AI()
    {
        _myfile.close();
    }
    void play(Map& map);
    void send(std::string output);
    std::string receive(void);

    std::ofstream _myfile;

protected:
private:
    std::string _path;
    Tree _tree;
};
