cmake_minimum_required(VERSION 3.16)
project(cmakub)

file(GLOB_RECURSE SOURCES_COMMON RELATIVE ${CMAKE_SOURCE_DIR} "src/common/*")

if(SERVER)
    file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/server/*")
else()
    file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/client/*")
    find_package(glfw3 3.3 REQUIRED)
    find_package(OpenGL REQUIRED)
endif()

find_package(Threads REQUIRED)
find_package(spdlog REQUIRED)

add_executable(cmakub ${SOURCES} ${SOURCES_COMMON})

target_include_directories(cmakub PUBLIC
                       $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
                       $<INSTALL_INTERFACE:include>)
if(SERVER)

else()
target_link_libraries(cmakub PUBLIC glfw OpenGL::GL ${CMAKE_DL_LIBS})
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
endif()
target_link_libraries(cmakub PUBLIC Threads::Threads)
target_link_libraries(cmakub PRIVATE spdlog::spdlog)