#include "Brain.hpp"

void Brain::run(int size_map)
{
    _command._name = START;
    _map.setSize(size_map);

    while (_command._name != END) {
        answer();
        receive();
        handleCommand();
    }
}

void Brain::handleCommand(void)
{
    std::vector<std::string> words = stringToVector(_input);

    if (words[0] == "BEGIN")
        return _command.begin(RECEIVE, _map);
    if (words[0] == "TURN")
        return _command.turn(RECEIVE, _map, words[1]);
    if (words[0] == "BOARD")
        return _command.board(RECEIVE, _map);
    if (words[0] == "INFO")
        return _command.info(RECEIVE, words[1], stringToINT(words[2]));
    if (words[0] == "END")
        return _command.end(RECEIVE, _map);
    if (words[0] == "ABOUT")
        return _command.about(RECEIVE);
}

void Brain::answer(void)
{
    switch (_command._name) {
    case START:
        _command.start(ANSWER, _map);
        break;
    case BEGIN:
        _command.begin(ANSWER, _map);
        break;
    case TURN:
        _command.turn(ANSWER, _map);
        break;
    case BOARD:
        _command.board(ANSWER, _map);
        break;
    case INFO:
        _command.info(ANSWER);
        break;
    case ABOUT:
        _command.about(ANSWER);
        break;
    default:
        break;
    }
}

void Brain::receive(void)
{
    _input = _command.receive(_map);
}
