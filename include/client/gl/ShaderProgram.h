#ifndef INCLUDE_CLIENT_GL_SHADERPROGRAM_H_
#define INCLUDE_CLIENT_GL_SHADERPROGRAM_H_
#include <sstream>
#include "client/gl/opengl.h"

namespace cmakub::gl {
    class ShaderProgram {
    private:
        unsigned int ID;

        unsigned int initShader(const std::stringstream &shaderSrcStream, GLenum type);
    public:
        void init(const std::string &srcPath);
        void use();
        unsigned int getID();
    };
} /* namespace cmakub::gl */

#endif /* INCLUDE_CLIENT_GL_SHADERPROGRAM_H_ */
