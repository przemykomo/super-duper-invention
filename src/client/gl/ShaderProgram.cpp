#include <fstream>
#include <sstream>
#include <string>

#include "client/gl/ShaderProgram.h"
#include "client/gl/opengl.h"

#include "common/log.h"

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
			log << "Shader source file " << srcPath << " cannot be opened!\n";
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
			log << "Shader Program log:\n" << infoLog << '\n';
		}
#endif
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
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
			log << "Shader log:\n" << infoLog << '\n';
		}
#endif

		glAttachShader(ID, shaderID);
		return shaderID;
	}

	void ShaderProgram::use() {
		glUseProgram(ID);
	}
} /* namespace cmakub::gl */