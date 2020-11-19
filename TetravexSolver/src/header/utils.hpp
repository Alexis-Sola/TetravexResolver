#ifndef UTILS_HPP
#define UTILS_HPP

#include "PieceOpti.hpp"

#include <iostream>
#include <vector>
#include <fstream>

//Créer et remplie un tableau de PieceOpti
vector<PieceOpti> fill_vector(Matrix data)
{
  vector<PieceOpti> return_v;
  unsigned cpt = 0;

  for(vector<int> piece : data)
  {
      if(cpt != 0)
      {
          PieceOpti p;
          p.west = piece[0];
          p.north = piece[1];
          p.est = piece[2];
          p.south = piece[3];
          return_v.push_back(p);
      }
      cpt++;
  }
  return return_v;
}

//Permet de lire un fichier
Matrix readFic(const string &path, const unsigned &size_puzzle)
{
    //on ouvre le fichier en lecture
    ifstream fichier(path, ios::in);

    Matrix m;
    m.resize(size_puzzle + 1);

    //si l'ouverture a réussi
    if(fichier)
    {
        string ligne;

        unsigned i = 0;
        unsigned j = 0;
        //tant que qu'il y a des lignes on créer notre matrice
        while(!fichier.eof())
        {
            getline(fichier, ligne);

            for(char c : ligne)
            {
                if(c != ' ' && c != '\n')
                {
                    m[i].resize(4);
                    m[i][j] = c - 48;
                    j++;
                }
            }
            j = 0;

            i++;
        }

        //on ferme le fichier
        fichier.close();
    }
    else
        cerr << "Impossible d'ouvrir le fichier !" << endl;

    return m;
}

#endif
