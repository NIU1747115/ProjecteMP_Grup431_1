#ifndef POSICIO_HPP
#define POSICIO_HPP

#include <string>
#include <iostream>
using namespace std;

class Posicio
{
public:
    Posicio();
    Posicio(const string& text);
    Posicio(int fila, int columna);

    int getFila() const { return m_fila; }
    int getColumna() const { return m_columna; }

    string toString() const;
    bool operator==(const Posicio& pos) const;

private:
    int m_fila;
    int m_columna;
};

ostream& operator<<(ostream& out, const Posicio& pos);

#endif