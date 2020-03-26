#ifndef INCLUDE_CLIENT_THREADSDATA_H_
#define INCLUDE_CLIENT_THREADSDATA_H_
#include <atomic>
#include <mutex>
#include <cstdint>
#include "common/math/camera.h"

namespace cmakub {
// Interface to send data over graphic and logic threads
    class ThreadsData {
    private:
    public:
        static constexpr std::uint_fast8_t left { 0b00000001 };
        static constexpr std::uint_fast8_t right{ 0b00000010 };
        static constexpr std::uint_fast8_t front{ 0b00000100 };
        static constexpr std::uint_fast8_t back { 0b00001000 };

        enum class Direction {
            LEFT,
            RIGHT,
            FRONT,
            BACK
        };

        std::atomic<bool> updateCamera;
        std::atomic<bool> logicThreadRunning;
        math::Camera camera;
        std::mutex cameraMutex;
        std::atomic<std::uint_fast8_t> cameraMovement;

        void startMovingCamera(Direction direction);
        void stopMovingCamera(Direction direction);
    };
}

#endif /* INCLUDE_CLIENT_THREADSDATA_H_ */
