#ifndef FITXA_H
#define FITXA_H

#include <string>
#include "moviment.hpp"
#include "posicio.hpp"

using namespace std;

typedef enum
{
    TIPUS_NORMAL,
    TIPUS_DAMA,
    TIPUS_EMPTY
} TipusFitxa;

typedef enum
{
    COLOR_NEGRE,
    COLOR_BLANC
} ColorFitxa;

const int MAX_MOVIMENTS = 16;

class Fitxa
{
public:
    Fitxa();
    Fitxa(TipusFitxa tipus, ColorFitxa color);

    TipusFitxa getTipus() const { return m_tipus; }
    ColorFitxa getColor() const { return m_color; }
    int getNombreMoviments() const { return m_nMovimentsValids; }
    Moviment getMovimentValid(int i) const { return m_movimentsValids[i]; }

    void setTipus(TipusFitxa tipus) { m_tipus = tipus; }
    void setColor(ColorFitxa color) { m_color = color; }
    void afegeixMovimentValid(const Moviment& moviment);
    void resetMoviments();

    bool esBuida() const;
    void promocionaADama();
    string toString() const;

private:
    TipusFitxa m_tipus;
    ColorFitxa m_color;
    Moviment m_movimentsValids[MAX_MOVIMENTS];
    int m_nMovimentsValids;
};

#endif