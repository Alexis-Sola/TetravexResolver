#ifndef PIECEOPTI_HPP
#define PIECEOPTI_HPP

#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int>> Matrix;

//Définition simple pour le solver
struct PieceOpti
{
    int west;
    int north;
    int est;
    int south;
    bool used = false;
};
#endif
