#include "posicio.hpp"

Posicio::Posicio()
{
    m_fila = 0;
    m_columna = 0;
}


Posicio::Posicio(const string& text)
{
    m_columna = text[0] - 'a';
    m_fila = (text[1] - '0') - 1;
}


Posicio::Posicio(int fila, int columna)
{
    m_fila = fila;
    m_columna = columna;
}


string Posicio::toString() const
{
    char columna = 'a' + m_columna;
    char fila = '1' + m_fila;

    string resultat;
    resultat += columna;
    resultat += fila;

    return resultat;
}


bool Posicio::operator==(const Posicio& pos) const
{
    return (m_fila == pos.m_fila && m_columna == pos.m_columna);
}


ostream& operator<<(ostream& out, const Posicio& pos)
{
    out << pos.toString();
    return out;
}