#ifndef INCLUDE_COMMON_MATH_MAT4_H_
#define INCLUDE_COMMON_MATH_MAT4_H_
#include "vec3.h"

namespace math {
    struct Mat4 {
        float data[4][4];
        Mat4();
        Mat4(float ax, float ay, float az, float aw,
             float bx, float by, float bz, float bw,
             float cx, float cy, float cz, float cw,
             float dx, float dy, float dz, float dw);
        float* operator [](int n);
        float* ptr();

        Mat4& translate(Vec3 vec);
    };

    Mat4 lookAt(Vec3 cameraPos, Vec3 cameraFront, Vec3 cameraUp);
    //              nearPlane, farPlane,     ratio, FOV (in radians)
    Mat4 perspective(float n, float f, float ratio, float FOV); //FOV is in radians
}

#endif /* INCLUDE_COMMON_MATH_MAT4_H_ */
