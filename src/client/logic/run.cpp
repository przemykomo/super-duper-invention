#include <thread>
#include <memory>
#include <spdlog/spdlog.h>
#include "client/logic/run.h"
#include "client/threadsData.h"

namespace cmakub::logic {
    void run(std::shared_ptr<ThreadsData> data_ptr) {
        data_ptr->logicThreadRunning = true;

        spdlog::info("Logic thread.");

        while(data_ptr->logicThreadRunning.load()) {
            if(data_ptr->cameraMovement.load()) {
                std::lock_guard<std::mutex> guard(data_ptr->cameraMutex);
                const float cameraSpeed{0.05f};

                if(data_ptr->cameraMovement.load() & cmakub::ThreadsData::front) {
                    data_ptr->camera.pos += data_ptr->camera.front * cameraSpeed;
                }
                if(data_ptr->cameraMovement.load() & cmakub::ThreadsData::back) {
                    data_ptr->camera.pos -= data_ptr->camera.front * cameraSpeed;
                }
                if(data_ptr->cameraMovement.load() & cmakub::ThreadsData::left) {
                    data_ptr->camera.pos -= (data_ptr->camera.front.cross(data_ptr->camera.up)).normalize() * cameraSpeed;
                }
                if(data_ptr->cameraMovement.load() & cmakub::ThreadsData::right) {
                    data_ptr->camera.pos += (data_ptr->camera.front.cross(data_ptr->camera.up)).normalize() * cameraSpeed;
                }

                data_ptr->updateCamera = true;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }

        spdlog::info("Closing logic thread.");
    }
}
