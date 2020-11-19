#ifndef SOLVER_HPP
#define SOLVER_HPP

#include <vector>
#include <iostream>
#include <mutex>
#include <thread>
#include <queue>
#include <algorithm>
#include <random>
#include <stack>

#include "Plateau.hpp"
#include "PieceOpti.hpp"

using namespace std;

class Solver{

private:
    Plateau plateau;
    unsigned nb_par_ligne;
    vector<PieceOpti> ps;
    vector<PieceOpti*> solved;

    //Test si le déplacement est posible sur les côtés
    bool test_sides(const unsigned &pos_est, const unsigned &pos_west);
    //Test si le déplacement est possible au dessus et en dessous
    bool test_extremities(const unsigned &pos_south, const unsigned &pos_north);
    //affiche la solution
    void show_solved();

public:
    static bool found;
    Solver(const Plateau &pl, const vector<PieceOpti> &v);
    //fonction de backtracking de résolution du puzzle
    bool solver_recur(const unsigned &pos);
};
#endif // SOLVER_HPP
