#ifndef INCLUDE_CLIENT_LOGIC_RUN_H_
#define INCLUDE_CLIENT_LOGIC_RUN_H_
#include <mutex>
#include "common/world.h"

namespace cmakub::logic {
	extern bool shouldRun;
	extern World world;
	extern std::mutex shouldRun_mutex;
	void setShouldNotRun();
	void run();
}

#endif /* INCLUDE_CLIENT_LOGIC_RUN_H_ */
