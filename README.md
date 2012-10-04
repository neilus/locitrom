__Alkalmazott modul: hálózati folyamok és alkalmazásaik__
 1. programozási házi feladat:
A beadandót készítette: Sana Norbert

Egy lgf formátumban megadott irányítatlan gráfról eldönteni, hogy összefüggõ-e. Hogyha nem összefüggõ, akkor megszámolni hány komponense van, illetve hány csúcsa van a legnagyobbik komponensnek.
== Fordítás: == 
A program megírásához felhasználtam a LEMON C++ Graph Library-t, így ez egy függõsége a program fordításának is. Hogyha a rendszerre már telepítve van a lemon, akkor elég a beadandó program könyvtárában a <pre><code>make</code></pre> parancsot kiadni, ez lefordítja a binárist valamint ha még nincs a könyvtárban letölti a beadandóhoz mellékelt gráfot. Abban az esetben ha a lemon nincs telepítve a rendszerre, akkor a <pre><code>make lemon && make </code></pre> parancs kiadásával elõször letölti és megpróbálja telepíteni a lemon-t a program könyvtárába, majd a programkönyvtárba telepített lemon-t fogja használni ez után a beadandó program fordításához.
== Használati útmutató: ==
A program alap esetben nem vár paramétereket, és a vele egy könyvtárban levõ hun-undir.lgf fájlt használja inputként. Lehet azonban paraméterként tetszõleges fájlt is megadni a hun.lgf helyett. 
{{{./uthalozat hun.lgf}}}
