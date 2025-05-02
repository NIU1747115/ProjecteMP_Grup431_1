#include <iostream>
#include <string>
#include "tauler.hpp"
#include <fstream>

void Tauler::inicialitza(const string& nomFitxer)
{
    for (int i = 0; i < MAX_FILES; i++)
        for (int j = 0; j < MAX_COLUMNES; j++)
            tauler[i][j] = Fitxa();

    ifstream fitxer(nomFitxer);
    if (fitxer.is_open())
    {
        char tipusFitxa;
        string posicioText;

        while (fitxer >> tipusFitxa >> posicioText)
        {
            Posicio posicio(posicioText);
            int fila = posicio.getFila();
            int columna = posicio.getColumna();

            if (fila >= 0 && fila < MAX_FILES && columna >= 0 && columna < MAX_COLUMNES)
            {
                TipusFitxa tipus;
                ColorFitxa color;
                switch (tipusFitxa)
                {
                case 'O':
                    tipus = TIPUS_NORMAL;
                    color = COLOR_BLANC;
                    break;
                case 'X':
                    tipus = TIPUS_NORMAL;
                    color = COLOR_NEGRE;
                    break;
                case 'D':
                    tipus = TIPUS_DAMA;
                    color = COLOR_BLANC;
                    break;
                case 'R':
                    tipus = TIPUS_DAMA;
                    color = COLOR_NEGRE;
                    break;
                default:
                    continue;
                }

                tauler[fila][columna] = Fitxa(tipus, color);
            }
        }

        fitxer.close();
    }
}


void Tauler::actualitzaMovimentsValids()
{
    for (int fila = 0; fila < MAX_FILES; fila++)
    {
        for (int columna = 0; columna < MAX_COLUMNES; columna++)
        {
            Posicio origen(fila, columna);
            Fitxa fitxa = getFitxa(origen);

            if (fitxa.getTipus() != TIPUS_EMPTY)
            {
                int nPosicions = 0;
                Posicio posicionsPossibles[4];

                getPosicionsPossibles(origen, nPosicions, posicionsPossibles);
            }
        }
    }
}


void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[])
{
    nPosicions = 0;

    Fitxa fitxa = getFitxa(origen);
    int columna = origen.getColumna();
    int fila = origen.getFila();

    if (fitxa.getTipus() == TIPUS_NORMAL)
    {
        int dir_f = (fitxa.getColor() == COLOR_BLANC) ? 1 : -1;

        for (int dir_c = -1; dir_c <= 1; dir_c += 2)
        {
            int f = fila + dir_f;
            int c = columna + dir_c;

            if (posicioValida(Posicio(f, c)) && getFitxa(Posicio(f, c)).esBuida())
                posicionsPossibles[nPosicions++] = Posicio(f, c);
        }

        bool visitat[8][8] = { false };
        exploraSaltNormal(origen, fitxa, visitat, nPosicions, posicionsPossibles);
    }

    else if (fitxa.getTipus() == TIPUS_DAMA)
    {
        int dirs[4][2] = { {1,1}, {-1,1}, {1,-1}, {-1,-1} };

        for (int d = 0; d < 4; ++d)
        {
            int movFila = dirs[d][0];
            int movCol = dirs[d][1];
            int f = fila + movFila;
            int c = columna + movCol;

            while (posicioValida(Posicio(f, c)) && getFitxa(Posicio(f, c)).esBuida())
            {
                posicionsPossibles[nPosicions++] = Posicio(f, c);
                f += movFila;
                c += movCol;
            }
        }

        bool visitat[8][8] = { false };
        exploraSaltDama(origen, fitxa, visitat, nPosicions, posicionsPossibles);
    }



}


bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti)
{
    if (!posicioValida(origen) || !posicioValida(desti))
        return false;

    if (!esMovimentValid(origen, desti))
        return false;

    Fitxa fitxaOrigen = tauler[origen.getFila()][origen.getColumna()];
    int difFila = desti.getFila() - origen.getFila();
    int difCol = desti.getColumna() - origen.getColumna();

    if (fitxaOrigen.getTipus() == TIPUS_NORMAL && abs(difFila) == abs(difCol) && abs(difFila) >= 2 && abs(difFila) % 2 == 0)
    {
        int color = fitxaOrigen.getColor();
        int dir_f = (color == COLOR_BLANC) ? 1 : -1;
        int pasos = abs(difFila) / 2;
        int f = origen.getFila();
        int c = origen.getColumna();
        for (int i = 0; i < pasos; ++i)
        {
            int fEnemic = f + dir_f;
            int cEnemic = c + ((difCol > 0) ? 1 : -1);
            tauler[fEnemic][cEnemic] = Fitxa();
            f += 2 * dir_f;
            c += (difCol > 0) ? 2 : -2;
        }
    }

    if (fitxaOrigen.getTipus() == TIPUS_DAMA && abs(difFila) > 1 && abs(difFila) == abs(difCol))
    {
        int movFila = (difFila > 0) ? 1 : -1;
        int movCol = (difCol > 0) ? 1 : -1;
        int f = origen.getFila() + movFila;
        int c = origen.getColumna() + movCol;
        while (f != desti.getFila() && c != desti.getColumna())
        {
            Fitxa fitxaActual = tauler[f][c];
            if (!fitxaActual.esBuida() && fitxaActual.getColor() != fitxaOrigen.getColor())
            {
                tauler[f][c] = Fitxa();
                break;
            }
            f += movFila;
            c += movCol;
        }
    }

    tauler[desti.getFila()][desti.getColumna()] = fitxaOrigen;
    tauler[origen.getFila()][origen.getColumna()] = Fitxa();

    if (fitxaOrigen.getTipus() == TIPUS_NORMAL)
    {
        if ((fitxaOrigen.getColor() == COLOR_BLANC && desti.getFila() == 7) || (fitxaOrigen.getColor() == COLOR_NEGRE && desti.getFila() == 0))
            tauler[desti.getFila()][desti.getColumna()].promocionaADama();
    }

    return true;
}


string Tauler::toString() const
{
    string resultado = "";

    for (int i = MAX_FILES - 1; i >= 0; --i)
    {
        resultado += to_string(i + 1) + ": ";
        for (int j = 0; j < MAX_COLUMNES; ++j)
        {
            const Fitxa& f = tauler[i][j];

            if (f.esBuida())
                resultado += "_";
            else
            {
                if (f.getTipus() == TIPUS_NORMAL)
                {
                    if (f.getColor() == COLOR_NEGRE)
                        resultado += "X";
                    else
                        resultado += "O";
                }
                else if (f.getTipus() == TIPUS_DAMA)
                {
                    if (f.getColor() == COLOR_NEGRE)
                        resultado += "R";
                    else
                        resultado += "D";
                }
            }

            if (j != MAX_COLUMNES - 1)
                resultado += " ";
        }
        resultado += "\n";
    }

    resultado += "   ";
    for (char col = 'a'; col <= 'h'; ++col)
        resultado += col + string(" ");
    resultado += "\n";

    return resultado;
}


Fitxa Tauler::getFitxa(const Posicio& pos) const
{
    return tauler[pos.getFila()][pos.getColumna()];
}


bool Tauler::posicioValida(const Posicio& pos) const
{
    return (pos.getFila() >= 0 && pos.getFila() < MAX_FILES && pos.getColumna() >= 0 && pos.getColumna() < MAX_COLUMNES);
}


bool Tauler::esMovimentValid(const Posicio& origen, const Posicio& desti) const
{
    Fitxa fitxaOrigen = tauler[origen.getFila()][origen.getColumna()];
    Fitxa fitxaDesti = tauler[desti.getFila()][desti.getColumna()];

    if (fitxaOrigen.getTipus() == TIPUS_EMPTY || fitxaDesti.getTipus() != TIPUS_EMPTY)
        return false;

    int color = fitxaOrigen.getColor();

    if (fitxaOrigen.getTipus() == TIPUS_NORMAL)
    {
        int dir_f = (color == COLOR_BLANC) ? 1 : -1;
        int difFila = desti.getFila() - origen.getFila();
        int difCol = desti.getColumna() - origen.getColumna();

        if (difFila == dir_f && abs(difCol) == 1)
            return true;

        if (abs(difFila) == abs(difCol) && abs(difFila) >= 2 && (difFila / dir_f) > 0 && abs(difFila) % 2 == 0)
        {
            int pasos = abs(difFila) / 2;
            int f = origen.getFila();
            int c = origen.getColumna();
            for (int i = 0; i < pasos; ++i)
            {
                int fEnemic = f + dir_f;
                int cEnemic = c + ((difCol > 0) ? 1 : -1);
                Fitxa fitxaEnemic = tauler[fEnemic][cEnemic];
                int fDesti = f + 2 * dir_f;
                int cDesti = c + ((difCol > 0) ? 2 : -2);

                if (fitxaEnemic.esBuida() || fitxaEnemic.getColor() == color)
                    return false;
                if (!tauler[fDesti][cDesti].esBuida())
                    return false;
                f = fDesti;
                c = cDesti;
            }
            if (f == desti.getFila() && c == desti.getColumna())
                return true;
        }
        return false;
    }

    if (fitxaOrigen.getTipus() == TIPUS_DAMA)
    {
        int difFila = desti.getFila() - origen.getFila();
        int difCol = desti.getColumna() - origen.getColumna();

        if (abs(difFila) == abs(difCol) && abs(difFila) > 0)
        {
            int movFila = (difFila > 0) ? 1 : -1;
            int movCol = (difCol > 0) ? 1 : -1;
            int f = origen.getFila() + movFila;
            int c = origen.getColumna() + movCol;
            bool esEnemic = false;
            while (f != desti.getFila() && c != desti.getColumna())
            {
                Fitxa fActual = tauler[f][c];
                if (!fActual.esBuida())
                {
                    if (!esEnemic && fActual.getColor() != fitxaOrigen.getColor())
                        esEnemic = true;
                    else
                        return false;
                }
                f += movFila;
                c += movCol;
            }
            return true;
        }
    }
    return false;
}


void Tauler::exploraSaltNormal(const Posicio& origen, const Fitxa& fitxa, bool visitat[8][8], int& nPosicions, Posicio posicionsPossibles[])
{
    int fila = origen.getFila();
    int columna = origen.getColumna();
    int dir_f = (fitxa.getColor() == COLOR_BLANC) ? 1 : -1;

    bool trobatSalt = false;

    for (int dc = -1; dc <= 1; dc += 2)
    {
        int fEnemic = fila + dir_f;
        int cEnemic = columna + dc;
        int fDesti = fila + 2 * dir_f;
        int cDesti = columna + 2 * dc;

        if (posicioValida(Posicio(fEnemic, cEnemic)) && posicioValida(Posicio(fDesti, cDesti)))
        {
            Fitxa enemiga = tauler[fEnemic][cEnemic];
            Fitxa desti = tauler[fDesti][cDesti];

            if (!enemiga.esBuida() && enemiga.getColor() != fitxa.getColor() && desti.esBuida() && !visitat[fDesti][cDesti])
            {
                Posicio novaPosicio(fDesti, cDesti);
                posicionsPossibles[nPosicions++] = novaPosicio;
                visitat[fDesti][cDesti] = true;
                exploraSaltNormal(novaPosicio, fitxa, visitat, nPosicions, posicionsPossibles);
                trobatSalt = true;
            }
        }
    }
}


void Tauler::exploraSaltDama(const Posicio& origen, const Fitxa& fitxa, bool visitat[8][8], int& nPosicions, Posicio posicionsPossibles[])
{
    int dirs[4][2] = { {1,1}, {-1,1}, {1,-1}, {-1,-1} };
    for (int d = 0; d < 4; ++d)
    {
        int dir_f = dirs[d][0];
        int dir_c = dirs[d][1];
        int f = origen.getFila() + dir_f;
        int c = origen.getColumna() + dir_c;
        bool trobat = false;

        while (posicioValida(Posicio(f, c)))
        {
            Fitxa fActual = tauler[f][c];
            if (!trobat)
            {
                if (!fActual.esBuida() && fActual.getColor() != fitxa.getColor())
                    trobat = true;
                else if (!fActual.esBuida())
                    break;
            }
            else
            {
                if (fActual.esBuida() && !visitat[f][c])
                {
                    Posicio novaPosicio(f, c);
                    posicionsPossibles[nPosicions++] = novaPosicio;
                    visitat[f][c] = true;
                    exploraSaltDama(novaPosicio, fitxa, visitat, nPosicions, posicionsPossibles);
                    break;
                }
                else
                    break;
            }
            f += dir_f;
            c += dir_c;
        }
    }
}
