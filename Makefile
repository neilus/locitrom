all: uthalozat
	
clean:
	rm -rf lemon-1.2 hun.lgf.zip hello gyakorlo uthalozat digraph
dist-clean: clean
	rm -rf lemon 
deep-clean: dist-clean
	rm -rf hun.lgf lemon-1.2.tar.gz  win-lib lemon-linux lemon-cygwin
linux-lib: lemon-linux
	rm -rf lemon
	cp -rl lemon-linux lemon 
cygwin-lib: lemon-cygwin
	rm -rf lemon
	cp -rl lemon-cygwin lemon 
hun.lgf.zip:
	wget http://lemon.cs.elte.hu/trac/lemon/raw-attachment/wiki/AlkMod2012/hun.lgf.zip
hun.lgf: hun.lgf.zip
	unzip -o hun.lgf.zip
	touch hun.lgf
lemon-1.2.tar.gz:
	wget http://lemon.cs.elte.hu/pub/sources/lemon-1.2.tar.gz
lemon-1.2: lemon-1.2.tar.gz
	tar xvzf lemon-1.2.tar.gz
lemon: lemon-1.2
	rm -rf lemon
	./install-lemon.sh "-`(uname -a|grep -i linux >/dev/null && echo linux) || (uname -a|grep -i cygwin >/dev/null && echo cygwin)`"
lemonpath:
	make lemon
hello: lemonpath hello.cpp 
	g++ -o hello hello.cpp  -I `cat lemonpath` -L `cat lemonpath` -lemon
digraph: lemonpath digraph.cpp 
	g++ -o digraph digraph.cpp  -I `cat lemonpath` -L `cat lemonpath` -lemon
gyakorlo: lemonpath gyakorlo.cpp 
	g++ -o gyakorlo gyakorlo.cpp -I `cat lemonpath` -L `cat lemonpath` -lemon
uthalozat: lemonpath uthalozat.cpp hun.lgf 
	g++ -o uthalozat uthalozat.cpp  -I `cat lemonpath` -L `cat lemonpath` -lemon

