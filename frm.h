#ifndef FRM_H_   /* Include guard */
#define FRM_H_

#include <sys/time.h>

#include <functional>

namespace glamour {

	class FrameRateManager {
	public:

		enum framestate {
			None, Executing, Calculating
		};

		FrameRateManager::framestate state = None;

		FrameRateManager();
		FrameRateManager(int fps);
		~FrameRateManager();

		template<typename F, typename C> void update(const F& function, const C& condition) {
			int gamestatus;
			while(condition() == true) {
				mark();
				if((gamestatus = function(framelength)) == -1) {
					break;
				}
				mark();
				pad();
			}
		}

	private:
		// frames per second
		int framerate = 0; 
		// floating-point length of individual frame
		double framelength = 0;

		// floating-point fractional representation of time to delay execution
		long delay_time;

		// number of frames that have elapsed since beginning 
		unsigned int framecount = 0; 

		struct timespec *t_measurer = nullptr;

		// current time (in microseconds) at start of frame
		long mark_start = 0; 
		// current time (in microseconds) at end of frame
		long mark_end = 0; 
		// difference (in microseconds) between end of frame and start of frame
		long frame_diff = 0; 

		int mark();
		int pad();

		void startframe();
		void endframe();
		void calculateFrame();

	};
} // namespace glamour

#endif
