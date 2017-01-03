#ifndef SCOREBOARD_H_
#define SCOREBOARD_H_

#include "window.h"
#include "context.h"

#include <sstream>
#include <string>

namespace glamour {

	template <typename T>
  	std::string NumberToString ( T Number )
  	{
     	std::ostringstream ss;
     	ss << Number;
     	return ss.str();
  	}

	class Scoreboard {

	public:

		Scoreboard(Context& factory);
		void increaseScore(int increment);
		void update();

	private:

		Window* board = nullptr;
		unsigned int score = 0;
	};

} // namespace glamour
#endif