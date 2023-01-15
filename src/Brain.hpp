#pragma once

#include <iostream>

#include "Command.hpp"

class Brain {
public:
    Brain() { }
    ~Brain() { }
    void run(int size_map);

protected:
private:
    void answer(void);
    void receive(void);
    void handleCommand(void);

    std::string _input;
    Map _map;
    Command _command;
};
