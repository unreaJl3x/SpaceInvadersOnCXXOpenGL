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

/// map
/// 0 ####################################
/// 1 #----------------------------------#
/// 2 #-----------------front------------#
/// 3 #-------------right-P-left---------#
/// 4 #----------------back--------------#
/// 5 ####################################

void GLFWOverlay::DrawUIBox(float sx, float sy, float ex, float ey, float* color, bool outline) {
    glBegin(GL_QUADS);
    glColor3f(color[0],color[1],color[2]);
    glVertex2f(sx,sy);
    glVertex2f(sx,ey);
    glVertex2f(ex,ey);
    glVertex2f(ex,sy);
    glEnd();
}

float *GLFWOverlay::DrawOnVertex(vector<GDEFPOINT> vertexes, float*startColor,float*endColor) {
    float * usingColor = new float[3] {1.f,0.0f,0.0f};
    glBegin(GL_QUADS);
    for (auto p : vertexes) {
        if ( p.state == GDEF_GDEFPOINT_STATE_TOP ) { usingColor=endColor; }
        else if ( p.state == GDEF_GDEFPOINT_STATE_BOTTOM ) { usingColor = startColor;}
        else { usingColor = startColor;}

        glColor3f(usingColor[0], usingColor[1], usingColor[2]);
        glVertex2f(p.x,p.y);
    }
    glEnd();
    return endColor;
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

void GLFWOverlay::DrawRandomNoise(vector<GDEFPOINT>* list, int count, float *color)  {
    glPointSize(2+(rand()%10+1>=4?1:0));
    glBegin(GL_POINTS);
    if (list->begin()==list->end()) {return;}
    for (auto i=0;i<list->size()-1;i++) {
        if ((*list)[i].y == (*list)[i+1].y || (*list)[i].x==(*list)[i+1].x ) {
            cout << "[DrawRandomNoise] ERR? start point y eaquls end point y. Safing programm from crash (^_^)" << endl;
            return;
        }
        for (auto j = 0; j < count; j++) {
            glColor3f(color[0], color[1], color[2]);
            glVertex2f((float((rand() % int(((*list)[i+1].x - (*list)[i].x) * windowResolution.x)) + (((*list)[i].x) * windowResolution.x)) /
                        windowResolution.x),
                       (float((rand() % int(((*list)[i+1].y - (*list)[i].y) * windowResolution.y)) + (((*list)[i].y) * windowResolution.y)) /
                        windowResolution.y));
        }
    }
    glEnd();
}