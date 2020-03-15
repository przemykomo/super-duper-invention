#include <thread>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include "client/window.h"
#include "client/logic/run.h"
#include "common/math/vec3.h"

//int main(int argc, char **argv) {
int main() {
	spdlog::info("Launching game...");

	cmakub::math::Vec3 vector{2.0f, 3.0f, 4.0f};
	spdlog::info("Vector: {}", vector.cross(cmakub::math::Vec3(5.0f, 6.0f, 7.0f)));

	//change to std::jthread in C++20
	std::thread gameLogic(cmakub::logic::run);

	spdlog::info("Graphics thread.");

	cmakub::Window window(640, 480);
	window.loop();

	cmakub::logic::setShouldNotRun();

	gameLogic.join();
	return 0;
}
