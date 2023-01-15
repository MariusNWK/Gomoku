#include "useful.hpp"

std::vector<std::string> stringToVector(std::string str, std::string delimiter)
{
    std::vector<std::string> vector;
    int start = 0;
    int end = str.find(delimiter);

    std::string tmp;

    while (end != -1) {
        vector.push_back(str.substr(start, end - start));
        start = end + delimiter.size();
        end = str.find(delimiter, start);
    }
    vector.push_back(str.substr(start, end - start));
    return vector;
}

int stringToINT(std::string str)
{
    std::stringstream sstream(str);
    int number;

    sstream >> number;
    return number;
}

int getMax(int n1, int n2)
{
    if (n1 >= n2) {
        return n1;
    }
    return n2;
}

int getMin(int n1, int n2)
{
    if (n1 < n2) {
        return n1;
    }
    return n2;
}

Eval getMaxEval(Eval n1, Eval n2)
{
    if (n1.value >= n2.value) {
        return n1;
    }
    return n2;
}

Eval getMinEval(Eval n1, Eval n2)
{
    if (n1.value < n2.value) {
        return n1;
    }
    return n2;
}

int absolute(int n)
{
    if (n < 0) {
        return -n;
    }
    return n;
}
