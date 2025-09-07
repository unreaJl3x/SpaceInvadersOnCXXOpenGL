#include <iostream>
#include <thread>
#include <windows.h>

#include "src/opengl/GLFWOverlay.h"
#include "engine/gamedef.h"
#include "engine/entity_person.h"
#include "engine/Scene.h"
#include "engine/ImageController.h"
#include "engine/FractionController.h"
#include "engine/ConfigMaster.h"
#include "engine/console.h"
#include "lib/glm/glm.hpp"
#include "src/engine/MapGeneretion.h"

#define GDEF_ROTATE_LEFT -1
#define GDEF_ROTATE_RIGHT 1
void Rotate(int rotateDirection, int* currentDirection) {
    cout<< "rotate "<<*currentDirection<<" to ";
    *currentDirection += rotateDirection;
    if ( *currentDirection < 0 ) { *currentDirection = GDEF_DIRECTION_MAX; }
    else if ( *currentDirection > GDEF_DIRECTION_MAX ) { *currentDirection = 0; }
    cout<<*currentDirection<<endl;
}

int main(int argc, char** argv) {
    gamedef_t gDate;
    gDate.gameName = "SimpleRPG";
    gDate.argc = argc;
    gDate.argv = argv;
    gDate.dir = argv[0];
    gDate.company = "MatchbookRomance";

    SetConsoleTitleA(gDate.gameName);

    ImageController ic;
    ic.Add("SWORD_CURSOR","cursor_sword.png");
    ic.Add("WIN_ICO","puppet.png");
    ic.Add("DEMON","demon.png");
    ic.Add("BAR","plbar.png");

    GLFWOverlay *over=new GLFWOverlay("Tetst", 800 , 600 , ic.Get("WIN_ICO").c_str(), ic.Get("SWORD_CURSOR").c_str());

    int *dir = new int(0); *dir = PERSON_DIRECTIONS::FRONT;

    MAP<10,10> map = MAP<10, 10>(dir);
    GenerateMap<10,10>(map.map);

    map.print();
    bool walk;

    GLFWimage* img=over->LoadImageA(ic.Get("BAR").c_str());

    while (!glfwWindowShouldClose(over->GetWindow())) {
        //glClearColor(1.f,1.f,1.f,1.f);
        if (GetKeyActive(GDEF_VK_W)) {
            walk=map.Move(true);
        }
        if (GetKeyActive(GDEF_VK_S)) {
            walk=map.Move(false);
        }
        if (GetKeyActive(GDEF_VK_A)) {
            Rotate(GDEF_ROTATE_LEFT,dir);
            walk=true;
        }
        if (GetKeyActive(GDEF_VK_D)) {
            Rotate(GDEF_ROTATE_RIGHT,dir);
            walk=true;
        }
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_ACCUM_BUFFER_BIT );

        over->DrawRandomNoise(new vector<GDEFPOINT> {GDEFPOINT(0.19f,0.6f),GDEFPOINT(0.81f,1.f)});
        vector<GDEFPOINT> noisePoints = vector<GDEFPOINT>();
        float *color=new float[3]{1.0f,.0f,.0f};
        over->DrawWorld<10, 10>(map.GetNextChar<GLFWO_DW_DRAWDISTANCE>(), &walk,&noisePoints, color);
        over->DrawRandomNoise(&noisePoints,50,color);
        over->DrawUI();
        //free(noisePoints);
        noisePoints.clear();

        /// img

        //glDrawPixels(img->width,img->height,GL_RGBA,GL_UNSIGNED_BYTE,img->pixels);

        ///

        glFlush();
        glfwPollEvents();
        glfwSwapBuffers(over->GetWindow());
        this_thread::sleep_for(chrono::milliseconds(3));
        walk=false;
    }
    getchar();
    return 0;
}