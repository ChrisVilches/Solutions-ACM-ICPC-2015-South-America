#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

ll mod = 1e9+7;
ll memo[5001][5001];

ll dp(int n, int k){

	// Para una lista de N numeros, K no puede ser mayor a N.
	// Por ejemplo si N=3, no existe ninguna lista que tenga un 4.
	// El maximo valor en ese caso seria 3, por eso el valor de K se trunca a N.
	k = min(n, k);

	// Para listas de tamano 1, solo existe la lista '1'. Y si K=1, entonces la unica lista
	// que existe es aquella que tiene solo unos.
	if(n <= 1 || k <= 1) return 1;
	if(memo[n][k] != -1) return memo[n][k];

	ll ans1 = (n-k) * dp(n-1, k-1);
	ll ans2 = k * dp(n-1, k);		
	memo[n][k] = ((ans1 % mod) + (ans2 % mod)) % mod;

	return memo[n][k];
}

int main(){
	int n, q;

	for(int i=0; i<5001; i++)
		fill(memo[i], memo[i]+5001, -1);

	while(scanf("%d %d", &n, &q) == 2){
		for(int i=0; i<q; i++){
			int k;			
			scanf("%d", &k);			
			printf("%s%lld", i==0? "" : " ", dp(n, k)); 
		}
		printf("\n");
	}
	return 0;
}
