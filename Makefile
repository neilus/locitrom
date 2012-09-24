all:hello gyakorlo uthalozat
	
clean:
	rm -rf lemon-1.2 lemon-1.2.tar.gz hun.lgf.zip hello gyakorlo uthalozat 
dist-clean:
	rm -rf lemon hun.lgf
hun.lgf:
	wget http://lemon.cs.elte.hu/trac/lemon/raw-attachment/wiki/AlkMod2012/hun.lgf.zip
	unzip hun.lgf.zip
	rm hun.lgf.zip
lemon-1.2:
	wget http://lemon.cs.elte.hu/pub/sources/lemon-1.2.tar.gz
	tar xvzf lemon-1.2.tar.gz
	rm lemon-1.2.tar.gz
lemon: lemon-1.2
	./install-lemon.sh

hello: hello.cpp lemon
	g++ -o hello hello.cpp  -I lemon/include/ -L lemon/lib/ -lemon

digraph: digraph.cpp lemon
	g++ -o digraph digraph.cpp  -I lemon/include/ -L lemon/lib/ -lemon

gyakorlo: gyakorlo.cpp lemon
	g++ -o gyakorlo gyakorlo.cpp -I lemon/include/ -L lemon/lib/ -lemon

uthalozat: uthalozat.cpp hun.lgf lemon
	g++ -o uthalozat uthalozat.cpp  -I lemon/include/ -L lemon/lib/ -lemon

