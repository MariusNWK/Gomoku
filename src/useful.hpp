#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

typedef struct Eval {
    int x;
    int y;
    int value;
} Eval;

std::vector<std::string> stringToVector(std::string str, std::string delimiter = " ");
int stringToINT(std::string str);
int getMax(int n1, int n2);
int getMin(int n1, int n2);
Eval getMaxEval(Eval n1, Eval n2);
Eval getMinEval(Eval n1, Eval n2);
int absolute(int n);

// pbrain-pela : nom de l'algo qu'il y a de base dans Piskvork
