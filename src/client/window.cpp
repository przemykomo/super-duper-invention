#include "client/window.h"
#include "common/log.h"

namespace cmakub::window {
	GLFWwindow* window{};

	void init() {
		{
			int major, minor, revision;
			glfwGetVersion(&major, &minor, &revision);
			log << "Window init.\nGLFW version: "
				<< major << "." << minor << "." << revision << "\n";
		}

		if(!glfwInit()) {
			log << "Can't initialize GLFW!\n";
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		// Don't change window title while in alpha version
		window = glfwCreateWindow(640, 480, "cmakub", NULL, NULL);

		if(!window) {
			log << "Window or OpenGL context creation has falied!\n";
		}

		glfwMakeContextCurrent(window);

		if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			log << "Can't load OpenGL functions!\n";
		}

		{
			int width, height;
			glfwGetFramebufferSize(window, &width, &height);
			glViewport(0, 0, width, height);
		}

		glfwSwapInterval(1);
		glfwSetFramebufferSizeCallback(window, onWindowSizeChanged);
		glfwSetWindowCloseCallback(window, onWindowClose);

		glClearColor(0.00f, 0.20f, 0.25f, 1.0f);
	}

	void loop() {
		while(!glfwWindowShouldClose(window)) {
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	void setWindowShouldClose() {
		glfwSetWindowShouldClose(window, 1);
	}

	void terminate() {
		log << "Terminating.\n";
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	// Events:
	void onWindowSizeChanged(GLFWwindow *window, int width, int height) {
		glViewport(0, 0, width, height);
	}

	void onWindowClose(GLFWwindow *window) {
		glfwSetWindowShouldClose(window, 1);
	}
}
