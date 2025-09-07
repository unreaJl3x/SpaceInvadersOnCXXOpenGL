#include <iostream>
#include <thread>
#include <windows.h>
#include "src/opengl/GLFWOverlay.h"


int main(int argc, char** argv) {
    SetConsoleTitleA("Hui");
    GLFWOverlay *over=new GLFWOverlay("Tetst", 800 , 600 );

    getchar();
    return 0;
}