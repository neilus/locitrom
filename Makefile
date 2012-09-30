all: uthalozat uthalozat-undir uthalozat-di hun.lgf hun-undir.lgf
	
clean:
	rm -rf lemon-1.2 hun.lgf.zip hun-undir.lgf.zip hello gyakorlo uthalozat digraph uthalozat-di uthalozat-undir

dist-clean: clean
	rm -rf lemon 

deep-clean: dist-clean
	rm -rf hun.lgf hun-undir.lgf lemon-1.2.tar.gz  win-lib lemon-linux lemon-cygwin

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
	wget http://lemon.cs.elte.hu/pub/sources/lemon-1.2.tar.gz

lemon-1.2: lemon-1.2.tar.gz
	tar xvzf lemon-1.2.tar.gz

lemon: lemon-1.2
	rm -rf lemon
	./install-lemon.sh "-`(uname -a|grep -i linux >/dev/null && echo linux) || (uname -a|grep -i cygwin >/dev/null && echo cygwin)`"
	rm -rf lemon-1.2

lemonpath:
	make lemon

hello: lemonpath hello.cpp 
	g++ -o hello hello.cpp  -I `cat lemonpath` -L `cat lemonpath` -lemon

digraph: lemonpath digraph.cpp 
	g++ -o digraph digraph.cpp  -I `cat lemonpath` -L `cat lemonpath` -lemon

gyakorlo: lemonpath gyakorlo.cpp 
	g++ -o gyakorlo gyakorlo.cpp -I `cat lemonpath` -L `cat lemonpath` -lemon

uthalozat: uthalozat-undir
	cp -fl uthalozat-undir uthalozat

uthalozat-undir: lemonpath uthalozat-undir.cpp
	g++ -o uthalozat-undir uthalozat-undir.cpp  -I `cat lemonpath` -L `cat lemonpath` -lemon

uthalozat-di: lemonpath uthalozat-di.cpp
	g++ -o uthalozat-di uthalozat-di.cpp  -I `cat lemonpath` -L `cat lemonpath` -lemon

