#include <bits/stdc++.h>
using namespace std;

// BIT with range updates, inspired by Petr Mitrichev
struct BIT {
    int n;
    vector<int> slope;
    vector<int> intercept;
    // BIT can be thought of as having entries f[1], ..., f[n]
    // which are 0-initialized
    BIT(int n): n(n), slope(n+1), intercept(n+1) {}
    // returns f[1] + ... + f[idx-1]
    // precondition idx <= n+1
    int query(int idx) {
        int m = 0, b = 0;
        for (int i = idx-1; i > 0; i -= i&-i) {
            m += slope[i];
            b += intercept[i];
        }
        return m*idx + b;
    }
    // adds amt to f[i] for i in [idx1, idx2)
    // precondition 1 <= idx1 <= idx2 <= n+1 (you can't update element 0)
    void update(int idx1, int idx2, int amt) {
        for (int i = idx1; i <= n; i += i&-i) {
            slope[i] += amt;
            intercept[i] -= idx1*amt;
        }
        for (int i = idx2; i <= n; i += i&-i) {
            slope[i] -= amt;
            intercept[i] += idx2*amt;
        }
    }
};

class punto{
public:
	int x, y, valor;
	punto(int v) : valor(v){
		cin>>x>>y;
	}
};

int P, V;

int main(){
	
	while(cin>>P>>V){

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

		BIT fenwick(y_comprimido + 7);

		long long int valor = 0;

		for(int i=0; i<puntos.size(); i++){

			punto p1 = puntos[i];

			if(p1.valor == -1){ // El punto p1 es un vertice

				punto p2 = puntos[++i]; // Se toma tambien el otro punto

				// Se tiene un intervalo p1 a p2.
				// Incrementar +1 al intervalo.
				fenwick.update(p1.y, p2.y, 1);

			} else {

				// El punto es una planta
				
				// Se tira una linea desde afuera del poligono hacia el punto de la planta,
				// y se cuenta cuantas veces intersecta el poligono, si es un numero impar,
				// entonces esta dentro. (Esto es lo mismo que prender y apagar el rango
				// del fenwick tree, 0=par/fuera, 1=impar/dentro)
				int intersecciones = fenwick.query(p1.y+1) - fenwick.query(p1.y); 

				if(intersecciones % 2 == 0) valor += p1.valor;
						
			}
		}

		printf("%lld\n", valor);
	}
	return 0;
}