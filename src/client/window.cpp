#include <spdlog/spdlog.h>
#include "client/window.h"
#include "common/math/mat4.h"

namespace cmakub {
    Window::Window(int width, int height, std::shared_ptr<ThreadsData> threadsData) :
                m_width{width}, m_height{height}, m_window{}, m_threadsData{threadsData} {
#ifndef NDEBUG
        {
            int major, minor, revision;
            glfwGetVersion(&major, &minor, &revision);
            spdlog::debug("GLFW version: {}.{}.{}", major, minor, revision);
        }
#endif
        setupWindow();
        setupGL();
    }

    void Window::setupWindow() {
        if(!glfwInit()) {
                spdlog::error("Can't initialize GLFW!");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        // Don't change window title while in alpha version
        m_window = glfwCreateWindow(m_width, m_height, "cmakub", NULL, NULL);

        if(!m_window) {
            spdlog::error("Window or OpenGL context creation has falied!");
        }

        glfwMakeContextCurrent(m_window);

        glfwSetWindowUserPointer(m_window, this);

        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        glfwSwapInterval(1);
        glfwSetFramebufferSizeCallback(m_window, onWindowSizeChanged);
        glfwSetWindowCloseCallback(m_window, onWindowClose);
        glfwSetKeyCallback(m_window, processInput);
        glfwSetCursorPosCallback(m_window, mouseInput);
    }

    void Window::setupGL() {
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            spdlog::error("Can't load OpenGL functions!");
        }

        glViewport(0, 0, m_width, m_height);

        glClearColor(0.00f, 0.20f, 0.25f, 1.0f);

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

        m_shaderProgram.init("assets/shader.glsl");
        m_shaderProgram.use();
    }

    void Window::loop() {
        while(!glfwWindowShouldClose(m_window)) {
            if(m_threadsData->updateCamera.load()) {
                m_threadsData->updateCamera.store(false);
                math::Mat4 view;

                {
                    std::lock_guard<std::mutex> guard(m_threadsData->cameraMutex);
                    view = math::lookAt(m_threadsData->camera.pos, m_threadsData->camera.front, m_threadsData->camera.up);
                }

                int viewLoc{ glGetUniformLocation(m_shaderProgram.getID(), "view") };
                glUniformMatrix4fv(viewLoc, 1, GL_TRUE, view.ptr());
            }

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
        spdlog::info("Closing window.\n");
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

    void Window::onWindowSizeChanged(GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);

        math::Mat4 projection = math::perspective(0.1f, 100.0f, static_cast<float>(width) / height, 45 * 3.14159265358f / 180);
        int projLoc{ glGetUniformLocation(static_cast<Window*>(glfwGetWindowUserPointer(window))->m_shaderProgram.getID(), "projection") };
        glUniformMatrix4fv(projLoc, 1, GL_TRUE, projection.ptr());
    }

    void Window::onWindowClose(GLFWwindow *window) {
        glfwSetWindowShouldClose(window, 1);
    }

    void Window::processInput(GLFWwindow *window, int key, int scancode, int action, int mods) {
        Window* winClass{ static_cast<Window*>(glfwGetWindowUserPointer(window)) };
        const float cameraSpeed{0.05f};

        if(action == GLFW_PRESS) {
            bool updateCamera{false};
            switch(key) {
            case GLFW_KEY_W:
                winClass->m_threadsData->startMovingCamera(cmakub::ThreadsData::Direction::FRONT);
                break;
            case GLFW_KEY_S:
                winClass->m_threadsData->startMovingCamera(cmakub::ThreadsData::Direction::BACK);
                break;
            case GLFW_KEY_A:
                winClass->m_threadsData->startMovingCamera(cmakub::ThreadsData::Direction::LEFT);
                break;
            case GLFW_KEY_D:
                winClass->m_threadsData->startMovingCamera(cmakub::ThreadsData::Direction::RIGHT);
                break;
            }
        } else if(action == GLFW_RELEASE) {
            bool updateCamera{false};
            switch(key) {
            case GLFW_KEY_W:
                winClass->m_threadsData->stopMovingCamera(cmakub::ThreadsData::Direction::FRONT);
                break;
            case GLFW_KEY_S:
                winClass->m_threadsData->stopMovingCamera(cmakub::ThreadsData::Direction::BACK);
                break;
            case GLFW_KEY_A:
                winClass->m_threadsData->stopMovingCamera(cmakub::ThreadsData::Direction::LEFT);
                break;
            case GLFW_KEY_D:
                winClass->m_threadsData->stopMovingCamera(cmakub::ThreadsData::Direction::RIGHT);
                break;
            }
        }
    }


    void Window::mouseInput(GLFWwindow *window, double xpos, double ypos) {
        static float lastX{300};
        static float lastY{240};

        float xoffset{xpos - lastX};
        float yoffset{ypos - lastY};
        lastX = xpos;
        lastY = ypos;

        constexpr float sensitivity{0.05f};
        //TODO: make it working
    }
}
