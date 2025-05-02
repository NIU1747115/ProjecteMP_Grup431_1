#include <iostream>
using namespace std;
#include "moviment.hpp"

Moviment::Moviment()
{
    m_nTrajecte = 0;
    m_nEliminades = 0;
}

Moviment::Moviment(const Posicio& origen)
{
    m_trajecte[0] = origen;
    m_nTrajecte = 1;
    m_nEliminades = 0;
}


void Moviment::afegeixPosicio(const Posicio& pos)
{
    m_trajecte[m_nTrajecte + 1] = pos;
    m_nTrajecte++;
}


void Moviment::afegeixFitxaEliminada(const Posicio& pos)
{
    m_eliminades[m_nEliminades + 1] = pos;
    m_nEliminades++;
}


string Moviment::toString() const
{
    string resultat;

    for (int i = 0; i < m_nTrajecte; ++i)
    {
        resultat += m_trajecte[i].toString();
        if (i != m_nTrajecte - 1)
            resultat += " -> ";
    }

    if (m_nEliminades > 0)
    {
        resultat += " | Captures: ";
        for (int i = 0; i < m_nEliminades; ++i)
        {
            resultat += m_eliminades[i].toString();
            if (i != m_nEliminades - 1)
                resultat += ", ";
        }
    }

    return resultat;
}