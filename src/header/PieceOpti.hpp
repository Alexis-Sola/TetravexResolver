#ifndef PIECEOPTI_HPP
#define PIECEOPTI_HPP

#include <iostream>
#include <vector>

using namespace std;

struct PieceOpti
{
  int west;
  int north;
  int est;
  int south;
  bool used = false;
};
#endif
