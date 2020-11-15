// Author: Borja Guanche Sicilia
// Mail: bg.sicilia@gmail.con
// Date: 15/11/2020
// File ciudad.cpp: Desarrollo clase ciudad. 


#include "../include/ciudad.hpp"


ciudad::ciudad() {}


//  Constructor de la ciudad para entrada manual y aleatoria.

ciudad::ciudad(int tam, int tipo, std::pair<int, int> posIni, std::pair<int, int> posFin, std::vector<std::pair<int, int>> vectorPosicionesAleatorias) {

    int var;

    dimension = tam + 1;

    if (tipo == 0) {
        std::cout<<"\n\n\t Debe solo introducir (0) si queremos celda vacía o (1) si queremos celda ocupada.";
        std::cout<<"\n\n\t En caso de que sea la posición de salida o la de destino ponga un (1) o un (0) indistintamente.";    
    }

    for (int i = 0; i  <= dimension; i++){
        std::vector<int> Calle;
        for (int j = 0; j <= dimension; j++) {
            if (tipo == 0) {
                if ((i == 0) || (i == dimension) || (j == 0) || (j == dimension)) {
                    var = 1;
                }
                else {
                    std::cout<<"\n\n\t Introduzca el dato de la pos [" << i << "]  [" << j << "] :";std::cin>> var;
                    if ((var == 0) || (var == 1)) {
                        std::cout<<"\n\n\t Dato: " << var << ".";
                    }   
                    else {
                        std::cout<<"\n\n\t var = " << var << " no es correcto.";
                        std::cout<< "\n\n\t Error, ha introducido un caracter distinto a 0 | 1. Saliendo del programa...\n\n";
                        exit(0);
                    }
                }
            } 
            else {

                std::pair<int, int> posicion;
                posicion = std::make_pair(i,j);
                var = retornarObstaculos(posicion, vectorPosicionesAleatorias);
            }
            if ((i == posIni.first) && (j == posIni.second)) {
                var = 2;    //  Salida del coche.
            }
            else if ((i == posFin.first) && (j == posFin.second)) {
                var = 3;    //  Llegada del coche.
            }
            else if ((i == 0) || (i == dimension) || (j == 0) || (j == dimension)) {
                var = 1;
            }
            
            Calle.push_back(var);
            
        }
        mapa.push_back(Calle);
    }
}


//  Constructor de la ciudad para entrada por fichero.

ciudad::ciudad(std::string nombreFichero) {

    std::ifstream input(nombreFichero); 
    std::string var;
    std::pair<int, int> posicionInicio, posicionDestino;
    int tam, val;

    if (!input.is_open()) {
        exit(0); 
    }
  
    input >> var;
    tam = std::stoi(var);
    dimension = tam + 1;
    
    for (int i = 0; i <= dimension; i++){
        std::vector<int> calle;
        for (int j = 0; j <= dimension; j++){
            if ((i == 0) || (i == dimension) || (j == 0) || (j == dimension)) {
                calle.push_back(1);
            }
            else {
                input >> var;
                if (var == "1" || var == "0") {
                    val = std::stoi(var);
                    calle.push_back(val);
                }
                else if (var == "I") {
                    posicionInicio = std::make_pair(i, j);
                    calle.push_back(2);
                }
                else if (var == "F") {
                    posicionDestino = std::make_pair(i, j);
                    calle.push_back(3);
                }
            } 
        }
        mapa.push_back(calle);
    }
    posicionesCoche = std::make_tuple(posicionInicio.first, posicionInicio.second, posicionDestino.first, posicionDestino.second);
}


ciudad::~ciudad() {

    mapa.clear();
    dimension = 0;
  
}


//  Método para mostrar la ciudad. 

void ciudad::mostrarCiudad() {

    std::cout<< "\n\n\t La ciudad es:  \n\n";

    for (int i = 0; i  <= dimension; i++){
        std::cout<< "\t  ";
        for (int j = 0; j <= dimension; j++) {
            if (mapa[i][j] == 1) {
                std::cout<< "X";   
            } 
            else if (mapa[i][j] == 2) {
                std::cout<< "I"; 
            } 
            else if (mapa[i][j] == 3) {
                std::cout<< "F"; 
            }     
            else if (mapa[i][j] == 4) {
                std::cout<< "."; 
            }   
            else {
                std::cout<< " "; 
            }
        }
        std::cout<<"\n";
    }
}


//  Método que devulve una tupla con la información de la celda hija perteneciente a la celda a expandirse.

std::tuple<int, int, int> ciudad::retornarPosicion(std::pair<int, int> posAct, int posSiguiente){

    std::tuple<int, int, int> datosSensores; // i, j, valor
    int norte, sur, este, oeste;

    for (int i = 0; i  <= dimension; i++){
        for (int j = 0; j <= dimension; j++) {
            if ((i == posAct.first) && (j == posAct.second)) {

                norte = i-1;
                sur = i + 1;
                este = j + 1;
                oeste = j - 1;

                if (posSiguiente == 0) { datosSensores = std::make_tuple(norte, j, mapa[norte][j]); //  posSiguiente = 0 --> NORTE
                } else if (posSiguiente == 1) { datosSensores = std::make_tuple(sur, j, mapa[sur][j]); //   posSiguiente = 1 --> SUR
                } else if (posSiguiente == 2) { datosSensores = std::make_tuple(i, este, mapa[i][este]); // posSiguiente = 2 --> ESTE
                } else { datosSensores = std::make_tuple(i, oeste, mapa[i][oeste]);} // posSiguiente = 3 --> OESTE
            } 
            
        }
    }

    return datosSensores;
}