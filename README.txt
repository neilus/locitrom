lócitrom - avagy elsõ lépéseim a lemon c++ library-val való ismerkedéskor:

Amit itt találni lehet azok, a lemon tutoriálból, illetve dokumentációból lemásolt demó kódok, néhol lehet módosítottam is, nem vezetem mivel ez tényleg csak a kis saját játszóterem...

Mivel lustaság fél egészség írtam egy szép Makefilet: 
a könyvtárban kiadott make parancs linux/unix/cygwin alatt (már ha van pl autotools, gcc, wget, stb ) letölti a kísérleteim során használt lemon library tar-ballt, a lemon honlapjáról, kicsomagolja és megpróbálja installálni is. Az installált lib, a könyvtárstruktúrában a relatív lemon könyvtár alatt lesz ezután. A Makefile-ban a target-ek fordítási szabályai, használják ezt a libraryt, így ha már van lemon a gépeden, célszerű lesz átírnod a Makefile-t.

Ezt az egáesz mókát az ELTÉn 2012 őszi félévében indított Alkalmazott modul 1 - Hálózati folyamok ... 
[http://lemon.cs.elte.hu/trac/lemon/wiki/AlkMod2012 tárgy linkje] miatt kezdtem el, ezért is a könnyítések. A programok jelenleg paraméter nélkül futnak, nem user számára készültek. A futásukhoz szükséges fájlokat általában letöltetem a Makefile-ból függőségként, így ne aggódj, hogy ilyen pici (legalább a git nem túl lassú)

Hogyha saját kódot szeretnél írni és a Make-szkriptem által telepített lemon-t szeretnéd használni, akkor (felteszem a repó könyvtárába hozod létre a fájlt, így:) 
<pre>
	g++ -o kimeneti-binaris-neve forrásfájlod.cpp -I lemon/include/ -L lemon/lib/ -lemon
</pre>
szóval a <pre>-I lemon/include/ -L lemon/lib/ -lemon</pre> rész kell a fordítónak, hogy tudja hol keresse a lemont, meg hogy egyáltalán keresse.

Az itteni tartalmakat a GNU/GPL licensze alatt teszem közre (ha jól emlékszem az eredeti forrás is így tett), ami azt jelenti, hogy játszhatsz kedvedre a kóddal ahogy csak akarsz, de ha publikálod vagy másnak odaadod az eredetit vagy az általad módosított változatát, meg kell nevezd az eredeti forrást és neked is GPL licensz alatt kell továbbadnod a kódot.

Ha örülsz és meg szeretnéd hálálni, hogy ezt így kiraktam: szeretem a SÖRt.
