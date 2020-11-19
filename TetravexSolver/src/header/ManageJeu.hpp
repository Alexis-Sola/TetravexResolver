#ifndef MANAGEJEU_HPP
#define MANAGEJEU_HPP

#include "Plateau.hpp"

//Permet de jouer au tetravex
//Gere la partie
class ManageJeu
{
private:
    Matrix fic;
    Plateau plateau;
    unsigned nb_par_ligne;

public:

    ManageJeu(Matrix _fic);

    //lance la game
    void game_start();
    //place la pièce selectionnée sur le palteau
    void switch_piece(unsigned num_piece_valable, unsigned piece_plateau);
    //vérifie si l'on peut placer la pièce
    bool check_deplacement(Piece p);
    //check tous les déplacements
    bool check_west(Piece p);
    bool check_est(Piece p);
    bool check_north(Piece p);
    bool check_south(Piece p);
    bool Equals(unsigned i, unsigned j);

};

#endif // MANAGEJEU_HPP
