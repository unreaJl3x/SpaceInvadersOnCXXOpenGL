//
// Любой объект на сцене будет брать свои ноги от сюда
//

#ifndef SIMPLECXXRPGONDX9_OBJ_H
#define SIMPLECXXRPGONDX9_OBJ_H

#include <iostream>
#include "WPOINT.h"
#include "WRECT.h"

class Obj {
private:
    struct Transform {
        double rotate;
        int x, y;
    };

private:
    Transform transform;
    char name[20];
    WRECT box;

public:
    Obj()=default;
    Obj(std::string name, POINT p, int width, int height);
};

#endif //SIMPLECXXRPGONDX9_OBJ_H
