#ifndef PLATEAU_HPP
#define PLATEAU_HPP

#include <iostream>
#include <vector>
#include "Piece.hpp"

using namespace std;

typedef vector<vector<int>> Matrix;

class Plateau
{
private:
    Matrix valeurs;
    unsigned taille_plateau;
    unsigned nb_par_ligne;

public:
    vector<Piece> pieces_init;
    vector<Piece> pieces_jeu;

    Plateau(){}

    Plateau(Matrix _valeurs);

    //Getters et Setters
    unsigned get_nb_par_ligne();
    unsigned get_taille_plateau();
    vector<Piece> get_pieces_jeu();
    void set_pieces_jeu(vector<Piece> new_list);
    vector<Piece> get_pieces_init();
    void set_pieces_init(vector<Piece> new_list);

    //Initialise le vecteur de pieces
    void fillPiecesJeu();
    //Initialise les pieces vides
    void fillPiecesInit();
    //affiche la grille de jeu
    void afficheGrille(vector<Piece> pieces);
    //affiche les pièces valables
    void affichePieceValable();
};

#endif // PLATEAU_HPP
