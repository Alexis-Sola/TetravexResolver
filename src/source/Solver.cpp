#include "../header/Solver.hpp"

Solver::Solver(const Plateau &pl, const vector<PieceOpti> &p_shuffle)
{
    plateau = pl;
    ps = p_shuffle;
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
    //On regarde si on est au bord et si on a le droit e placer la piece
    if((pos_est < 1) || (pos_est % nb_par_ligne == 0) || (solved.at(pos_est - 1)->est == ps.at(pos_west).west))
        return true;
    return false;
}

bool Solver::test_extremities(const unsigned &pos_south, const unsigned &pos_north)
{
    if((pos_south < nb_par_ligne) || (solved.at(pos_south - nb_par_ligne)->south == ps.at(pos_north).north))
      return true;
    return false;
}

bool Solver::solver_recur(const unsigned &pos)
{
    if(Solver::found)
      return true;

    if(pos == ps.size())
        return true;

    for(unsigned i = 0; i < ps.size(); i++)
    {
        if(ps.at(i).used)
            continue;

        if(test_sides(pos, i) && test_extremities(pos, i))
        {
            solved.push_back(&ps.at(i));
            ps.at(i).used = true;

            unsigned new_pos = pos + 1;

            if(solver_recur(new_pos))
              return true;

            solved.pop_back();
            ps.at(i).used = false;
        }
    }
    return false;
}
