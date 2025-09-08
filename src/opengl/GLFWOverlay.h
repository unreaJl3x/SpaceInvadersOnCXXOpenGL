#ifndef GLFWOVERLAY_H
#define GLFWOVERLAY_H

#include <iostream>
#include <vector>

#define GLEW_STATIC
#include "lib/GLEW/include/glew.h"
#include "lib/GLEW/include/wglew.h"
#include "glfw3.h"
using namespace std;

class GLFWOverlay {
private:
    GLFWwindow *window;
    class GLFWOimage : public GLFWimage {
    public:
        string name;
        GLFWOimage();
        GLFWOimage(GLFWimage *cur, string name) {
            this->height = cur->height;
            this->width = cur->width;
            this->name = name;
            this->pixels = cur->pixels;
        }
    };
    vector<GLFWOimage *> cursors;
    POINT windowResolution;

public:
    bool SetCursor(const char *path, string name);
    bool SetCursor(string cursorName);
    bool SetWinIcon(string path);
    GLFWwindow *GetWindow() { return window; };
    GLFWOverlay(const char *windowName, int w, int h, const char *iconPath = "", const char *curosrPath = "");
    ~GLFWOverlay();

public:
    GLFWimage *LoadImage(const char *path);

public:
    void DrawSquad();
    void DrawTriangel();
    void DrawLine();
    void DrawText();
};

#endif