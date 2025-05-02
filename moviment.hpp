#ifndef MOVIMENT_H
#define MOVIMENT_H

#include "posicio.hpp"
#include <string>
using namespace std;

const int MAX_TRAJECTE = 20;
const int MAX_ENEMICS = 8;

class Moviment
{
public:
    Moviment();
    Moviment(const Posicio& origen);

    int getNombrePassos() const { return m_nTrajecte; }
    const Posicio& getPosicio(int i) const { return m_trajecte[i]; }
    int getNombreEliminades() const { return m_nEliminades; }
    const Posicio& getEliminada(int i) const { return m_eliminades[i]; }

    void afegeixPosicio(const Posicio& pos);
    void afegeixFitxaEliminada(const Posicio& pos);
    string toString() const;

private:
    Posicio m_trajecte[MAX_TRAJECTE];
    int m_nTrajecte;
    Posicio m_eliminades[MAX_ENEMICS];
    int m_nEliminades;
};

#endif