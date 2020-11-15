// Author: Borja Guanche Sicilia
// Mail: bg.sicilia@gmail.con
// Date: 15/11/2020
// File coche.cpp: Desarrollo clase coche.


#include "../include/coche.hpp"


coche::coche() {}


coche::coche(std::pair<int, int> posIni, std::pair<int, int> posFin) {

    posicionInicio.first = posIni.first;
    posicionInicio.second = posIni.second;
    posicionDestino.first = posFin.first;
    posicionDestino.second = posFin.second;
}


coche::~coche() {}


//  Algoritmo A*

std::vector<std::tuple<int, int, float, float, float, int, int>> coche::algoritmoBusquedaEstrella(ciudad A, bool inicio, int fHeuristica) { 

    std::vector<std::tuple<int, int, float, float, float, int, int>> listaCerrada, listaAbierta, error; 
    std::vector<std::pair<int, int>> listaFinal;

    std::tuple<int, int, float, float, float, int, int> celdaAExpandir, celdaExpandida;
    std::tuple<int, int, int> celdaAux;

    std::pair<int, int> posPadre,posHija, posHijaAnterior, nodoHijo;

    float funcionCoste, funcionHeuristica, funcionEvaluacion; 
    funcionCoste = funcionHeuristica = funcionEvaluacion = 0.0;

    int menor, k, contador, modo;
    contador = 0;


    //  Establacemos como posición actual la posición de salida y el nodo padre.

    posicionActual.first = posicionInicio.first;
    posicionActual.second = posicionInicio.second;


    //  Calculamos función de evañuación de la posicón inicial

    if (fHeuristica == 0) {

        funcionHeuristica = calcularDistanciaEuclidea(posicionActual, posicionDestino);
    }
    else {

        funcionHeuristica = calcularDistanciaManhattan(posicionActual, posicionDestino);
    }
    funcionEvaluacion = funcionHeuristica;


    //  Almacenamos en la lista abierta la posición inicial con su información

    listaAbierta.push_back(std::make_tuple(posicionActual.first, posicionActual.second, funcionCoste, funcionHeuristica, funcionEvaluacion, posicionActual.first, posicionActual.second));
	
	contNodos = 1;
    
    while (!listaAbierta.empty()) {

        menor = 999999999;
        for (int i = 0; i <= listaAbierta.size()-1; i++) {
    
            if (menor > std::get<4>(listaAbierta[i])) {
                menor = std::get<4>(listaAbierta[i]);
                
                k = i;  //  k = indice de la lista abierta del nodo con menor f(n)
            }
        }

        if ((std::get<0>(listaAbierta[k]) == posicionDestino.first) && (std::get<1>(listaAbierta[k]) == posicionDestino.second)) {

            return listaCerrada;
        }
        else {

            // Hacemos una copia de la celda que seleccionada a expandirse

            celdaAExpandir = listaAbierta[k];

            posicionActual.first = std::get<0>(listaAbierta[k]);
            posicionActual.second = std::get<1>(listaAbierta[k]);

            // Indicamos cual es la posición de la celda padre (para calcular despues sus hijas: N,S,E,O)

            posPadre.first = std::get<0>(celdaAExpandir);
            posPadre.second = std::get<1>(celdaAExpandir);


            // Metemos en la lista cerrada la celda seleccionada a expandirse

            listaCerrada.push_back(celdaAExpandir);

            // Sacamos de la lista abierta la celda seleccionada a expandirse

            listaAbierta.erase(listaAbierta.begin() + k);

            for (int i = 0; i <= 3; i++){

                //  Hacemos una copia de la celda expandida

                celdaAux = A.retornarPosicion(posPadre, i);  // Se recoge la posicion de (N,S,E,O) y valor
                posHija.first = std::get<0>(celdaAux); //   alamceno i de (N,S,E,O)
                posHija.second = std::get<1>(celdaAux); //  alamceno j de (N,S,E,O)

            
                if ((posHija.first == posicionDestino.first) && (posHija.second == posicionDestino.second)){
                
                    std::cout << "\n\n\t Se ha llegado al objetivo. \n\n";
                    modo = 1;
                    listaCerrada.push_back(std::make_tuple(posicionDestino.first, posicionDestino.second, funcionCoste + 1.0  , 0.0, funcionEvaluacion, posicionActual.first, posicionActual.second));
                    return listaCerrada;
                }
                else if (std::get<2>(celdaAux) == 1) {
                
                    contador++;
                    continue;
                }
                else if (contador == 4) {

                    std::cout << "\n\n\t FALLO: Problema sin solución. \n\n";
                    exit(0);
                }
                else if (std::get<2>(celdaAux) != 1) { //   No es un obstáculo, ni el objetivo

                    contador = 0;

                    if ((std::get<0>(comprobarLista(listaCerrada, posHija))) == false) {

                        funcionCoste = 1.0;
                        if (fHeuristica == 0) {
                            funcionHeuristica = calcularDistanciaEuclidea(posHija, posicionDestino);
                        }
                        else {
                            funcionHeuristica = calcularDistanciaManhattan(posHija, posicionDestino);
                        }
                        
                        funcionEvaluacion = funcionCoste + funcionHeuristica;


                        if ((std::get<0>(comprobarLista(listaAbierta, posHija))) == true) {

                            if (std::get<2>(listaAbierta[std::get<1>(comprobarLista(listaAbierta, posHija))]) > funcionEvaluacion) {
                                
                                std::get<2>(listaAbierta[std::get<1>(comprobarLista(listaAbierta, posHija))]) = funcionEvaluacion;
                            }
                        }
                        else {

                            celdaExpandida = std::make_tuple(posHija.first, posHija.second, funcionCoste, funcionHeuristica, funcionEvaluacion, posicionActual.first, posicionActual.second);
                            listaAbierta.push_back(celdaExpandida);
                            posHijaAnterior.first = posHija.first;
                            contNodos = contNodos + 1;
                        }
                    }
                }
            }
        }   
    }

    return error;    
}


//  Método que devulv el número de nodos que hemos recorrido.

int coche::rutaOptima(ciudad A) {

    int camino = 0;

    for (int i = 0; i  <= A.dimension; i++){
        for (int j = 0; j <= A.dimension; j++) {    
            if (A.mapa[i][j] == 4) {
                camino++;
            }   

        }
    }

    return camino + 1;
}