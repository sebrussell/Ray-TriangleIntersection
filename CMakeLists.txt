cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_STANDARD 11)
project(RayIntersection)

include_directories(
	${PROJECT_SOURCE_DIR}/libraries/glm
	${PROJECT_SOURCE_DIR}/libraries/glfw/include
	${PROJECT_SOURCE_DIR}/libraries/glad/include
	${PROJECT_SOURCE_DIR}/libraries/assimp/include
	${PROJECT_SOURCE_DIR}/libraries/loader/include
)

link_directories(
	${PROJECT_SOURCE_DIR}/libraries/assimp/lib
	${PROJECT_SOURCE_DIR}/libraries/glfw/lib
)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "-fopenmp")

add_executable(demo
  main.cpp    
  Math.cpp
  OpenGL.cpp
  libraries/glad/src/glad.c
  Object.cpp
)


target_link_libraries(demo assimp glfw3) 





