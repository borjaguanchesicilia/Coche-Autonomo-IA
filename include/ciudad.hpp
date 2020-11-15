// Author: Borja Guanche Sicilia
// Mail: bg.sicilia@gmail.con
// Date: 15/11/2020
// File ciudad.hpp: Definición clase ciudad.  


#include <iostream>
#include <vector>
#include <map>
#include <string.h>
#include "../src/funcionObstaculos.cpp"

class ciudad {

    public:

        int dimension;
        std::vector<std::vector<int>> mapa;
        std::tuple<int, int, int, int> posicionesCoche;

        ciudad();
        ciudad(int tam, int tipo, std::pair<int, int> posIni, std::pair<int, int> posFin, std::vector<std::pair<int, int>> vectorPosicionesAleatorias);
        ciudad(std::string nombreFichero);
        ~ciudad();
        void mostrarCiudad();
        std::tuple<int, int, int> retornarPosicion(std::pair<int, int> posAct, int posSiguiente);
};
