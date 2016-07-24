#include <bits/stdc++.h>

using namespace std;

int grafo[202][202], colores[202], precios[202];

enum { DSP, PPP };

class objeto{
public:
	int cuantas_d, cuantas_p, costo_total, valor;
	objeto(): cuantas_p(0), cuantas_d(0), costo_total(0){}
};

// n = cantidad de objetos
// W = capacidad total del knapsack
// objs = vector de objetos (tiene que tener dos atributos al menos, valor y costo)
int knapSack(int n, int W, vector<objeto> &objs){
   int i, w;
   int K[n+1][W+1];
   for (i = 0; i <= n; i++){
       for (w = 0; w <= W; w++){
           if (i==0 || w==0)
               K[i][w] = 0;
           else if (objs[i-1].costo_total <= w)
                 K[i][w] = max(objs[i-1].valor + K[i-1][w-objs[i-1].costo_total],  K[i-1][w]);
           else
                 K[i][w] = K[i-1][w];
       }
   } 
   return K[n][W];
}


int main(){
	int D, P, R, B, i;

	while(cin>>D>>P>>R>>B){

		for(i=0; i<202; i++) 
			fill(grafo[i], grafo[i]+202, 0);

		for(i=0; i<D; ++i){
			cin>>precios[i];
			colores[i] = DSP;
		}

		for(; i<P+D; ++i){
			cin>>precios[i];
			colores[i] = PPP;
		}


		for(int i=0; i<R; ++i){
			int a,b;
			cin>>a>>b;
			--a; --b;
			grafo[a][b+D] = grafo[b+D][a] = 1;			
		} // lectura del grafo

		vector<objeto> todos_objs;

		bool visitados[D+P]={false};

		// Crear los objetos, cada objeto es una componente conexa del grafo. Incluso si hay
		// solo un nodo, se toma como componente conexa y se agrega como objeto.
		for(int i=0; i<D+P; i++){

			if(visitados[i]) continue;
			visitados[i] = true;

			objeto obj; // nuevo objeto, una componente conexa del grafo
			queue<int> cola;
			cola.push(i);

			while(!cola.empty()){

				int nodo = cola.front(); cola.pop();				

				obj.costo_total += precios[nodo]; // agregar costo a la componente conexa

				if(colores[nodo] == DSP)
					obj.cuantas_d++;
				else
					obj.cuantas_p++;
				
				for(int j=0; j<D+P; j++){ // Ver sus vecinos
					if(!visitados[j] && grafo[nodo][j] == 1 && nodo!=j){
						visitados[j] = true;
						cola.push(j);
					}
				}
			}			
			todos_objs.push_back(obj);
		}

		int dsp_cuenta = 0, ppp_cuenta = 0;
		vector<objeto> dsp, ppp;

		// Luego de crear todos los objetos, hay que filtrarlos para cada crear distintos
		// grupos de objetos que se puedan comprar. Por eso no se ponen los que no le agreguen nodos,
		// ni tampoco los que quiten. Solo se ponen los que agregan nodos a un partido politico.

		// Este codigo mapea el problema a un knapsack que se resuelve con programacion dinamica.
		// la idea es tener varios objetos con un valor y costo, en este caso el costo es el dinero
		// total requerido para comprar toda la componente conexa, y el valor, es la cantidad de nodos
		// extra que se adquieren al comprar la componente.
		
		for(int i=0; i<todos_objs.size(); i++){
			objeto o = todos_objs[i];
			ppp_cuenta += o.cuantas_p; // se guarda cuantos politicos hay sin necesidad de comprar
			dsp_cuenta += o.cuantas_d; // nada (es decir, es el numero base)

			if(o.cuantas_p > o.cuantas_d){				
				objeto new_obj;
				new_obj.valor = o.cuantas_p - o.cuantas_d;
				new_obj.costo_total = o.costo_total;
				dsp.push_back(new_obj);
			}
			else if(o.cuantas_p < o.cuantas_d){				
				objeto new_obj;
				new_obj.valor = o.cuantas_d - o.cuantas_p;
				new_obj.costo_total = o.costo_total;
				ppp.push_back(new_obj);
			}
		}

		cout << dsp_cuenta + knapSack(dsp.size(), B, dsp);
		cout << " ";
		cout << ppp_cuenta + knapSack(ppp.size(), B, ppp);
		cout << endl;
	}
	return 0;
}