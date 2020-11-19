#include "../header/ManageJeu.hpp"

ManageJeu::ManageJeu(Matrix _fic)
{
    fic = _fic;
    plateau = Plateau(fic);
    nb_par_ligne = plateau.get_nb_par_ligne();
}

void ManageJeu::game_start()
{

    //Initialisation des pièces
    plateau.fillPiecesInit();
    plateau.fillPiecesJeu();

    while(true){

        plateau.afficheGrille(plateau.get_pieces_init());
        cout << '\n';

        cout << "---------------------------------------------------------------------------------------------------------------------------------";

        plateau.affichePieceValable();
        cout << '\n';

        unsigned piece_plateau;
        unsigned piece_valable;

        cout << "Selectionner un emplacement sur la grille";
        cin >> piece_plateau;
        cout << "Selectionner la piece a echanger";
        cin >> piece_valable;

        switch_piece(piece_valable - 1, piece_plateau - 1);

        if(plateau.get_pieces_jeu().empty())
        {
            cout << "WIN" << endl;
            break;
        }
    }
}

void ManageJeu::switch_piece(unsigned num_piece_valable, unsigned piece_plateau)
{
    //On set la postion souhaité à la piece du puzzle avec les valeurs du fichier
    plateau.pieces_jeu[num_piece_valable].set_position(piece_plateau);

    if(check_deplacement(plateau.pieces_jeu[num_piece_valable]))
    {
        plateau.pieces_init[piece_plateau] = plateau.pieces_jeu[num_piece_valable];
        plateau.pieces_jeu.erase(plateau.pieces_jeu.begin() + num_piece_valable);
    }
    else
        cout << "Deplacement impossible" << endl;

}

bool ManageJeu::check_deplacement(Piece p)
{
    if(check_west(p) && check_est(p) && check_north(p) && check_south(p))
    {
        return true;
    }
    else
        return false;
}

bool ManageJeu::check_west(Piece p)
{
    unsigned position = p.get_position();
    if(position >= 1)
    {
        Piece p_west = plateau.pieces_init[p.get_position() - 1];

        if(Equals( p_west.get_face()['E'], p.get_face()['W']))
        {
            return true;
        }
        return false;
    }
    return true;
}

bool ManageJeu::check_est(Piece p)
{
    unsigned position = p.get_position();
    if(position <= plateau.get_taille_plateau() - 1)
    {
        Piece p_est = plateau.pieces_init[p.get_position() + 1];

        if(Equals(p_est.get_face()['W'], p.get_face()['E']))
        {
            return true;
        }
        return false;
    }
    return true;
}

bool ManageJeu::check_north(Piece p)
{
    unsigned position = p.get_position();
    if(position >= nb_par_ligne)
    {
        Piece p_north = plateau.pieces_init[p.get_position() - nb_par_ligne];

        if(Equals(p_north.get_face()['S'], p.get_face()['N']))
        {
            return true;
        }
        return false;
    }
    return true;
}

bool ManageJeu::check_south(Piece p)
{
    unsigned position = p.get_position();
    if(position <= plateau.get_taille_plateau() - nb_par_ligne)
    {
        Piece p_south = plateau.pieces_init[p.get_position() + nb_par_ligne];

        if(Equals(p_south.get_face()['N'], p.get_face()['S']))
        {
            return true;
        }
        return false;
    }
    return true;
}

bool ManageJeu::Equals(unsigned i, unsigned j)
{
    if(i == j || i == 99)
    {
        return true;
    }
    return false;
}
