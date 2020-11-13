#include "frupal.h"

Hero::Hero(int whif, int nRG)
{
  whiffles = whif;
  energy = nRG;
  for(int i = 0; i < 128; ++i)
  {
    for(int j = 0; j < 128; ++j)
    {
      visitMap[i][j] = false;
    }
  }
}

void Hero::modEner(int nRG)
{
  energy += nRG;
}

void Hero::modWhif(int Whif)
{
  whiffles += Whif;
}

bool Hero::updateMap(int y, int x)
{
  if(!visitMap[y][x])
  {
    visitMap[y][x] = true;
    return true;
  }
  return false;
}
