#include "GLFWOverlay.h"

#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image.h"
#pragma comment(lib,"glfw3.lib")
#pragma comment(lib,"glew32s.lib")
using namespace std;
GLFWimage *GLFWOverlay::LoadImage(const char* path) {
    GLFWimage *img = new GLFWimage ;
    img->pixels=stbi_load(path,&img->width,&img->height,nullptr,STBI_rgb_alpha);
    if (!img->pixels) { std::cout<<"[GLFWOverlay::LoadImage] Err? invalid window icon, mayby corrypt path."<<endl; return nullptr; }
    return img;
}

GLFWOverlay::GLFWOverlay(const char *winName, int w,int h,const char *pathToIcon, const char *pathToCursor) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);
    if (!glfwInit()) { std::cout<<"[GLFWOverlay constructor] Err? failure glfw init."<<std::endl;return;}
    this->window = glfwCreateWindow(w,h,winName,NULL,NULL);
    if (!window) { glfwTerminate(); std::cout<<"[GLFWOverlay constructor] Err? failure creating window."<<std::endl;return;}
    glfwMakeContextCurrent(window);
    windowResolution.x = w;
    windowResolution.y = h;

    if (  !SetWinIcon(pathToIcon)  ) { cout<<"[GLFWOverlay constructor] Err? failure icon"<<endl;  }
    if (  !SetCursor(pathToCursor, "startCursor") ) { cout<<"[GLFWOverlay constructor] Err? failure cursor"<<endl; }

    glewExperimental=GL_TRUE;
    glewInit();
    glMatrixMode(GL_PROJECTION);
    glOrtho(0,1.f,0,1.f,-1.f,1.f);
    glViewport(0,0,(GLint)w,(GLint)h);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_PROGRAM_POINT_SIZE_EXT);
    glEnable(GL_PROGRAM_POINT_SIZE);


    return;
}

GLFWOverlay::~GLFWOverlay() {
    std::cout<<"exit"<<std::endl;
    glfwTerminate();
}

bool GLFWOverlay::SetCursor(const char* path, string name) {
    GLFWimage *cursor;
    cursor = LoadImage(path);
    if (cursor) {
        GLFWcursor *glcursor = glfwCreateCursor(cursor, cursor->width * (28/cursor->height), cursor->height * (28/cursor->width)); //need image 28x28
        glfwSetCursor(window, glcursor);
        this->cursors.push_back( new GLFWOimage(cursor, name) );

        return true;
    }
    return false;
}

bool GLFWOverlay::SetCursor(std::string name) {
    for (auto cur : cursors) {
        if (cur->name == name) {
            GLFWcursor *glcursor = glfwCreateCursor(cur, cur->width * (28/cur->height), cur->height * (28/cur->width)); //need image 28x28
            glfwSetCursor(window, glcursor);
            return true;
        }
    }
    return false;
}

bool GLFWOverlay::SetWinIcon(std::string path) {
    GLFWimage *ico;
    ico = LoadImage(path.c_str());
    if (ico) {
        glfwSetWindowIcon(window,1,ico);
        return true;
    }
    return false;
}