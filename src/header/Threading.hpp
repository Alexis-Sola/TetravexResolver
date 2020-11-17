#ifndef THREADING_HPP
#define THREADING_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include<stdio.h>
#include<stdlib.h>
#include <thread>
#include <mutex>
#include <algorithm>
#include <random>

#include "Solver.hpp"
#include "ThreadPool.hpp"
#include "utils.hpp"

using namespace std;

mutex m1;
bool Solver::found = false;

//Fonction qui sera lancé dans les threads
void init_thread(const Matrix &data)
{
    //On lance le chrono
    auto start_ = chrono::high_resolution_clock::now();
    //Valeur qui permet d'utiliser le random
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    Plateau pl(data);
    //On mélange le vecteur
    //Le but et d'avoir un point de départ différent pour
    //lancer notre fonction sur différents threads
    vector<PieceOpti> shuffle_vec = fill_vector(data);
    shuffle (shuffle_vec.begin(), shuffle_vec.end(), default_random_engine(seed));

    //On lance la fonction de résolution
    Solver s(pl, shuffle_vec);
    s.solver_recur(0);

    //Si un thread a déjà résolu on passe l'affichage
    if(Solver::found)
      return;
    //On calcule le temps
    auto find_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::high_resolution_clock::now() - start_);

    //On affiche le temps
    cout << "Solution trouvé en : " << find_time.count()*0.001 << " seconds" << endl;

    //Quand une solution est trouvée on l'indique
    m1.lock();
    Solver::found = true;
    m1.unlock();
}

//1er fonction de parallélisation
void solver_para(const unsigned &nb_thread, const Matrix &data)
{
    //On créer un vecteur de thread
    vector<thread> ts;
    //On lance notre fonction sur chaque thread
    for(unsigned i = 0; i < nb_thread; i++)
        ts.push_back(thread(init_thread, data));

    //On lance les threads
    for(unsigned i = 0; i < ts.size(); i++)
    {
        if(ts.at(i).joinable())
            ts.at(i).join();
    }
    //On remet found dans son état de départ
    Solver::found = false;
}

//2e fonction qui utilise le thread pool
void solver_tp(const unsigned &size_pool, const unsigned &nb_thread, const Matrix &data)
{
    //Creation du thread pool
    ThreadPool tp(size_pool, data);
    //On remplie notre queue
    for(unsigned i = 0; i < nb_thread; i++)
        tp.add(init_thread);
    Solver::found = false;
}

#endif
