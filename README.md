# Solutions ACM ICPC 2015 South America

Soluciones de los problemas de la ACM ICPC 2015.

## Soluciones actualizadas

Nuevas soluciones hechas entre 2020 y 2021. Código mas limpio y elegante.

* [A - At Most Twice](https://github.com/ChrisVilches/Algorithms/blob/main/urionlinejudge/2013-at_most_twice.cpp)
* [B - Blood Groups](https://github.com/ChrisVilches/Algorithms/blob/main/urionlinejudge/2014-blood_groups.cpp)
* [C - Cake Cut](https://github.com/ChrisVilches/Algorithms/blob/main/urionlinejudge/2015-cake_cut.cpp)
* D - D as in Daedalus
* [E - Exposing Corruption](https://github.com/ChrisVilches/Algorithms/blob/main/urionlinejudge/2008-exposing_corruption.cpp)
* [F - Fence the Vegetables Fail](https://github.com/ChrisVilches/Algorithms/blob/main/urionlinejudge/2007-fence_the_vegetables_fail.cpp)
* [G - Galactic Taxes](https://github.com/ChrisVilches/Algorithms/blob/main/uva/13010-galactic_taxes.cpp)
* [H - Height Map](https://github.com/ChrisVilches/Algorithms/blob/main/uva/13011-height_map.cpp)
* I - Identifying Tea
* [J - Just a Bit Sorted](https://github.com/ChrisVilches/Algorithms/blob/main/urionlinejudge/2009-just_a_bit_sorted.cpp)
* [K - Keep it Energized](https://github.com/ChrisVilches/Algorithms/blob/main/urionlinejudge/2010-keep_it_energized.cpp)

## Análisis del problema J - Just a bit sorted

El problema se resuelve con una implementación casi directa del triángulo de números de Euler.

### Triángulo de Euler

El triángulo de Euler es una fórmula matemática que puede, tomando dos parámetros n y k, entregar el número de permutaciones del conjunto {1,2,3,4...n} en donde existen k pares de números adyacentes en donde el primero es menor al segundo.

Por ejemplo para n=3 las permutaciones posibles son:

| Permutaciones |  Pares en incremento |
|---	|---	|
|1 2 3|1,2 y 2,3 |
|1 3 2| 1,3|
|2 1 3| 1,3|
|2 3 1|2,3|
|3 1 2 |1,2|
|3 2 1|-|



Si tomamos k=2, solo existe una permutación, la {1, 2, 3} que tiene dos pares en incremento. Y si tomamos k=1, existen 4 permutaciones de este tipo.

Con la fórmula de Euler, se genera siempre el siguiente triángulo:

|N / K|*0*|*1*|*2*|*3*|*4*|*5*|*6*|
|---|---|---|---|---|---|---|---|
|*1*|1|||||||
|*2*|1|1||||||
|*3*|1|4|1|||||
|*4*|1|11|11|1||||
|*5*|1|26|66|26|1|||
|*6*|1|57|302|302|57|1||
|*7*|1|120|1191|2416|1191|120|1|

Cuando k=0, siempre existe solo 1 posible permutación, que corresponde a {n, n-1, …, 4, 3, 2, 1} (orden descendente), y para el caso de k=n-1, también existe una posible permutación, que es en orden ascendente. Por ejemplo n=3, k=2, la permutación es {1, 2, 3}.

Ahora se mapea las listas Just a bit sorted con este triángulo. En el problema, si tenemos N elementos, y K es el máximo valor que puede existir dentro de una lista, se puede crear una correspondencia entre las listas del problema, y el triángulo de Euler.

Para n=3, y k=2, todas las listas Just a bit sorted que existen son:

|Secuencias posibles para N=3 y K=2|
|---|
|1 1 1|
|1 1 2|
|1 2 1|
|1 2 2|
|2 1 2|


### Mapeo al triángulo de Euler


Para cada lista, podemos crear listas de posiciones en donde ocurre cada número en la lista original. La idea es encontrar una correspondencia con el triángulo de Euler.

Por ejemplo en la lista {3, 2, 1, 2, 2, 3}, el número 1 ocurre en la posición {3}, el 2 ocurre en las posiciones {2, 4, 5}, y el 3 ocurre en las posiciones {1, 6}. Ahora si concatenamos estas listas en orden inverso (empezando por el 3), nos queda la lista {1, 6, 2, 4, 5, 3}. Es decir, la lista resultante tiene exactamente N números distintos. Llegar a la conclusión de que se debe concatenar las listas era lo más difícil del problema, ya que se debia descubrir que este problema podía ser modelado con un triángulo de Euler.

En el ejemplo anterior, cada secuencia Just a bit sorted, tiene una lista asociada:

|Just a bit sorted list| Mapeo a permutaciones de {1, 2, 3, ...n}
|---|---|
|1 1 1|1 2 3|
|1 1 2|3 1 2|
|1 2 1|2 1 3|
|1 2 2|2 3 1|
|2 1 2|1 3 2|
|2 2 1 *|1 2 3|



\* La lista {2, 2, 1} no es una Just a bit sorted list, pero sirve para demostrar que su lista asociada, es decir, {1, 2, 3} ya existe dentro del conjunto, y por eso el resultado final solo considera las permutaciones distintas (calculadas por el triángulo de Euler).

Esto demuestra que la cantidad total de secuencias válidas es el mismo que al calcular el número de permutaciones con K incrementos con el triángulo de Euler, luego de mapear las Just a bit sorted lists a permutaciones del conjunto {1, 2, 3, 4, …n}. El problema se traduce perfectamente a simplemente ocupar la fórmula de los números de Euler.

Dado que las listas Just a bit sorted permiten que no necesariamente estén todos los números desde 1 hasta K (es decir si K=100, una lista no necesariamente debe tener todos los números desde 1 hasta 100), uno puede sumar todas los resultados de una fila del triángulo, empezando desde la fila N, en la primera posicion (K=1, ya que K=0 no es un valor permitido en este problema), e iterando hasta la posición K de esa misma fila. Se debe calcular las sumas acumuladas para así consultarlas en orden O(1).

Por ejemplo, cuando N=3 y K=2, en el triángulo, sumamos 1+4 = 5. Este resultado es correcto ya que la cantidad posible de secuencias son 5. También se da el caso especial en que si N=K, al sumar toda la fila, se obtiene N! (factorial de N). Por ejemplo si N=K=5, existe un total de 5! = 1 + 26 + 66 + 26 + 1 = 120 Just a bit sorted lists.

Otra cosa a considerar es que si K es mayor a N, entonces K debe ser truncado a N, ya que no existe ninguna secuencia que, por ejemplo, tenga N=3 elementos, y uno de ellos sea un 4. La secuencia {1,3,4} es inválida. Esto permite que K tenga un máximo valor de N=5000, en vez de 10^9 como dice el enunciado, dando posibilidad de crear una tabla de memoización y resolverlo con programación dinámica.

La tabla ```dp[5000][5000]``` resultante se ve igual que un triángulo de Euler, excepto que tiene las sumas acumuladas, y a la derecha de la diagonal, todas las casillas tienen el mismo valor que el valor situado en la diagonal.

La fórmula a ocupar para generar el triángulo de Euler es (esta fórmula fue creada por Euler, solo hay que ocuparla):

```c++
dp(n, k) = (n-k) * dp(n-1, k-1) + (m+1) * dp(n-1, k);
```

Los casos bases son cuando N=1 o K=1, ya que en esos casos solo existe una posible lista, la respuesta es 1 en tales casos.
