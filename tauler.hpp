#ifndef TAULER_H
#define TAULER_H

#include "posicio.hpp"
#include "fitxa.hpp"
#include <string>

const int MAX_FILES = 8;
const int MAX_COLUMNES = 8;

class Tauler
{
public:
    Tauler() {}

    void inicialitza(const std::string& nomFitxer);
    void actualitzaMovimentsValids();
    void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);
    bool mouFitxa(const Posicio& origen, const Posicio& desti);
    std::string toString() const;

private:
    Fitxa tauler[MAX_FILES][MAX_COLUMNES];

    Fitxa getFitxa(const Posicio& pos) const;
    bool posicioValida(const Posicio& pos) const;
    bool esMovimentValid(const Posicio& origen, const Posicio& desti) const;

    void exploraSaltNormal(const Posicio& origen, const Fitxa& fitxa, bool visitat[8][8], int& nPosicions, Posicio posicionsPossibles[]);
    void exploraSaltDama(const Posicio& origen, const Fitxa& fitxa, bool visitat[8][8], int& nPosicions, Posicio posicionsPossibles[]);
};

#endif