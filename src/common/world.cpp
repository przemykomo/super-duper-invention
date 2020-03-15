#include "common/world.h"

namespace cmakub {
	World::World() : blocks{} {
		blocks[0][0][0] = 1;
		blocks[2][2][1] = 1;
	}
}
