#include "../header/Solver.hpp"

Solver::Solver(const Plateau &pl, const vector<PieceOpti> &v)
{
    plateau = pl;
    ps = v;
    nb_par_ligne = plateau.get_nb_par_ligne();
}

void Solver::show_solved()
{
    unsigned cpt = 0;
    for(PieceOpti *p : solved)
    {
        if(cpt%nb_par_ligne == 0)
        {
            cout << '\n';
        }
        cout << ' ' << cpt + 1 << ' ';
        cout << "[W: " << p->west << " N: " << p->north << " E: " << p->est << " S: " << p->south << "] ";
        cpt++;
    }
}

bool Solver::test_sides(const unsigned &pos_est, const unsigned &pos_west)
{
    //Si pos==0 pas de test à faire car il n'y a rien avant
    //Si on est sur le bord droit de la matrice pas de contrainte
    //Sinon on test que E == W
    if((pos_est < 1) || (pos_est % nb_par_ligne == 0) || (solved.at(pos_est - 1)->est == ps.at(pos_west).west))
        return true;
    return false;
}

bool Solver::test_extremities(const unsigned &pos_south, const unsigned &pos_north)
{
    //Si on est < nb_par_ligne par de contrainte car rien à tester avant
    //Sinon on test S == N
    if((pos_south < nb_par_ligne) || (solved.at(pos_south - nb_par_ligne)->south == ps.at(pos_north).north))
      return true;
    return false;
}

bool Solver::solver_recur(const unsigned &pos)
{
    //Permet d'arrêter la recherche lors de la parallélisation
    if(Solver::found)
      return true;

    //On s'arrête dès que le tableau de solution est plein
    if(pos == ps.size())
        return true;

    //On parcours toutes les pièces dispo
    for(unsigned i = 0; i < ps.size(); i++)
    {
        //Si la pièce déjà utilisée on passe à la pièce suivante
        if(ps.at(i).used)
            continue;

        //On test si la pièce respecte nos contraintes
        if(test_sides(pos, i) && test_extremities(pos, i))
        {
            //On ajoute la pièce candidate au vecteur de solution
            solved.push_back(&ps.at(i));
            ps.at(i).used = true;

            //Pos permet de connaitre la position du tableau de solution
            unsigned new_pos = pos + 1;

            //Appel récursif pour explorer les solutions
            //Si on trouve une solution on s'enfonce plus profondément dans l'exploration
            if(solver_recur(new_pos))
              return true;

            //Sinon on revient en arrière et on enlève la pièce condidate du tableau
            //Et on test d'autre pièce candidate
            solved.pop_back();
            ps.at(i).used = false;
        }
    }
    return false;
}
