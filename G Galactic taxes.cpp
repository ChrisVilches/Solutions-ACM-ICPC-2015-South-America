#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
#define INF 10e9

int nodos, conexiones;

class arista{ // arista para el grafo
public:
	ld A;
	ld B;
	int nodo;
	arista(ld _A, ld _B, int _nodo) : A(_A), B(_B), nodo(_nodo){}
	ld get_peso(ld tiempo){
		return (A*tiempo) + B;
	}
};


class par{ // par nodo-distancia para el dijkstra
public:
	int n;
	ld dist;
	par(int no, ld _dist):n(no), dist(_dist){}
	friend bool operator <(const par& p1, const par& p2){
		return p1.dist > p2.dist;
	}
};

// Entrada: grafo como lista de adyacencias, y el tiempo.
ld dijkstra(vector<arista> grafo[], ld tiempo){
	ld dist[nodos];
	bool vis[nodos];
	fill(dist, dist+nodos, INF);
    fill(vis, vis+nodos, false);

	priority_queue<par> q;
	q.push(par(0, 0));
	while(!q.empty()){
		par top = q.top();
		q.pop();
		int u = top.n;
		ld peso = top.dist;

		if(vis[u]) continue;

		dist[u] = peso;
		vis[u] = true;

		for(arista ady : grafo[u]){ 
			int v = ady.nodo; 
			if(!vis[v]){
				ld alt = dist[u] + ady.get_peso(tiempo);
				if(alt < dist[v]){
					dist[v] = alt;
					q.push(par(v, dist[v]));
				}
			}
		} 
	}
	return dist[nodos-1];
}

int main(){

	while(cin>>nodos>>conexiones){

		vector<arista> grafo[nodos]; // grafo = listas de adyacencias

		for(int i=0; i<conexiones; i++){ // construir el grafo
			int nodo1, nodo2;
			ld A, B;
			cin>>nodo1>>nodo2>>A>>B;
			nodo1--; nodo2--;
			grafo[nodo1].push_back(arista(A, B, nodo2));
			grafo[nodo2].push_back(arista(A, B, nodo1));
		}

		ld left = 0;
		ld right = 60*24;

		for(int i=0; i<80; i++){ // busqueda ternaria
			ld tercio = (right-left)/3;
			ld tercio1 = left + tercio;
			ld tercio2 = right - tercio;

			if(dijkstra(grafo, tercio1) < dijkstra(grafo, tercio2))
				left = tercio1;
			else
				right = tercio2;
		}

		printf("%.5Lf\n", dijkstra(grafo, (left+right)/2));

	} // cada caso

	return 0;
}