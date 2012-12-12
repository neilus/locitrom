Alkalmazott modul: hálózati folyamok és alkalmazásaik
=====================================================
1. programozási házi feladat:
-----------------------------
A beadandót készítette: Sana Norbert

Egy lgf formátumban megadott irányítatlan gráfról eldönteni, hogy összefüggõ-e. Hogyha nem összefüggõ, akkor megszámolni hány komponense van, illetve hány csúcsa van a legnagyobbik komponensnek.

2. Fordítás:
------------
A program megírásához felhasználtam a LEMON C++ Graph Library-t, így ez egy függõsége a program fordításának is. Hogyha a rendszerre már telepítve van a lemon, akkor elég a beadandó program könyvtárában a `make` parancsot kiadni, ha még nincs a könyvtárban letölti a beadandóhoz mellékelt gráfokat amik esetleg nincsenek ebben a repóban. Ha nincs lemon telepítve a rendszeredre, vagy szeretnéd az általam használt lemon verziót használni erre is van mód egyszerűen: mindenekelőtt add ki a `make lemon` parancsot, ez letölti és megpróbálja telepíteni a lemon-t a program könyvtárába, majd a programkönyvtárba telepített lemon-t fogja használni ez után a beadandó program fordításához.

3. Használati útmutató:
-----------------------
A program alap esetben nem vár paramétereket, és a vele egy könyvtárban levõ hun-undir.lgf fájlt használja inputként. Lehet azonban paraméterként tetszõleges fájlt is megadni a hun.lgf helyett. 
Alap esetben az alábbi parameterezéssel ekvivalensen futnak paraméterek nélkül is a programok:

`./uthalozat-undir hun-undir.lgf`

`./uthalozat-dir hun.lgf`

`./szintezo teszt-szintezo.lgf`

`./eljavito teszt-eljavito.lgf`

