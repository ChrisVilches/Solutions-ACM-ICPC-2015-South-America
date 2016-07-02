#include <bits/stdc++.h>
using namespace std;

#define reemplazar() mejor_area = max(mejor_area, max(area_total-acum, acum));

typedef long double ld;

int num_vertices, x[100001], y[100001];


// Area entre los vertices a, b, c (indices)
ld area(int a, int b, int c){
	ld x1 = x[b] - x[a];
	ld y1 = y[b] - y[a];
	ld x2 = x[c] - x[a];
	ld y2 = y[c] - y[a];

	return abs(((x1*y2) - (y1*x2)))/2;
}

ld areaTotal(){
	ld area_total = 0;
	for(int v=2; v<num_vertices; ++v){
		area_total += area(0, v-1, v);
	}
	return area_total;
}

int main(){

	while(scanf("%d", &num_vertices) == 1){

		for(int i=0; i<num_vertices; ++i)
			scanf("%d %d", &x[i], &y[i]);

		ld area_total = areaTotal();		
		ld mitad_area = area_total/2;
		ld mejor_area = 0;
		ld acum = 0;

		for(int v=0, w=2; v<num_vertices; ++v){
			
			if(v>0) acum -= area(v-1, v, w%num_vertices);

			int primer_w = w;

			for(; w%num_vertices!=v; ++w){

				ld trozo = area(v, (w-1)%num_vertices, w%num_vertices);

				if(trozo == 0) continue;	

				if(v!=0 && primer_w == w) trozo = 0;		

				acum += trozo;

				if(acum == mitad_area){
					reemplazar();
					break; 
				}
				else if(acum > mitad_area){

					if(acum-trozo == 0 || abs(mitad_area-acum) < abs(mitad_area-(acum-trozo))){
						reemplazar(); // mantener w
					}									
					else{
						// Volver atras
						acum -= trozo;
						reemplazar();

						if(primer_w < w)
							w--;
					}					
					break; // Si acum es mayor a la mitad, siempre se hace break;
				}
			}
		}

		ld vol1 = (area_total-mejor_area)*2;
		ld vol2 = (mejor_area)*2;

		if(vol1 < vol2) swap(vol1, vol2);
	
		printf("%.0Lf %.0Lf\n", vol1, vol2);
	}

	return 0;
}