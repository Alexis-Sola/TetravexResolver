#include <iostream>
#include "../header/Threading.hpp"
#include "../header/PieceOpti.hpp"
#include "../header/utils.hpp"
#include "../header/ManageJeu.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    if(argc == 1)
      cerr << "Arguments incomplets 1 : path du fichier 2 : taille du plateau" << endl;

    string fic_path = argv[1];
    unsigned p_size = atoi(argv[2]);

    Matrix data = readFic(fic_path, p_size);
    while(true)
    {
        int inter_un;
        cout << "1 : Jouer - 2 : Solver " << endl;
        cin >> inter_un;

        if(inter_un == 1)
        {
            //On créer notre vecteur de pièces
            //Plateau pl(data);
            ManageJeu jeu(data);
            jeu.game_start();
        }
        if(inter_un == 2)
        {
            while(true) {
                int inter_deux;
                cout << "1 : Solver recursif - 2 : Solver thread - 3 : Solver thread pool" << endl;
                cin >> inter_deux;
                if(inter_deux == 1)
                {

                    Plateau pl(data);

                    //On lance la fonction de résolution
                    Solver s(pl, fill_vector(data));

                    //On lance le chrono
                    auto start_ = chrono::high_resolution_clock::now();

                    s.solver_recur(0);

                    //On calcule le temps
                    auto find_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                                std::chrono::high_resolution_clock::now() - start_);

                    //On affiche le temps
                    cout << "Solution trouvé en : " << find_time.count()*0.001 << " seconds" << endl;

                }
                else if(inter_deux == 2)
                {
                    solver_para(10, data);
                }
                else if(inter_deux == 3)
                {
                    solver_tp(4, 4, data);
                }
                else
                    break;
            }
        }
        else
            break;
    }
    return 0;
}
