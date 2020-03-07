#include "windowEvents.h"

void windowSizeChanged(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

void closeWindow(GLFWwindow *window) {
	glfwSetWindowShouldClose(window, 1);
}
