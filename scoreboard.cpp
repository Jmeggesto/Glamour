#include "scoreboard.h"

namespace glamour {

	Scoreboard::Scoreboard(Context& factory) {
		board = factory.createWin(1,1,COLS-1,3);
		board->standardBox();
	}
	void Scoreboard::increaseScore(int increment) {
		score += increment;
		std::string increase = NumberToString(increment);
		increase.insert(0,"+");
		std::string total = NumberToString(score);

		board->addString(total.c_str(), Left, 1);
		board->addString(increase.c_str(), Right, 1);
	}
	void Scoreboard::update() {
		board->refresh();
		board->standardBox();
	}

} // namespace glamour