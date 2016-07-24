#include <bits/stdc++.h>
using namespace std;
#define INF 2000000000

int acum[1000007], dp[1000007], N, M;

class shop{
public:
	int L, S, C;
	shop(){
		scanf("%d %d %d", &L, &S, &C);
		L--;
	}	
};

class segtree {
private:
	int* tree;
	int* A;
	int n;
	int left (int p) { return p << 1; }
	int right(int p) { return (p << 1) + 1; }

	void build(int p, int L, int R) {
		if (L == R) tree[p] = A[L];
		else {
			build(left(p), L, (L + R)/2);
			build(right(p), (L + R)/2 + 1, R);
			int p1 = tree[left(p)];
			int p2 = tree[right(p)];
			tree[p] = min(p1, p2);
		}
	}

	int query(int p, int L, int R, int i, int j) {
		if (i >  R || j <  L) return INF;
		if (L >= i && R <= j) return tree[p];
		int p1 = query(left(p), L, (L+R)/2, i, j);
		int p2 = query(right(p), (L+R)/2 + 1, R, i, j);

		return min(p1, p2);
	}

	int update(int p, int L, int R, int idx, int new_value) {
		if (idx < L || R < idx) return tree[p];

		if (L == idx && R == idx){
			A[idx] = new_value;
			return tree[p] = A[idx];
		}
		int p1, p2;
		p1 = update(left(p), L, (L + R)/2, idx, new_value);
		p2 = update(right(p), (L + R)/2 + 1, R, idx, new_value);
		return tree[p] = min(p1, p2);
	}

public:
	segtree(int* _A, int _n) : A(_A), n(_n) {
		tree = new int[4 * n];
		fill(tree, tree+(4*n), 0);
		build(1, 0, n - 1);
	}
	~segtree(){ delete[] tree; }

	int query(int i, int j) {
		return query(1, 0, n - 1, i, j);
	}

	int update(int idx, int new_value) {
		return update(1, 0, n - 1, idx, new_value); 
	}
};

int main(){

	while(scanf("%d %d", &N, &M) == 2){

		vector<shop> shops;
		fill(dp, dp+100007, INF);
		fill(acum, acum+100007, 0);
		dp[N] = 0;

		segtree st(dp, N+1); // Crea el arbol de segmentos

		// Leer energias necesarias para cada nivel y crear arreglo de acumulados
		acum[0] = 0;
		for(int i=0; i<N; i++){			
			scanf("%d", &acum[i+1]);
			acum[i+1] += acum[i];
		}

		// Leer cada tienda
		for(int i=0; i<M; i++) shops.push_back(shop());

		// Ordenar las tiendas por nivel
		sort(shops.begin(), shops.end(), [](const shop& s1, const shop& s2){
			return s1.L < s2.L;
		});

		// Revisar cada tienda desde la ultima hasta la primera
		for(int i=M-1; i>=0; i--){

			int energia = shops[i].S;
			int left = shops[i].L;
			int a = left, b = N;

			// Hacer una busqueda binaria para encontrar el nivel mas alejado
			// al que puede llegar si se compra la energia de esta tienda.
			while(a <= b){
				int mid = (a+b)/2;
				if(acum[mid] <= energia + acum[left]){
					a = mid+1;
				} else b = mid-1;
			}

			int right = b;

			// Se hace un RMQ entre el intervalo
			// nivel de la tienda - nivel al que puede llegar
			int minimo = st.query(left+1, right);

			// Conservar el minimo
    			st.update(left, min(dp[left], minimo + shops[i].C));
    		}
		printf("%d\n", dp[0] >= INF ? -1 : dp[0]);
	}
	return 0;
}
