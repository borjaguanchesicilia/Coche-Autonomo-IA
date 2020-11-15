// Author: Borja Guanche Sicilia
// Mail: bg.sicilia@gmail.con
// Date: 15/11/2020
// File coche.hpp: Definición clase coche.   

#include <utility>
#include <tuple>
#include <fstream>
#include "../src/ciudad.cpp"
#include "../src/funcionesBusqueda.cpp"

class coche {

    private:

        std::pair<int, int> posicionInicio;
        std::pair<int, int> posicionDestino;
        std::pair<int, int> posicionActual;
        std::vector<std::pair<int, int>> caminoOptimo;

    public:
    	
		int contNodos;
        coche();
        coche(std::pair<int, int> posIni, std::pair<int, int> posFin);
        ~coche();
        std::vector<std::tuple<int, int, float, float, float, int, int>> algoritmoBusquedaEstrella(ciudad A, bool inicio, int fHeuristica);
        int rutaOptima(ciudad A);
};
