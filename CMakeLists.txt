cmake_minimum_required(VERSION 3.28)
project(SimpleCXXRPGOnDX9)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(lib)
include_directories(src)

include_directories(lib/GLFW/includes)
#link_directories(lib/GLFW/32vc22)
link_directories(lib/GLFW/64vc22)
b,fwsednjklqfejhklaesawsefhnjkl3erqw
include_directories(lib/GLEW/include)
#link_directories(lib/GLEW/Win32)
link_directories(lib/GLEW/x64)

#configure_file(src/engine/names.txt ${CMAKE_BUILD_RPATH}Debug/name.txt)
#configure_file(src/engine/entity_person_stats_coof.txt ${CMAKE_BUILD_RPATH}Debug/entity_person_stats_coof.txt)

add_executable( ${PROJECT_NAME}
        src/opengl/GLFWOverlay.h
        src/opengl/GLFWOverlay.cpp
        main.cpp
)



target_link_libraries(${PROJECT_NAME} glfw3 glew32s opengl32  )