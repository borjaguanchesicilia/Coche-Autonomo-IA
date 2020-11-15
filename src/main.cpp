// Author: Borja Guanche Sicilia
// Mail: bg.sicilia@gmail.con
// Date: 15/11/2020
// File main.cpp:


#include "coche.cpp"
#include <utility>
#include <time.h>




int main() {

    int modo, tam, tipo, m, n, fHeuristica, caminoOptimo;
    std::string nombreFichero;
    bool inicio = true;
    float obstaculos;
    std::vector<std::tuple<int, int, float, float, float, int, int>> camino;
    std::vector<std::pair<int, int>> vectorPosicionesAleatorias, rutaOptima;
    std::pair<int, int> posicionDeSalida, posicionDeLlegada, posicionPadre;
    srand(time(NULL));

    std::cout<<"\n\n\t\t Práctica 1: Estrategias de búsquedas. \n\n";
    std::cout<<"\n\n\t ¿Quiere una ciudad fichero (0) o (ciudad manual | aleatoria) (1)? "; std::cin>>modo;
    
    if ((modo == 0) || (modo == 1)) {}
	else {
		std::cout<<"\n\n\t Saliendo del programa, ha introducido un numero distinto de 0 | 1. \n\n";
        return 0;
	}


    switch (modo) {
        
        case 0: {   // Ciudad mediante fichero.

            nombreFichero = "../ficherosCiudades/200.txt";
            ciudad A(nombreFichero);

            posicionDeSalida = std::make_pair(std::get<0>(A.posicionesCoche), std::get<1>(A.posicionesCoche));
            posicionDeLlegada = std::make_pair(std::get<2>(A.posicionesCoche), std::get<3>(A.posicionesCoche));
            coche B(posicionDeSalida, posicionDeLlegada);

            //A.mostrarCiudad();

            std::cout<<"\n\n\t Introduzca qué función heuristica quiere utilizar Distancia Euclídea (0) o Distancia Manhattan (1): ";std::cin>>fHeuristica;
    		
			if ((fHeuristica == 0) || (fHeuristica == 1)) {}
			else {
				std::cout<<"\n\n\t Saliendo del programa, ha introducido un numero distinto de 0 | 1. \n\n";
        		return 0;
			}
			
    		clock_t t;
    		t = clock();
            camino = B.algoritmoBusquedaEstrella(A, inicio, fHeuristica);
			      
            posicionPadre.first = posicionDeLlegada.first;
            posicionPadre.second = posicionDeLlegada.second;
              
			for (int k = 0; k  <= camino.size()-1; k++){
   
   				posicionPadre = buscarPadre(camino, posicionPadre);
   				rutaOptima.push_back(posicionPadre);     
            }

            for (int i = 0; i  <= rutaOptima.size()-1; i++){
        
                if (((rutaOptima[i].first == posicionDeSalida.first) && (rutaOptima[i].second == posicionDeSalida.first))) {
                    A.mapa[rutaOptima[i].first][rutaOptima[i].second] = 2; 
                }
                else if (((rutaOptima[i].first == posicionDeLlegada.first) && (rutaOptima[i].second == posicionDeLlegada.first))) {
                	 A.mapa[rutaOptima[i].first][rutaOptima[i].second] = 3; 	
				}
                else {
                    A.mapa[rutaOptima[i].first][rutaOptima[i].second] = 4; 
                }
            }
            
            t = clock() - t;
            caminoOptimo = B.rutaOptima(A);
			std::cout << "\n\n\t El nº de nodos expandidos es:          |           " << "El nº de nodos del camino es:         |           " << "El tiempo de ejecución es:   ";
			std::cout << "\n\n\t 	 " << B.contNodos  << " nodos.                      |                       " << caminoOptimo << " nodos.                 |                 " << float(t)/CLOCKS_PER_SEC << " segundos. \n\n";
            //A.mostrarCiudad();
        }
        break;

        
        case 1: { // Ciudad manual | aleatoria. 

            std::cout<<"\n\n\t Introduzca el tamaño de la ciudad: "; std::cin>>tam;
            std::cout<<"\n\n\t ¿Quiere una ciudad manual (0) o ciudad aleatoria (1)? "; std::cin>>tipo;

            if (tipo == 0) { // Ciudad generada manualmente por el usuario.

                std::cout<<"\n\n\t La ciudad será diseñada manualmente. ";
                std::cout<<"\n\n\t El tamaño de la ciudad es: " << tam;
            } 
            else if(tipo == 1) { // Ciudad generada aleatoriamente.

                std::cout<<"\n\n\t La ciudad será diseñada aleatoriamente. ";
                std::cout<<"\n\n\t El tamaño de la ciudad es: " << tam;
                std::cout<<"\n\n\t Introduzca el porcentaje de obstáculos: "; std::cin>>obstaculos;
                vectorPosicionesAleatorias = posicionesAleatorias(obstaculos, tam);
            } 
            else {

                std::cout<<"\n\n\t Saliendo del programa, ha introducido un numero distinto de 0 | 1. \n\n";
                return 0;
            }

            std::cout<<"\n\n\t Introduzca la posición de partida del coche [i]:  ";std::cin>>m;
            std::cout<<"\n\n\t Introduzca la posición de partida del coche [j]:  ";std::cin>>n;
            if ((m | n) < 0) {
                std::cout<<"\n\n\t Saliendo del programa, ha introducido una posición menor que la dimensión. \n\n";
                return 0;
            }
            else if ((m | n) > tam) {
                std::cout<<"\n\n\t Saliendo del programa, ha introducido una posición mayor que la dimensión. \n\n";
                return 0;  
            }

            posicionDeSalida.first = m;
            posicionDeSalida.second = n;

            std::cout<<"\n\n\t Introduzca la posición de llegada del coche [i]:  ";std::cin>>m;
            std::cout<<"\n\n\t Introduzca la posición de llegada del coche [j]:  ";std::cin>>n;

            if ((m | n) < 0) {
                std::cout<<"\n\n\t Saliendo del programa, ha introducido una posición menor que la dimensión. \n\n";
                return 0;
            }
            else if ((m | n) > tam) {
                std::cout<<"\n\n\t Saliendo del programa, ha introducido una posición mayor que la dimensión. \n\n";
                return 0;  
            }

            posicionDeLlegada.first = m;
            posicionDeLlegada.second = n;
    
            ciudad A(tam, tipo, posicionDeSalida, posicionDeLlegada, vectorPosicionesAleatorias);

            coche B(posicionDeSalida, posicionDeLlegada);

            A.mostrarCiudad();

            std::cout<<"\n\n\t Introduzca qué función heuristica quiere utilizar Distancia Euclídea (0) o Distancia Manhattan (1): ";std::cin>>fHeuristica;
            
            if ((fHeuristica == 0) || (fHeuristica == 1)) {}
			else {
				std::cout<<"\n\n\t Saliendo del programa, ha introducido un numero distinto de 0 | 1. \n\n";
        		return 0;
			}

    		clock_t t;
    		t = clock();
            camino = B.algoritmoBusquedaEstrella(A, inicio, fHeuristica);
					           
            posicionPadre.first = posicionDeLlegada.first;
            posicionPadre.second = posicionDeLlegada.second;
              
			for (int k = 0; k  <= camino.size()-1; k++){
   
   				posicionPadre = buscarPadre(camino, posicionPadre);
   				rutaOptima.push_back(posicionPadre);     
            }

            for (int i = 0; i  <= rutaOptima.size()-1; i++){
        
                if (((rutaOptima[i].first == posicionDeSalida.first) && (rutaOptima[i].second == posicionDeSalida.first))) {
                    A.mapa[rutaOptima[i].first][rutaOptima[i].second] = 2; 
                }
                else if (((rutaOptima[i].first == posicionDeLlegada.first) && (rutaOptima[i].second == posicionDeLlegada.first))) {
                	 A.mapa[rutaOptima[i].first][rutaOptima[i].second] = 3; 	
				}
                else {
                    A.mapa[rutaOptima[i].first][rutaOptima[i].second] = 4; 
                }
            }
            
            t = clock() - t;
            caminoOptimo = B.rutaOptima(A);
			std::cout << "\n\n\t El nº de nodos expandidos es:          |           " << "El nº de nodos del camino es:         |           " << "El tiempo de ejecución es:   ";
			std::cout << "\n\n\t 	 " << B.contNodos  << " nodos.                      |                       " << caminoOptimo << " nodos.                 |                 " << float(t)/CLOCKS_PER_SEC << " segundos. \n\n";
            A.mostrarCiudad();
        }
        break;
    
        default:
        break;
    }

    return 0;
}