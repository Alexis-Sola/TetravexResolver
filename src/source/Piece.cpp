#include "../header/Piece.hpp"


Piece::Piece(const vector<int> &v)
{
    valeurs = v;

    face = {
        {'W', valeurs[0] },
        {'N', valeurs[1] },
        {'E', valeurs[2] },
        {'S', valeurs[3] }
    };
}

vector<int> Piece::get_valeurs()
{
    return valeurs;
}

map<char, int> Piece::get_face()
{
    return face;
}

unsigned Piece::get_position()
{
    return position;
}

void Piece::set_position(unsigned pos)
{
    position = pos;
}

void Piece::affiche_piece()
{
   cout << "[W: " << face['W'] << " N: " << face['N'] << " E: " << face['E'] << " S: " << face['S'] << "] ";
}
