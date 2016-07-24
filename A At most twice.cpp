#include <bits/stdc++.h>

using namespace std;

int num_digitos, i;
int arreglo[19];

int main(){

	string linea;
	
	while(cin>>linea){

		num_digitos = linea.length();
		for(i=0; i<num_digitos; ++i)
			arreglo[i] = linea[i]-'0';

		while(true){

			int cuenta[10] = {0};
			for(i=0; i<num_digitos; i++)
				if(++cuenta[arreglo[i]] == 3) break;

			if(i == num_digitos) break;
			int x = i;
			--arreglo[i];
			while(arreglo[i] == -1){
				arreglo[i] = 9;
				arreglo[--i]--;
			}

			for(++x; x<num_digitos; ++x)
				arreglo[x] = 9;
		}

		for(i=0; i<num_digitos; ++i)
			if(arreglo[i] != 0) break;
			
		for(; i<num_digitos; ++i)
			cout << arreglo[i];
		cout << endl;
	}

	return 0;

}