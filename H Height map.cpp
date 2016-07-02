#include <bits/stdc++.h>
using namespace std;

#define dentro(y, x) (x>=0 && y>=0 && x<C && y<R)
#define direccion(y, x) if(dentro(y, x) && matriz[y][x]==valor){cola.push(y); cola.push(x); matriz[y][x]=0;}
#define entre(a, b, v) (a < v && v < b)
#define intervalo(a,b,x,y) (entre(a,b,x) || entre(a,b,y) || entre(x,y,a) || entre(x,y,b) || (a==x && b==y))

int R, C, caras;
int matriz[101][101];

int main(){

	while(cin>>R>>C){
		for(int i=0; i<R; ++i)
			for(int j=0; j<C; ++j)
				cin>>matriz[i][j];

		caras = 5;

		// Norte sur
		for(int x=0; x<2; ++x){
			for(int i=0; i<R-1; ++i){
				for(int j=0; j<C; ++j){
					int a = matriz[i][j];
					int b = matriz[i+1][j];
					if(a < b){
						if(j == 0)
							caras++;
						else {
							int c = matriz[i][j-1];
							int d = matriz[i+1][j-1];

							if((c < d && !intervalo(c,d,a,b)) || c >= d){
								caras++;
							}
						}
					}
				}
			}

			// swap para hacerlo alreves
			for(int i=0; i<R/2; i++)
				for(int j=0; j<C; ++j)
					swap(matriz[i][j], matriz[R-i-1][j]);
		}


		// Este oeste
		for(int x=0; x<2; ++x){
			for(int j=0; j<C-1; ++j){
				for(int i=0; i<R; ++i){
					int a = matriz[i][j];
					int b = matriz[i][j+1];
					if(a < b){
						if(i== 0)
							caras++;
						else {
							int c = matriz[i-1][j];
							int d = matriz[i-1][j+1];

							if((c < d && !intervalo(c,d,a,b)) || c >= d){
								caras++;
							}
						}
					}
				}
			}
			for(int j=0; j<C/2; j++)
				for(int i=0; i<R; i++)
					swap(matriz[i][j], matriz[i][C-j-1]);
		}

		// Caras desde arriba (BFS)
		for(int i=0; i<R; ++i){
			for(int j=0; j<C; ++j){
				if(matriz[i][j] != 0){
					caras++;
					int valor = matriz[i][j];
					matriz[i][j] = 0;
					queue<int> cola;
					cola.push(i);
					cola.push(j);
					while(!cola.empty()){
						int y = cola.front(); cola.pop();
						int x = cola.front(); cola.pop();
						direccion(y, x+1);
						direccion(y, x-1);
						direccion(y+1, x);
						direccion(y-1, x);
					}
				}
			}
		}
		cout << caras << endl;
	}
	return 0;
}