// Author: Borja Guanche Sicilia
// Mail: bg.sicilia@gmail.con
// Date: 15/11/2020
// File funcionesObstáculos.cpp: Desarrollo funciones para generar obstáculos según un porcentaje (%).


#include <iostream>
#include <vector>
#include <utility>


std::vector<std::pair<int, int>> posicionesAleatorias (float porcentaje, int dimension);
int retornarObstaculos (std::pair<int, int> posicion, std::vector<std::pair<int, int>> vectorPosicionesAleatorias);
    

//  Generamos un vector con las posiciones que van a tener obstaculos, según un porcentaje 
//  solicitado y un tamaño de ciudad.

std::vector<std::pair<int, int>> posicionesAleatorias (float porcentaje, int dimension) {
	
	std::vector<std::pair<int, int>> vectorPosicionesAlt;
	std::pair<int, int> posicion;
	int totalObstaculos = (((dimension*dimension) - 2) * (porcentaje / 100));
	
	for (int i = 0; i <= totalObstaculos; i++) {
		
		posicion.first = rand() % dimension;
		posicion.second = rand() % dimension;
		vectorPosicionesAlt.push_back(posicion);
	}
	
	return vectorPosicionesAlt;
}



//  Buscamos si en esa posición hay un obstáculo (que se encuentran almacenanos en el vector de pares 
//  generado mediante la función anterior.

int retornarObstaculos (std::pair<int, int> posicion, std::vector<std::pair<int, int>> vectorPosicionesAleatorias) {

    for (int k = 0; k <= vectorPosicionesAleatorias.size() - 1; k++) {
        if ((posicion.first == (vectorPosicionesAleatorias[k].first)) && (posicion.second == (vectorPosicionesAleatorias[k].second))) {
            return 1;
            vectorPosicionesAleatorias.erase(vectorPosicionesAleatorias.begin() + k);
		}

	}

    return 0;
}