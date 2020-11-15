// Author: Borja Guanche Sicilia
// Mail: bg.sicilia@gmail.con
// Date: 15/11/2020
// File funcionesBusqueda.cpp: Desarrollo funciones para ayudar a la búsqueda A*.


#include <iostream>
#include <vector>
#include <tuple>
#include <utility>
#include <math.h>


std::tuple<bool, int> comprobarLista(std::vector<std::tuple<int, int, float, float, int, int>> lista, std::pair<int, int> posicion);
float calcularDistanciaEuclidea(std::pair<int, int> posicion, std::pair<int, int> posicionLlegada);
float calcularDistanciaManhattan(std::pair<int, int> posicion, std::pair<int, int> posicionLlegada);
std::pair<int, int> buscarPadre(std::vector<std::tuple<int, int, float, float, float, int, int>> camino, std::pair<int, int> hijo);


//  Comprobamos si una posicion de la ciudad está en la lista abierta o cerrada. Se le 
//  deberá de pasar la lista y la posición a comprobar.
std::tuple<bool, int> comprobarLista(std::vector<std::tuple<int, int, float, float, float, int, int>> lista, std::pair<int, int> posicion) {

    std::tuple<bool, int> tupla;

    if (lista.empty()) {
        
        tupla = std::make_tuple(false, 0);
        return tupla;
    }
 
    for (int i = 0; i <= lista.size(); i++) {
        if ((std::get<0>(lista[i]) == posicion.first) && (std::get<1>(lista[i]) == posicion.second)) { 
            
            tupla = std::make_tuple(true, i);
            return tupla;
        }
    }

    return tupla;
}


//  Cálculo de la distancia Euclidea.

float calcularDistanciaEuclidea(std::pair<int, int> posicion, std::pair<int, int> posicionLlegada) {
    
    float dEuclidea;
    dEuclidea = sqrt(pow((posicionLlegada.first - posicion.first),2) + pow((posicionLlegada.second - posicion.second),2));
    return dEuclidea;
}


// Cálculo de la distancia Manhattan.

float calcularDistanciaManhattan(std::pair<int, int> posicion, std::pair<int, int> posicionLlegada) {

    float dManhattan;
    dManhattan = (abs(posicion.first - posicionLlegada.first) + abs(posicion.second - posicionLlegada.second));
    return dManhattan;
}


// Función que busca el padre de una celda, y lo retorna en forma de par de datos.

std::pair<int, int> buscarPadre(std::vector<std::tuple<int, int, float, float, float, int, int>> camino, std::pair<int, int> hijo) {
	
	for (int k = 0; k  <= camino.size()-1; k++){
   
   		if ((hijo.first == std::get<0>(camino[k])) && (hijo.second == std::get<1>(camino[k]))) {
   					
   			return (std::make_pair(std::get<5>(camino[k]), std::get<6>(camino[k])));	// Retorna el par de datos con el padre del nodo 
		}            
    }	

    return (std::make_pair(NULL, NULL));	// Retorna un pair NULL
}