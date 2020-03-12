#include "client/window.h"
#include "common/log.h"

namespace cmakub {
	Window::Window(int width, int height) :
	m_width{width}, m_height{height}, m_window{} {
#ifndef NDEBUG
		{
			int major, minor, revision;
			glfwGetVersion(&major, &minor, &revision);
			log << "Window init.\nGLFW version: "
				<< major << "." << minor << "." << revision << "\n";
		}
#endif
		setupWindow();
		setupGL();
	}

	void Window::setupWindow() {
		if(!glfwInit()) {
				log << "Can't initialize GLFW!\n";
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		// Don't change window title while in alpha version
		m_window = glfwCreateWindow(m_width, m_height, "cmakub", NULL, NULL);

		if(!m_window) {
			log << "Window or OpenGL context creation has falied!\n";
		}

		glfwMakeContextCurrent(m_window);

		glfwSwapInterval(1);
		glfwSetFramebufferSizeCallback(m_window, onWindowSizeChanged);
		glfwSetWindowCloseCallback(m_window, onWindowClose);
	}

	void Window::setupGL() {
		if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			log << "Can't load OpenGL functions!\n";
		}

		glViewport(0, 0, m_width, m_height);

		glClearColor(0.00f, 0.20f, 0.25f, 1.0f);

		// actual buffers etc.
		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		float vertices[]{
				-0.5f, -0.5f, 0.0f,
				+0.5f, -0.5f, 0.0f,
				+0.0f, +0.5f, 0.0f
		};

		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		shaderProgram.init("assets/shader.glsl");
		shaderProgram.use();
	}

	void Window::loop() {
		while(!glfwWindowShouldClose(m_window)) {
			glClear(GL_COLOR_BUFFER_BIT);

			glDrawArrays(GL_TRIANGLES, 0, 3);

			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}
	}

	void Window::setWindowShouldClose() {
		glfwSetWindowShouldClose(m_window, 1);
	}

	Window::~Window() {
		log << "Closing window.\n";
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	void Window::onWindowSizeChanged(GLFWwindow *window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	void Window::onWindowClose(GLFWwindow *window) {
		glfwSetWindowShouldClose(window, 1);
	}
}
