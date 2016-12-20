#include "frm.h"
#include <time.h>
#include <stdio.h>
#include <unistd.h>

#ifdef __MACH__
#include <mach/clock.h>
#include <mach/mach.h>
#endif

namespace glamour {

	void current_utc_time(struct timespec *ts) {

#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
  	clock_serv_t cclock;
  	mach_timespec_t mts;
  	host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
  	clock_get_time(cclock, &mts);
  	mach_port_deallocate(mach_task_self(), cclock);
  	ts->tv_sec = mts.tv_sec;
  	ts->tv_nsec = mts.tv_nsec;
#else
  	clock_gettime(CLOCK_REALTIME, ts);
#endif

	}

	FrameRateManager::FrameRateManager() {}

	FrameRateManager::FrameRateManager(int fps) : framerate(fps) {

		framelength = (double) 1 / fps;
		t_measurer = new struct timespec;		
		state = Executing;

	}
	FrameRateManager::~FrameRateManager() {
		if(t_measurer){
			delete t_measurer;
		}
	}	
	int FrameRateManager::mark() {
		if(state == Executing) {
			startframe();
			state = Calculating;
		} else if(state == Calculating) {
			endframe();
			calculateFrame();
			state = Executing;
		}
		return 1;

	}

	void FrameRateManager::startframe() {
		current_utc_time(t_measurer);
		mark_start = t_measurer->tv_nsec / 1000;
		
	}
	void FrameRateManager::endframe() {
		current_utc_time(t_measurer);
		mark_end = t_measurer->tv_nsec / 1000;
		framecount++;
	}

	void FrameRateManager::calculateFrame() {
		frame_diff = mark_end - mark_start;
		int framelength_long = (int)(framelength * 1000000);
		delay_time = framelength_long - frame_diff;
	}

	int FrameRateManager::pad() {
		if(state == Executing && delay_time > 0){
			usleep(delay_time);
		}
		return 1;
	}

} // namespace glamour