#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int N, Q;
int** grafo;

// Funcion auxiliar
bool bpm(int** grafo, int filas, int cols, int u, bool seen[], int matchR[]){
	for (int v = 0; v < cols; v++){
		if (grafo[u][v]==1 && !seen[v]){
			seen[v] = true; // Mark v as visited
			if (matchR[v] < 0 || bpm(grafo, filas, cols, matchR[v], seen, matchR)){
				matchR[v] = u;
				return true;
			}
		}
	}
	return false;
}

// Retorna la cantidad de aristas que tiene el bipartite matching maximal.
// El grafo contiene 'filas' numero de nodos que hay en la parte izquierda del grafo
// y contiene 'cols' cantidad de nodos en el lado derecho. Las adyacencias (dirigidas) van de
// izquierda a derecha (no es una matriz de adyacencias usual). Algoritmo es Bipartite matching + Max flow.
int maxBPM(int** grafo, int filas, int cols){
	int matchR[cols];
	fill(matchR, matchR+cols, -1);
	int result = 0; // Count of jobs assigned to applicants
	for (int u = 0; u < filas; u++){
		bool seen[cols];
		fill(seen, seen+cols, false);
		if (bpm(grafo, filas, cols, u, seen, matchR))
			result++;
	}
	return result;
}


class celula{
public:
	int cuantos;
	vector<int> antigenes;
	celula(){
		cin>>cuantos;
		for(int i=0; i<cuantos; ++i){
			int num;
			cin>>num;
			antigenes.push_back(num);
		}
		sort(antigenes.begin(), antigenes.end());
	}
};



int main(){

	grafo = new int*[100];
	for(int i=0; i<100; i++)
		grafo[i] = new int[200];
	

	while(cin>>N>>Q){

		// Crear arreglo de celulas padres
		vector<celula> padres;

		// Leer todos los padres
		for(int n=0; n<N; n++)
			padres.push_back(celula());		

		// Para cada consulta
		for(int q=0; q<Q; ++q){

			// Limpiamos el grafo copia
			for(int i=0; i<100; i++)
				fill(grafo[i], grafo[i]+200, 0);

			// Leer la celula hijo
			celula hijo;

			// Para cada padre
			for(int i=0; i<padres.size(); ++i){

				celula padre = padres[i];

				// para cada antigen del padre
				for(int antigen : padre.antigenes){

					// ver si el antigen del padre se encuentra en los del hijo
					// (tambien funciona con una busqueda lineal)
					if(binary_search(hijo.antigenes.begin(), hijo.antigenes.end(), antigen))
						grafo[i][antigen-1] = 1;
					
				}

				int ceros = N - hijo.cuantos;

				// Si el hijo tiene algun 0
				if(ceros > 0){
					// Si la celula hijo no tiene N antigenes, significa
					// que tiene algunos ceros, los cuales se pueden usar para
					// colocar ahi cualquier antigen (sirve como joker).
					// Por lo que el nodo padre se conecta con este cero, solo si
					// alguno de sus antigenes esta en la celula hijo.

					// Si el padre tiene el antigen 0, se crea una adyacencia de el padre, con todos los
					// ceros del hijo.
					if(padre.cuantos < N){
						fill(grafo[i]+100, grafo[i]+100+ceros, 1);
					} else {

						// Si el padre si tiene antigenes, se busca si esta celula padre
						// puede heredar a los ceros del hijo. Para esto se busca si alguno de los
						// antigenes del padre se encuentran en la celula hijo.

						bool encontrado = false;

						// Para cada antigen del padre
						for(int antigen : padre.antigenes){

							if(binary_search(hijo.antigenes.begin(), hijo.antigenes.end(), antigen)){
								fill(grafo[i]+100, grafo[i]+100+ceros, 1);
								encontrado = true;
								break;
							}
							if(encontrado) break;
						}
					}
				}
			} // fin para cada padre (grafo listo)

			int cantidad_aristas = maxBPM(grafo, N, 200);

			printf("%c\n", (cantidad_aristas == N)? 'Y' : 'N');

		} // para cada consulta
	} // while caso
	return 0;
}