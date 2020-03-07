#ifndef SRC_WINDOWEVENTS_H_
#define SRC_WINDOWEVENTS_H_

#include "client/opengl.h"

namespace cmakub::window {
	void init();
	void loop();
	void setWindowShouldClose();
	void terminate();

	// Events, don't call them directly:
	void onWindowSizeChanged(GLFWwindow *window, int width, int height);
	void onWindowClose(GLFWwindow *window);
}

#endif /* SRC_WINDOWEVENTS_H_ */
