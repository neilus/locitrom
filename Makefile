all: lemon nacl_sdk
	make clean
	cd nacl_sdk && ./naclsdk update 
	cd nacl_sdk && ./naclsdk update
	
clean:
	rm -rf  hello gyakorlo uthalozat digraph uthalozat-di uthalozat-undir hello_lemon uthalozat-di.cpp szintezo eljavito *.log *.exe *.stackdump szintezve_parosit eljavitva_parosit
	rm -rf *.tar.gz *.tar.bz *.zip *bak

dist-clean: clean deep-clean
	rm -rf lemon lemonpath lemon-1.2 
	echo " -lemon">lemonpath

deep-clean: 
	rm -rf hun.lgf hun-undir.lgf hun.lgf.zip hun-undir.lgf.zip lemon-* nacl*

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
	@echo -n "ide rakom a lemon backupjat"
	-@tput setf 
	@echo `(uname -a|grep -i linux >/dev/null && echo linux) || (uname -a|grep -i cygwin >/dev/null && echo cygwin)|| (uname -a|grep -i MINGW32 >/dev/null && echo windows-mingw) `
	-@tput sgr0
	./install-lemon.sh "-`(uname -a|grep -i linux >/dev/null && echo linux) || (uname -a|grep -i cygwin >/dev/null && echo cygwin)|| (uname -a|grep -i MINGW32 >/dev/null && echo windows-mingw) `"
	
lemonpath:
	-@tput setf 4
	@echo "Ha nincs LEMON konfiguralva, add ki a make lemon parancsot, mely beallitja a lemonpath-ot is a forditonak!!!"
	-@tput sgr0
	
nacl_sdk.zip:
	wget http://storage.googleapis.com/nativeclient-mirror/nacl/nacl_sdk/nacl_sdk.zip
nacl_sdk: nacl_sdk.zip
	unzip nacl_sdk.zip

hello_lemon: lemonpath hello_lemon.cc
	g++ -o hello_lemon hello_lemon.cc  `cat lemonpath`
digraph: lemonpath digraph.cpp 
	g++ -o digraph digraph.cpp  
gyakorlo: lemonpath gyakorlo.cpp 
	g++ -o gyakorlo gyakorlo.cpp `cat lemonpath`
gyakorlo-dir: lemonpath gyakorlo-dir.cpp 
	g++ -o gyakorlo-dir gyakorlo-dir.cpp `cat lemonpath`
mindenfele.o: mindenfele.h
	g++ -c mindenfele.h `cat lemonpath`
szintezo: lemonpath szintezo.cpp szintezo.h mindenfele.h
	g++ -o szintezo szintezo.cpp `cat lemonpath`
szintezve_parosit: lemonpath szintezve_parosit.cpp szintezo.h mindenfele.h
	g++ -o szintezve_parosit szintezve_parosit.cpp `cat lemonpath`
eljavito: lemonpath eljavito.cpp eljavito.h mindenfele.h
	g++ -o eljavito eljavito.cpp `cat lemonpath`
eljavitva_parosit: lemonpath eljavitva_parosit.cpp eljavito.h mindenfele.h
	g++ -o eljavitva_parosit eljavitva_parosit.cpp `cat lemonpath`
uthalozat-undir: lemonpath uthalozat-undir.cpp hun-undir.lgf
	g++ -o uthalozat-undir uthalozat-undir.cpp  `cat lemonpath`
uthalozat-di: lemonpath uthalozat-di.cpp hun.lgf
	g++ -o uthalozat-di uthalozat-di.cpp  `cat lemonpath`
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
