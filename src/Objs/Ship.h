//
// Как наш так и вражеский
//

#ifndef SIMPLECXXRPGONDX9_SHIP_H
#define SIMPLECXXRPGONDX9_SHIP_H

#include "Obj.h"

class Ship : public Obj{
private:
    float currentSpeed, maxSpeed;

public:
    Ship()=default;

};


#endif //SIMPLECXXRPGONDX9_SHIP_H
