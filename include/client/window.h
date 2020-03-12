#ifndef WINDOW_H_
#define WINDOW_H_

#include "client/gl/opengl.h"
#include "client/gl/ShaderProgram.h"

namespace cmakub {
	class Window {
	private:
		int m_width;
		int m_height;

		GLFWwindow* m_window;

		gl::ShaderProgram shaderProgram;

		inline void setupWindow();
		inline void setupGL();

		static void onWindowSizeChanged(GLFWwindow *window, int width, int height);
		static void onWindowClose(GLFWwindow *window);
	public:
		Window(int width, int height);
		void loop();
		void setWindowShouldClose();
		~Window();
	};
}

#endif /* WINDOW_H_ */
