#include "Brain.hpp"

int main(void)
{
    Brain brain;
    std::string input;

    std::getline(std::cin, input);
    std::vector<std::string> words = stringToVector(input);

    if (words[0] == "START") {
        int size_map = stringToINT(words[1]);
        brain.run(size_map);
    }
    return 0;
}
