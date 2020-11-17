#include "../header/Plateau.hpp"

Plateau::Plateau(Matrix _valeurs)
{
    valeurs = _valeurs;
    nb_par_ligne = valeurs[0][0];
    taille_plateau = nb_par_ligne * nb_par_ligne;
}

unsigned Plateau::get_nb_par_ligne()
{
    return nb_par_ligne;
}
unsigned Plateau::get_taille_plateau()
{
    return taille_plateau;
}
vector<Piece> Plateau::get_pieces_jeu()
{
    return pieces_jeu;
}
void Plateau::set_pieces_jeu(vector<Piece> new_list)
{
    pieces_jeu = new_list;
}
vector<Piece> Plateau::get_pieces_init()
{
  return pieces_init;
}

void Plateau::fillPiecesJeu()
{
    int cpt = 0;
    for(vector<int> piece : valeurs)
    {
        if(cpt != 0)
            pieces_jeu.push_back(Piece(piece));
        cpt++;
    }
}

void Plateau::fillPiecesInit()
{
    for(unsigned i = 0; i < taille_plateau; i++)
    {
        pieces_init.push_back(Piece({99,99,99,99}));
    }
}

void Plateau::afficheGrille(vector<Piece> pieces)
{
    unsigned cpt = 0;
    for(Piece p : pieces)
    {
        if(cpt%nb_par_ligne == 0)
        {
            cout << '\n';
        }
        cout << ' ' << cpt + 1 << ' ';
        p.affiche_piece();
        cpt++;
    }
}

void Plateau::affichePieceValable()
{
    unsigned cpt = 0;
    for(Piece p : pieces_jeu)
    {
        cout << '\n';
        cout << ' ' << cpt + 1 << ' ';
        p.affiche_piece();
        cpt++;
    }
}
