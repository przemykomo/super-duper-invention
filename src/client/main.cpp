#include <thread>
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include "client/window.h"
#include "client/logic/run.h"
#include "client/threadsData.h"

//int main(int argc, char **argv) {
int main() {
    spdlog::info("Launching game...");

    std::shared_ptr<cmakub::ThreadsData> threadsData = std::make_shared<cmakub::ThreadsData>();

    //change to std::jthread in C++20
    std::thread gameLogic(cmakub::logic::run, threadsData);

    spdlog::info("Graphics thread.");

    cmakub::Window window(640, 480, threadsData);
    window.loop();

    threadsData->logicThreadRunning = false;

    gameLogic.join();
    return 0;
}
