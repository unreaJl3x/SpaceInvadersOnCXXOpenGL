#ifndef GLFWOVERLAY_H
#define GLFWOVERLAY_H

#include <iostream>
#include <vector>

#define GLEW_STATIC
#include "lib/GLEW/include/glew.h"
#include "lib/GLEW/include/wglew.h"
#include "glfw3.h"
#include "engine/gamedef.h"
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
    static float *DrawOnVertex(vector<GDEFPOINT> vertexes, float *startColor, float *colorEnd = nullptr);

public:
    static void DrawUIBox(float sx, float sy, float ex, float ey, float *color, bool outline = false);
    void DrawRandomNoise(vector<GDEFPOINT> *list, int count = 800, float *color = new float[3]{0.05f, 0.05f, 0.05f});

private:
    void CoofAddact(bool *mwall, float *mwallCoofX, float *mwallCoofY, float coofAddact) {
        if (*mwall) {
            if (*mwallCoofX > 1.f && *mwallCoofY > 1.f) {
                *mwallCoofX = 1.f;
                *mwallCoofY = 1.f;
            } else if (*mwallCoofX == 1.f && *mwallCoofY == 1.f) {
                *mwall = false;
            } else if (*mwallCoofX <= 1.f && *mwallCoofY <= 1.f) {
                *mwallCoofY += coofAddact;
                *mwallCoofX += coofAddact;
            } else if (*mwallCoofX >= 1.f && *mwallCoofY <= 1.f) {
                *mwallCoofY += coofAddact;
            } else if (*mwallCoofX <= 1.f && *mwallCoofY >= 1.f) {
                *mwallCoofX += coofAddact;
            }
        }
    }

public:
#define GLFWO_DW_COLOR_COOF     0.5f
#define GLFWO_DW_DRAWDISTANCE   3
#define GDEF_DW_LEFTCOOFY       ( i * 0.128f )
#define GDEF_DW_LEFTCOOFX       ( i * 0.118f )
#define GDEF_DW_RIGHTCOOFY      GDEF_DW_LEFTCOOFY
#define GDEF_DW_RIGHTCOOFX      -GDEF_DW_LEFTCOOFX
#define GDEF_DW_MIDDLECOOFY     ( i * 0.128f )
#define GDEF_DW_MIDDLECOOFX     (i*0.07f)
#define GDEF_COOF_ADDACT        0.01f
#define GDEF_COOF_ADDACTF        0.037f
#define GDEF_WALL_HEIGHT        1.2f
#define GDEF_DW_NOISE_COOF_SY 0.02f
#define GDEF_DW_NOISE_COOF_SX -0.02f
#define GDEF_DW_NOISE_COOF_EX 0.02f

#define GDEF_DW_VERTEXVECTORFLOOR vector<float> {0.07f, 0.47f, 0.19f, 0.6f, 0.32f, 0.6f, 0.25f, 0.47f, \
                                                 0.26f, 0.47f, 0.33f, 0.6f, 0.68f, 0.6f, 0.75f, 0.47f, \
                                                 0.76f, 0.47f,0.69f, 0.6f, 0.81f, 0.6f, 0.93f , 0.47f \
}
#define GDEF_DW_VERTEXVECTORWALL vector<float> {0.07f, 0.47f, 0.07f, GDEF_WALL_HEIGHT, 0.25f, GDEF_WALL_HEIGHT, 0.25f, 0.47f, \
                                                0.26f, 0.47f, 0.26f, GDEF_WALL_HEIGHT, 0.75f, GDEF_WALL_HEIGHT, 0.75f, 0.47f, \
                                                0.76f, 0.47f, 0.76f, GDEF_WALL_HEIGHT, 0.93f, GDEF_WALL_HEIGHT, 0.93f, 0.47f \
}
#define GDEF_DW_COOFVECTOR vector <double> { GDEF_DW_LEFTCOOFX, (GDEF_DW_LEFTCOOFX/1.72), GDEF_DW_LEFTCOOFY, GDEF_DW_MIDDLECOOFX, -GDEF_DW_MIDDLECOOFX, GDEF_DW_MIDDLECOOFY, (GDEF_DW_RIGHTCOOFX/1.72),GDEF_DW_RIGHTCOOFX, GDEF_DW_RIGHTCOOFY}
#define GDEF_DW_STATEVECTOR vector<char> {  GDEF_GDEFPOINT_STATE_TOP,GDEF_GDEFPOINT_STATE_BOTTOM,GDEF_GDEFPOINT_STATE_TOP,GDEF_GDEFPOINT_STATE_BOTTOM, \
                                            GDEF_GDEFPOINT_STATE_TOP,GDEF_GDEFPOINT_STATE_BOTTOM,GDEF_GDEFPOINT_STATE_TOP,GDEF_GDEFPOINT_STATE_BOTTOM, \
                                            GDEF_GDEFPOINT_STATE_TOP,GDEF_GDEFPOINT_STATE_BOTTOM,GDEF_GDEFPOINT_STATE_TOP,GDEF_GDEFPOINT_STATE_BOTTOM }
    template <int w, int h>
    void DrawWorld(vector<char[3]> matrix, bool* walk, vector<GDEFPOINT>* noisePointsP, float* noiseColor) {
        GDEFCOLOR color(-0.1f,-0.1f,-0.1f);
        for (int i = 0; i < GLFWO_DW_DRAWDISTANCE;i++) {
            vector<GDEFPOINT> vertex;
            static bool mwall,mfloor = false;
            static float mwallCoofX,mwallCoofY, mfloorCoofx,mfloorCoofy = 1.0f;
            if (*walk) { mwallCoofX=0.7f; mwallCoofY=0.0f; mwall=true;mfloorCoofx=1.0f;mfloorCoofy=0.0f;mfloor=true; }

            CoofAddact(&mwall, &mwallCoofX, &mwallCoofY, GDEF_COOF_ADDACT);
            CoofAddact(&mfloor, &mfloorCoofx, &mfloorCoofy, GDEF_COOF_ADDACTF);

            GDEFPOINT noisePoints[2] = {GDEFPOINT(),GDEFPOINT()};

            for (int j = 0; j<3;j++) {
                if ( matrix[i][j] == GDEF_MAP_EMPTY ) {
                    vertex.push_back( GDEFPOINT( (i==0? mfloorCoofx : 1 )* (GDEF_DW_VERTEXVECTORFLOOR[j*8+0] - GDEF_DW_COOFVECTOR[j*3])   , (i==0? mfloorCoofy : 1 )* ( GDEF_DW_VERTEXVECTORFLOOR[j*8+1] - GDEF_DW_COOFVECTOR[(j*3)+2] ) , GDEF_DW_STATEVECTOR[j*4+0] ) );
                    vertex.push_back( GDEFPOINT( (i==0? mfloorCoofx : 1 )* (GDEF_DW_VERTEXVECTORFLOOR[j*8+2] - GDEF_DW_COOFVECTOR[j*3])   , (i==0? mfloorCoofy : 1 )* ( GDEF_DW_VERTEXVECTORFLOOR[j*8+3]-GDEF_DW_COOFVECTOR[(j*3)+2] )  , GDEF_DW_STATEVECTOR[j*4+1]   ) );
                    noisePoints[0] = GDEFPOINT((vertex.end()-1)->x, (vertex.end()-1)->y-GDEF_DW_NOISE_COOF_SY);
                    vertex.push_back( GDEFPOINT( (i==0? mfloorCoofx : 1 )* (GDEF_DW_VERTEXVECTORFLOOR[j*8+4] - GDEF_DW_COOFVECTOR[(j*3)+1]) , (i==0? mfloorCoofy : 1 )* ( GDEF_DW_VERTEXVECTORFLOOR[j*8+5] - GDEF_DW_COOFVECTOR[(j*3)+2] )  , GDEF_DW_STATEVECTOR[j*4+1]   ) );
                    noisePoints[1] = GDEFPOINT((vertex.end()-1)->x, (vertex.end()-1)->y);
                    vertex.push_back( GDEFPOINT( (i==0? mfloorCoofx : 1 )* (GDEF_DW_VERTEXVECTORFLOOR[j*8+6] - GDEF_DW_COOFVECTOR[j*3+1]) , (i==0? mfloorCoofy : 1 )* ( GDEF_DW_VERTEXVECTORFLOOR[j*8+7] - GDEF_DW_COOFVECTOR[(j*3)+2] ) , GDEF_DW_STATEVECTOR[j*4+0] ) );
                    if (i == 0 || (i-2>-1 && (matrix[i-2][j]) == GDEF_MAP_WALL && (matrix[i-1][j]) != GDEF_MAP_EMPTY)||(i-1>-1 && (matrix[i-1][j]) == GDEF_MAP_WALL) ) {
                        noisePointsP->push_back(noisePoints[0]);noisePointsP->push_back(noisePoints[1]);
                    }
                }
                else if  ( matrix[i][j] == GDEF_MAP_WALL ) {
                    vertex.push_back( GDEFPOINT( mwallCoofX* (     GDEF_DW_VERTEXVECTORWALL[j*8+0]-GDEF_DW_COOFVECTOR[j*3]    )   , mwallCoofY* (GDEF_DW_VERTEXVECTORWALL[j*8+1]-GDEF_DW_COOFVECTOR[(j*3)+2])   , GDEF_DW_STATEVECTOR[j*4+1]   ) );
                    vertex.push_back( GDEFPOINT( mwallCoofX* (     GDEF_DW_VERTEXVECTORWALL[j*8+2]-GDEF_DW_COOFVECTOR[j*3]    )   , mwallCoofY* (GDEF_DW_VERTEXVECTORWALL[j*8+3]-GDEF_DW_COOFVECTOR[(j*3)+2])   , GDEF_DW_STATEVECTOR[j*4+2]) );
                    vertex.push_back( GDEFPOINT( mwallCoofX* (     GDEF_DW_VERTEXVECTORWALL[j*8+4]-GDEF_DW_COOFVECTOR[(j*3)+1]  )   , mwallCoofY* (GDEF_DW_VERTEXVECTORWALL[j*8+5]-GDEF_DW_COOFVECTOR[(j*3)+2])   , GDEF_DW_STATEVECTOR[j*4+2]) );
                    vertex.push_back( GDEFPOINT( mwallCoofX* (     GDEF_DW_VERTEXVECTORWALL[j*8+6]-GDEF_DW_COOFVECTOR[(j*3)+1]  )   , mwallCoofY* (GDEF_DW_VERTEXVECTORWALL[j*8+7]-GDEF_DW_COOFVECTOR[(j*3)+2])   , GDEF_DW_STATEVECTOR[j*4+1]   ) );
                } else {}
            }

            float *sColor = new float[3];
            color.CopyTo(sColor);
            sColor = GDEFCOLOR(sColor)+=GLFWO_DW_COLOR_COOF;
            DrawOnVertex(vertex,              color.GetPColor(),*walk?color.GetPColor():sColor);
            color.CopyIn(sColor);
            free(sColor);
            GDEFCOLOR(sColor).CopyTo(noiseColor);
        }
    }
    void DrawEntity(vector<char[3]> matrix) {

    };

    static void DrawUI() {
        DrawUIBox(0.0f,0.f,1.f,0.25f, new float[3]{0.6f,.6f,.1f});
        DrawUIBox(0.1f,0.05f,.12f,0.19f, new float[3]{.6f,.0f,.0f});
        DrawUIBox(0.13f,0.05f,.15f,0.19f, new float[3]{.0f,.0f,.9f});
    }
};

#endif