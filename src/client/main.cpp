#include <iostream>

#include "client/window.h"
#include "client/opengl.h"


//int main(int argc, char **argv) {
int main() {

	cmakub::window::init();
	cmakub::window::loop();
	cmakub::window::terminate();

	return 0;
}
