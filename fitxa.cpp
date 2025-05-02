#include <iostream>
using namespace std;
#include "fitxa.hpp"

Fitxa::Fitxa()
{
    m_tipus = TIPUS_EMPTY;
    m_color = COLOR_BLANC;
    m_nMovimentsValids = 0;
}


Fitxa::Fitxa(TipusFitxa tipus, ColorFitxa color)
{
    m_tipus = tipus;
    m_color = color;
    m_nMovimentsValids = 0;
}


void Fitxa::afegeixMovimentValid(const Moviment& moviment)
{
    if (m_nMovimentsValids < MAX_MOVIMENTS)
    {
        m_movimentsValids[m_nMovimentsValids] = moviment;
        m_nMovimentsValids++;
    }
}


void Fitxa::resetMoviments()
{
    m_nMovimentsValids = 0;
    for (int i = 0; i < MAX_MOVIMENTS; i++)
    {
        m_movimentsValids[i] = Moviment();
    }
}


bool Fitxa::esBuida() const
{
    return m_tipus == TIPUS_EMPTY;
}


void Fitxa::promocionaADama()
{
    if (m_tipus == TIPUS_NORMAL)
    {
        m_tipus = TIPUS_DAMA;
    }
}

string Fitxa::toString() const
{
    if (m_tipus == TIPUS_EMPTY)
        return "-";

    if (m_color == COLOR_BLANC)
        return (m_tipus == TIPUS_DAMA) ? "D" : "O";
    else if (m_color == COLOR_NEGRE)
        return (m_tipus == TIPUS_DAMA) ? "R" : "X";

    return "0";
}