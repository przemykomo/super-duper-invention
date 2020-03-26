#ifndef INCLUDE_COMMON_MATH_CAMERA_H_
#define INCLUDE_COMMON_MATH_CAMERA_H_
#include <mutex>
#include "vec3.h"

namespace math {
    struct Camera {
        Vec3 pos;
        Vec3 front;
        Vec3 up;
        std::mutex camera_mutex;
        Camera();
    };
}

#endif /* INCLUDE_COMMON_MATH_CAMERA_H_ */
