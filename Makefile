all: hello gyakorlo uthalozat

clean:
	rm -rf hello gyakorlo uthalozat
hello: hello.cpp
	g++ -o hello hello.cpp  -I /home/username/lemon/include/ -L /home/username/lemon/lib/ -lemon

gyakorlo: gyakorlo.cpp
	g++ -o gyakorlo gyakorlo.cpp -lemon

uthalozat: uthalozat.cpp hun.lgf
	g++ -o uthalozat uthalozat.cpp   -lemon

