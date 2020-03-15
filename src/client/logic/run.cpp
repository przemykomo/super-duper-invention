#include <mutex>
#include <spdlog/spdlog.h>
#include "client/logic/run.h"

namespace cmakub::logic {
    bool shouldRun{true};
    World world{};
    std::mutex shouldRun_mutex;

    void run() {
        spdlog::info("Logic thread.");
        {
            std::lock_guard<std::mutex> chunkLock(world.chunk_mutex);
            world.blocks[0][1][0] = 1;
        }
        while(shouldRun) {}
    }

    void setShouldNotRun() {
        std::lock_guard<std::mutex> lock(shouldRun_mutex);
        shouldRun = false;
    }
}
