all:  hello_lemon  gyakorlo szintezo eljavito uthalozat-di uthalozat-undir
	
clean:
	rm -rf lemon-1.2 hun.lgf.zip hun-undir.lgf.zip hello gyakorlo uthalozat digraph uthalozat-di uthalozat-undir hello_lemon uthalozat-di.cpp szintezo eljavito

dist-clean: clean
	rm -rf lemon 

deep-clean: dist-clean
	rm -rf hun.lgf hun-undir.lgf lemon-1.2.tar.gz  win-lib lemon-linux lemon-cygwin lemonpath

linux-lib: lemon-linux
	rm -rf lemon
	cp -rl lemon-linux lemon 

cygwin-lib: lemon-cygwin
	rm -rf lemon
	cp -rl lemon-cygwin lemon 

hun.lgf.zip:
	wget http://lemon.cs.elte.hu/trac/lemon/raw-attachment/wiki/AlkMod2012/hun.lgf.zip

hun-undir.lgf.zip:
	wget http://lemon.cs.elte.hu/trac/lemon/raw-attachment/wiki/AlkMod2012/hun-undir.lgf.zip

hun.lgf: hun.lgf.zip
	unzip -o hun.lgf.zip
	touch hun.lgf

hun-undir.lgf: hun-undir.lgf.zip
	unzip -o hun-undir.lgf.zip
	touch hun-undir.lgf

lemon-1.2.tar.gz:
	-@tput setf 6
	@echo "Letoltom a lemont ide lokalis installalasra"
	-@tput sgr0
	wget http://lemon.cs.elte.hu/pub/sources/lemon-1.2.tar.gz

lemon-1.2: lemon-1.2.tar.gz
	-@tput setf 6
	@echo "Kicsomagolom ide a lemont"
	-@tput sgr0
	tar xvzf lemon-1.2.tar.gz

lemon: lemon-1.2
	-@tput setf 6
	@echo "Most installalok lokalisan egy lemon-t"
	-@tput sgr0
	rm -rf lemon
	./install-lemon.sh "-`(uname -a|grep -i linux >/dev/null && echo linux) || (uname -a|grep -i cygwin >/dev/null && echo cygwin)`"
	rm -rf lemon-1.2
	
lemonpath:
	make lemon
	-@tput setf 6
	@echo "bellitom a lemon helyet a lokalis lemn alkonyvtarra"
	-@tput sgr0
	echo "lemon">lemonpath

hello_lemon: lemonpath hello_lemon.cc
	g++ -o hello_lemon hello_lemon.cc  -I `cat lemonpath`"/include" -L `cat lemonpath`"/lib" -lemon
digraph: lemonpath digraph.cpp 
	g++ -o digraph digraph.cpp  -I `cat lemonpath`"/include" -L `cat lemonpath`"/lib" -lemon

gyakorlo: lemonpath gyakorlo.cpp 
	g++ -o gyakorlo gyakorlo.cpp -I `cat lemonpath`"/include" -L `cat lemonpath`"/lib" -lemon
gyakorlo-dir: lemonpath gyakorlo-dir.cpp 
	g++ -o gyakorlo-dir gyakorlo-dir.cpp -I  `cat lemonpath`"/include" -L `cat lemonpath`"/lib" -lemon

szintezo: lemonpath szintezo.cpp 
	g++ -o szintezo szintezo.cpp -I `cat lemonpath`"/include" -L `cat lemonpath`"/lib" -lemon
eljavito: lemonpath eljavito.cpp 
	g++ -o eljavito eljavito.cpp -I `cat lemonpath`"/include" -L `cat lemonpath`"/lib" -lemon

uthalozat: uthalozat-undir
	g++ -o uthalozat uthalozat.cpp  -I `cat lemonpath`"/include" -L `cat lemonpath`"/lib" -lemon

uthalozat-undir: lemonpath uthalozat-undir.cpp
	g++ -o uthalozat-undir uthalozat-undir.cpp  -I `cat lemonpath`"/include" -L `cat lemonpath`"/lib" -lemon

uthalozat-di: lemonpath uthalozat-di.cpp
	g++ -o uthalozat-di uthalozat-di.cpp  -I `cat lemonpath`"/include" -L `cat lemonpath`"/lib" -lemon
uthalozat-di.cpp: uthalozat-undir.cpp
	-@tput setf 6
	@echo "Ugy latom frissult az uthalozat iranyitatlan verzioja!, begrissitem rola az iranyitottat!"
	-@tput sgr0
	sed 's/ListGraph/ListDigraph/' uthalozat-undir.cpp > $@
	sed -i 's/Edge/Arc/' $@
	sed -i 's/edges/arcs/' $@
	sed -i 's/EdgeMap/ArcMap/' $@
	sed -i 's/edgeMap/arcMap/' $@
	sed -i 's/graphReader/DigraphReader/' $@
	sed -i 's/hun-undir.lgf/hun.lgf/' $@
