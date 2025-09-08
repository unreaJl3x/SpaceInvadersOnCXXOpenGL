#ifndef DIRECTX9EXTERNALGUILIB_WPOINT_H
#define DIRECTX9EXTERNALGUILIB_WPOINT_H

#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;

class WPOINT : public POINT {
public:
    void operator += (POINT p) {
        this->x += p.x;
        this->y += p.y;
    }
    void operator += (POINT* p) {
        this->x += p->x;
        this->y += p->y;
    }
    void operator += (int i) {
        this->x += i;
        this->y += i;
    }
    void operator ++ ()  {
        this->x++;
        this->y++;
    }
    void operator *= (WPOINT p) {
        this->x *= p.x;
        this->y *= p.y;
    }
    void operator *= (WPOINT* p) {
        this->x *= p->x;
        this->y *= p->y;
    }
    void operator *= (int i) {
        this->x *= i;
        this->y *= i;
    }
    void operator *= (float i) {
        this->x *= i;
        this->y *= i;
    }


    bool operator != (WPOINT ap) {
        return ( this->x == ap.x )&&( this->y == ap.y );
    }
    bool operator != (WPOINT* ap) {
        return ( this->x == ap->x )&&( this->y == ap->y );
    }

    WPOINT (LONG x, LONG y){
        this->x=x;
        this->y=y;
    }
    WPOINT (RECT r){
        this->x=r.left;
        this->y=r.top;
    }
    WPOINT (RECT* r){
        this->x=r->left;
        this->y=r->top;
    }
    WPOINT(POINT p) {
        this->x = p.x;
        this->y = p.y;
    }
    WPOINT(POINT *p) {
        this->x = p->x;
        this->y = p->y;
    }

    /// \return vector[0] -> point of rect.left&rect.top ;
    ///   vector[1] -> point of rect.right&rect.bottom
    static std::vector<WPOINT> CreatePoints (RECT rect) {
        return std::vector<WPOINT> {WPOINT(rect.left,rect.top), WPOINT(rect.right,rect.bottom)};
    }
    /// \return vector[0] -> point of rect.left&rect.top  ;
    ///  vector[1] -> point of rect.right&rect.bottom
    static std::vector<WPOINT> CreatePoints (RECT* rect) {
        return std::vector<WPOINT> {WPOINT(rect->left,rect->top), WPOINT(rect->right,rect->bottom)};
    }
    static std::vector<POINT>* BoxToPoints(RECT* rect) {
        return new vector<POINT> {WPOINT(rect->left,rect->top), WPOINT(rect->right, rect->top),WPOINT(rect->right,rect->bottom),WPOINT(rect->left,rect->bottom)} ;
    }
};

#endif //DIRECTX9EXTERNALGUILIB_WPOINT_H