Alkalmazott modul: hálózati folyamok és alkalmazásaik
=====================================================
1. programozási házi feladat:
-----------------------------
A beadandót készítette: Sana Norbert

Egy lgf formátumban megadott irányítatlan gráfról eldönteni, hogy összefüggõ-e. Hogyha nem összefüggõ, akkor megszámolni hány komponense van, illetve hány csúcsa van a legnagyobbik komponensnek.

2. Fordítás:
------------
A program megírásához felhasználtam a LEMON C++ Graph Library-t, így ez egy függõsége a program fordításának is. Hogyha a rendszerre már telepítve van a lemon, akkor elég a beadandó program könyvtárában a `make` parancsot kiadni, ez lefordítja a binárist valamint ha még nincs a könyvtárban letölti a beadandóhoz mellékelt gráfot. Abban az esetben ha a lemon nincs telepítve a rendszerre, akkor a `make lemon && make ` parancs kiadásával elõször letölti és megpróbálja telepíteni a lemon-t a program könyvtárába, majd a programkönyvtárba telepített lemon-t fogja használni ez után a beadandó program fordításához.

megjegyzes:
============
fontos a make definiciok miatt, hogy egy lemonpath nevu textfile letezzen es az installalt lemonra mutasson. Ezert alapbol most a make parancsra fuggosegkent ezt ugy probalja meg maganak letrehozni, hogy elotte megprobalja a munkakonyvtarba telepiteni a lemont, majd ezt az utvonalat berakja a lemonpath fajlba. Ehhez kell internetkapcsolat, hogy a lemont le tudja tolteni, es persze a elmon fuggosegei is kellenek.
Ha mar van telepitve lemonod es nem szeretned, hogy telepitsen maganak meg egyet, akkor hozd letre a lemonpath fajlt es add meg benne a lemon library abszolut utvonalat (azt a konyvtarat amiben az include meg a lib konyvtarak vannak)!

a hun.lgf es a hun-undir.lgf (magyarorszag uthalozatanak grafja iranyitatlan es iranyitott verzioban) fajlokat ha nincsenek jelen a konyvtarban ugyszint le szeretne tolteni automatikusan. Ha ezt el szeretned kerulni helyezd ide az allomanyokat elore. Ugyanez igaz a lemon-1.2.tar.gz -re. Ha szeretned, hogy telepitsen maganak egy lokalis lemont forrasbol, de nem akarod, hogy megprobalja letolteni akkor ezt a fajlt is toltsd le a http://lemon.cs.elte.hu -rol es helyezd ide!

3. Használati útmutató:
-----------------------
A program alap esetben nem vár paramétereket, és a vele egy könyvtárban levõ hun-undir.lgf fájlt használja inputként. Lehet azonban paraméterként tetszõleges fájlt is megadni a hun.lgf helyett. 
`./uthalozat hun.lgf`
