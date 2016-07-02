#include <iostream>
using namespace std;

int main(){
	
	int players, rounds, D, Dinicial, sumaOtros, B;
	while(cin>>players>>rounds){
		int total = 0;
		for(int i=0; i<rounds; ++i){
			cin>>B>>D;
			Dinicial = D;
			sumaOtros = 0;
			for(int i=0; i<players-1; ++i){
				int a;
				cin>>a;
				sumaOtros+=a;
			}

			if(D+sumaOtros < B)
				while((D*10)+sumaOtros <= B && (D*10) <= 10000) D *= 10;
				
			else if(D+sumaOtros > B)
				while(D+sumaOtros > B && (D/10) >= 1) D /= 10; 

			if(D + sumaOtros > B){
				// No gana puntos extra
			} else

			if(Dinicial > D) total += D;
			else total += D-Dinicial;
		}
		cout << total << endl;
	}
	return 0;
}