#ifndef INCLUDE_COMMON_WORLD_H_
#define INCLUDE_COMMON_WORLD_H_
#include <mutex>

namespace cmakub {
    class World {
    public:
        static constexpr short chunkSize{3};
        short blocks[3][3][3];
        std::mutex chunk_mutex;
        World();
    };
}

#endif /* INCLUDE_COMMON_WORLD_H_ */
