all:
	rm -rf ./glamtest
	g++ -std=c++11 glamtest.cpp context.cpp enemymanager.cpp frm.cpp gameworld.cpp scoreboard.cpp window.cpp -o glamtest -lncurses 
	./glamtest