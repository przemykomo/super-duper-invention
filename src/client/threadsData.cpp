#include "client/threadsData.h"

namespace cmakub {
    void ThreadsData::startMovingCamera(Direction direction) {
        switch(direction) {
        case Direction::BACK:
            cameraMovement.fetch_or(back);
            break;
        case Direction::FRONT:
            cameraMovement.fetch_or(front);
            break;
        case Direction::LEFT:
            cameraMovement.fetch_or(left);
            break;
        case Direction::RIGHT:
            cameraMovement.fetch_or(right);
            break;
        }
    }

    void ThreadsData::stopMovingCamera(Direction direction) {
        switch(direction) {
        case Direction::BACK:
            cameraMovement.fetch_and(~back);
            break;
        case Direction::FRONT:
            cameraMovement.fetch_and(~front);
            break;
        case Direction::LEFT:
            cameraMovement.fetch_and(~left);
            break;
        case Direction::RIGHT:
            cameraMovement.fetch_and(~right);
            break;
        }

    }
}
