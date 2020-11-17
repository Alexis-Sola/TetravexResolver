#ifndef PIECE_HPP
#define PIECE_HPP

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Piece
{

private:
    vector<int> valeurs;
    map<char, int> face;
    unsigned position;

public:
    //Par defaut la piece n'est pas utilisée
    bool use = false;

    //Constructeur de Piece
    Piece(const vector<int> &v);

    //Getters-Setters
    vector<int> get_valeurs();
    map<char, int> get_face();
    unsigned get_position();
    void set_position(unsigned pos);

    //Affichage de la piece
    void affiche_piece();
};

#endif // TES_H
