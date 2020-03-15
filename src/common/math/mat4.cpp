#include <cmath>
#include "common/math/mat4.h"
#include "common/math/vec3.h"

namespace cmakub::math {
    //constructs indentity matrix
    Mat4::Mat4() : data{{1.0f, 0.0f, 0.0f, 0.0f},
                        {0.0f, 1.0f, 0.0f, 0.0f},
                        {0.0f, 0.0f, 1.0f, 0.0f},
                        {0.0f, 0.0f, 0.0f, 1.0f}} {}

    Mat4::Mat4(float ax, float ay, float az, float aw,
               float bx, float by, float bz, float bw,
               float cx, float cy, float cz, float cw,
               float dx, float dy, float dz, float dw) :
                data{{ax, ay, az, aw},
                     {bx, by, bz, bw},
                     {cx, cy, cz, cw},
                     {dx, dy, dz, dw}} {}

    float* Mat4::operator [](int n) {
        return data[n];
    }

    Mat4 lookAt(Vec3 cameraPos, Vec3 cameraFront, Vec3 cameraUp) {
        /* front is -z
         * right is +x
         * up is +y
         */

        Vec3 zaxis(cameraPos - cameraFront); //forward
        zaxis.normalize();

        Vec3 xaxis(cameraUp.cross(zaxis)); //right
        xaxis.normalize();

        Vec3 yaxis(zaxis.cross(xaxis)); //up

        return Mat4(xaxis.x, xaxis.y, xaxis.z, -xaxis*cameraPos,
                    yaxis.x, yaxis.y, yaxis.z, -yaxis*cameraPos,
                    zaxis.x, zaxis.y, zaxis.z, -zaxis*cameraPos,
                    0.0f,    0.0f,    0.0f,     1.0f);
    }

    Mat4 perspective(float nearPlane, float farPlane, float ratio, float FOV) { //FOV is in radians
        float tanThetaOver2{std::tan(FOV/2)};

        return Mat4(1.0f/tanThetaOver2, 0.0f, 0.0f, 0.0f,
                    0.0f, 1.0f, 0.0f, 0.0f,
                    0.0f, 0.0f, 1.0f, 0.0f,
                    0.0f, 0.0f, -1.0f, 0.0f);
    }
}
