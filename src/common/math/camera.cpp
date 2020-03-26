#include "common/math/camera.h"

namespace math {
    Camera::Camera() : pos(0.0f, 0.0f, 3.0f), front(0.0f, 0.0f, -1.0f), up(0.0f, 1.0f, 0.0f) {}
}
