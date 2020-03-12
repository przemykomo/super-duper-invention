cmake_minimum_required(VERSION 3.16)
project(cmakub)

file(GLOB_RECURSE SOURCES_COMMON RELATIVE ${CMAKE_SOURCE_DIR} "src/common/*")

if(SERVER)
    file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/server/*")
else()
    file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/client/*")
endif()

add_executable(cmakub ${SOURCES} ${SOURCES_COMMON})

find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

target_include_directories(cmakub PUBLIC
                       $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
                       $<INSTALL_INTERFACE:include>)
if(SERVER)

else()
target_link_libraries(cmakub PUBLIC glfw OpenGL::GL ${CMAKE_DL_LIBS})
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
endif()