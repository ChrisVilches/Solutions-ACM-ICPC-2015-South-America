#include <bits/stdc++.h>
using namespace std;

// A[] is the original array
// int A[] (no se usa)

// the fenwick tree maintaining the diffs initialized with 0
int diff_array[900000];
int fenwick_n;
 
// Add v to A[p]
void update(int p, int v){
	p++;
	for (; p <= fenwick_n; p += p&(-p))
		diff_array[p] += v;
}

// Add v to A[a...b] 
void update(int a, int b, int v){
	update(a, v);
	update(b + 1, -v);
}

// Return A[b]	 
int query(int b){
	b++;   
	int sum = 0;
	for(; b > 0; b -= b&(-b))
		sum += diff_array[b];
	return sum/* + A[b] ... array original, pero este es siempre 0*/;
}

class punto{
public:
	int x, y, valor;
	punto(int v) : valor(v){
		scanf("%d %d", &x, &y);
	}
};

int P, V;

int main(){
	
	while(scanf("%d %d", &P, &V) == 2){

		vector<punto> puntos;
		for(int i=0; i<P; i++) puntos.push_back(punto(i+1));
		for(int i=0; i<V; i++) puntos.push_back(punto(-1));

		// Compresion de las coordenadas Y

		sort(puntos.begin(), puntos.end(), [](const punto &p1, const punto &p2){
			return p1.y < p2.y;
		});

		int y_real = puntos[0].y;
		int y_comprimido = 3;
		puntos[0].y = y_comprimido;

		for(int i=1; i<puntos.size(); i++){
			if(puntos[i].y == y_real) puntos[i].y = y_comprimido;
			else {
				y_comprimido += 2;
				y_real = puntos[i].y;
				puntos[i].y = y_comprimido;
			}
		}

		// Orden lexicográfico
		sort(puntos.begin(), puntos.end(), [](const punto &p1, const punto &p2){
			if(p1.x == p2.x) return p1.y < p2.y;
			else return p1.x < p2.x;
		});

		long long int valor = 0;
		fenwick_n = y_comprimido+7;
		memset(diff_array, 0, sizeof(diff_array)); 

		for(int i=0; i<puntos.size(); i++){

			punto p1 = puntos[i];

			if(p1.valor == -1){ // El punto p1 es un vertice

				punto p2 = puntos[++i]; // Se toma tambien el otro punto

				// Se tiene un intervalo p1 a p2.
				// Incrementar +1 al intervalo.
				update(p1.y, p2.y, 1);

			} else {

				// El punto es una planta
				
				// Se tira una linea desde afuera del poligono hacia el punto de la planta,
				// y se cuenta cuantas veces intersecta el poligono, si es un numero impar,
				// entonces esta dentro. (Esto es lo mismo que prender y apagar el rango
				// del fenwick tree, 0=par/fuera, 1=impar/dentro)
				if(query(p1.y+1)% 2 == 0) valor += p1.valor;						
			}
		}
		printf("%lld\n", valor);
	}
	return 0;
}