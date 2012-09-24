all:hello gyakorlo uthalozat digraph
	make clean	
clean:
	rm -rf lemon-1.2 lemon-1.2.tar.gz hun.lgf.zip hello gyakorlo uthalozat 
dist-clean: clean
	rm -rf lemon hun.lgf
hun.lgf.zip:
	wget http://lemon.cs.elte.hu/trac/lemon/raw-attachment/wiki/AlkMod2012/hun.lgf.zip
hun.lgf: hun.lgf.zip
	unzip hun.lgf.zip
lemon-1.2.tar.gz:
	wget http://lemon.cs.elte.hu/pub/sources/lemon-1.2.tar.gz
lemon-1.2: lemon-1.2.tar.gz
	tar xvzf lemon-1.2.tar.gz
lemon: lemon-1.2
	./install-lemon.sh
hello: lemon hello.cpp 
	g++ -o hello hello.cpp  -I lemon/include/ -L lemon/lib/ -lemon
digraph: lemon digraph.cpp 
	g++ -o digraph digraph.cpp  -I lemon/include/ -L lemon/lib/ -lemon
gyakorlo: lemon gyakorlo.cpp 
	g++ -o gyakorlo gyakorlo.cpp -I lemon/include/ -L lemon/lib/ -lemon
uthalozat: lemon uthalozat.cpp hun.lgf 
	g++ -o uthalozat uthalozat.cpp  -I lemon/include/ -L lemon/lib/ -lemon

