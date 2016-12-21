all:
	rm -rf ./glamtest
	g++ -std=c++11 glamtest.cpp context.cpp enemymanager.cpp frm.cpp gameworld.cpp xwindow.cpp -o glamtest -lncurses -w
	rm -rf *.txt
	./glamtest