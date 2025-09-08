#include <iostream>
#include <thread>
#include <windows.h>
#include "src/opengl/GLFWOverlay.h"


int main(int argc, char** argv) {
    SetConsoleTitleA("Hui");
    GLFWOverlay *over=new GLFWOverlay("Tetst", 800 , 600 );

    while (!glfwWindowShouldClose(over->GetWindow())) {
        //glFlush();
        glfwPollEvents();
        glfwSwapBuffers(over->GetWindow());
        this_thread::sleep_for(chrono::milliseconds(3));
    }

    getchar();
    return 0;
}