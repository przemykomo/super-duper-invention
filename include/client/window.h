#ifndef WINDOW_H_
#define WINDOW_H_

#include <memory>

#include "client/gl/opengl.h"
#include "client/gl/ShaderProgram.h"
#include "common/math/camera.h"
#include "client/threadsData.h"

namespace cmakub {
    class Window {
    private:
        int m_width;
        int m_height;
        GLFWwindow* m_window;
        gl::ShaderProgram m_shaderProgram;
        std::shared_ptr<ThreadsData> m_threadsData;

        inline void setupWindow();
        inline void setupGL();

        static void onWindowSizeChanged(GLFWwindow *window, int width, int height);
        static void onWindowClose(GLFWwindow *window);
        static void processInput(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void mouseInput(GLFWwindow *window, double xpos, double ypos);
    public:
        Window(int width, int height, std::shared_ptr<ThreadsData> threadsData);
        void loop();
        void setWindowShouldClose();
        ~Window();
    };
}

#endif /* WINDOW_H_ */
