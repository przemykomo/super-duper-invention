#include <iostream>

#include "opengl.h"

#include "windowEvents.h"

//int main(int argc, char **argv) {
int main() {
	auto &log{std::cout};

	log << "Starting up.\n";

	if(!glfwInit()) {
		log << "Can't initialize GLFW!\n";
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	// Don't change window title while in alpha version
	GLFWwindow* window = glfwCreateWindow(640, 480, "cmakub", NULL, NULL);

	if(!window) {
		log << "Window or OpenGL context creation failed!\n";
	}

	glfwMakeContextCurrent(window);

	if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		log << "Can't load opengl! 'gladLoadGL()'\n";
		return -1; //TODO: some better termination
	}

	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
	}

	glfwSwapInterval(1);
	glfwSetFramebufferSizeCallback(window, windowSizeChanged);
	glfwSetWindowCloseCallback(window, closeWindow);

	glClearColor(0.00f, 0.20f, 0.25f, 1.0f);

	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	log << "Terminating.\n";
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
