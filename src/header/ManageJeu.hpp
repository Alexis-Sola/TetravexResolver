#ifndef MANAGEJEU_HPP
#define MANAGEJEU_HPP

#include "Plateau.hpp"

class ManageJeu
{
private:
    Matrix fic;
    Plateau plateau;
    unsigned nb_par_ligne;

public:

    ManageJeu(Matrix _fic);

    void game_start();
    void switch_piece(unsigned num_piece_valable, unsigned piece_plateau);
    bool check_deplacement(Piece p);
    bool check_west(Piece p);
    bool check_est(Piece p);
    bool check_north(Piece p);
    bool check_south(Piece p);
    bool Equals(unsigned i, unsigned j);

};

#endif // MANAGEJEU_HPP
