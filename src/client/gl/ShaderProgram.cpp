#include <fstream>
#include <sstream>
#include <string>

#include <spdlog/spdlog.h>

#include "client/gl/ShaderProgram.h"
#include "client/gl/opengl.h"
#include "common/math/mat4.h"

namespace cmakub::gl {
    enum ShaderType {
        FRAGMENT,
        VERTEX
        //add more if needed
    };

    void ShaderProgram::init(const std::string &srcPath) {
        ID = glCreateProgram();

        std::ifstream file(srcPath);
        if (!file) {
            spdlog::error("Shader source file {} cannot be opened!", srcPath);
            return;
        }

        std::stringstream vertexSrcStream{};
        std::stringstream fragmentSrcStream{};

        ShaderType type;

        std::string line;
        while (std::getline(file, line)) {
            if (line == "#shader vertex") {
                type = VERTEX;
                continue;
            }
            if (line == "#shader fragment") {
                type = FRAGMENT;
                continue;
            }

            switch (type) {
            case VERTEX:
                vertexSrcStream << line << '\n';
                break;
            case FRAGMENT:
                fragmentSrcStream << line << '\n';
                break;
            }
        }

        unsigned int vertexShader{ initShader(vertexSrcStream, GL_VERTEX_SHADER) };
        unsigned int fragmentShader{ initShader(fragmentSrcStream, GL_FRAGMENT_SHADER) };

        glLinkProgram(ID);
#ifndef NDEBUG
        {
            char infoLog[512];
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            if(infoLog[0] != '\0') {
                spdlog::warn(infoLog);
            }
        }
#endif
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        glUseProgram(ID);

        //temporary
        math::Mat4 view{};
        view.translate(math::Vec3(0.0f, 0.0f, -3.0f));
        int viewLoc{ glGetUniformLocation(ID, "view") };
        glUniformMatrix4fv(viewLoc, 1, GL_TRUE, view.ptr());

        math::Mat4 projection = math::perspective(0.1f, 100.0f, 640.0f / 480.0f, 45 * 3.14159265358f / 180);
        int projLoc{ glGetUniformLocation(ID, "projection") };
        glUniformMatrix4fv(projLoc, 1, GL_TRUE, projection.ptr());
    }

    unsigned int ShaderProgram::initShader(const std::stringstream &shaderSrcStream, GLenum type) {
        std::string shaderSource = shaderSrcStream.str();
        if (shaderSource.empty()) {
            return 0;
        }

        unsigned int shaderID{ glCreateShader(type) };
        const char *c_src{shaderSource.c_str()};
        glShaderSource(shaderID, 1, &c_src, NULL);
        glCompileShader(shaderID);

#ifndef NDEBUG
        {
            char infoLog[512];
            glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
            if(infoLog[0] != '\0') {
                spdlog::warn(infoLog);
            }
        }
#endif

        glAttachShader(ID, shaderID);
        return shaderID;
    }

    void ShaderProgram::use() {
        glUseProgram(ID);
    }

    unsigned int ShaderProgram::getID() {
        return ID;
    }
} /* namespace cmakub::gl */
