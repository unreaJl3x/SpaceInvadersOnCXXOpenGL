#ifndef WRECT_H
#define WRECT_H
#include <Windows.h>

struct WRECT : RECT {
    WRECT()=default;
    WRECT(long l,long t,long r,long b)
    {
        left = l;
        right=r;
        top=t;
        bottom=b;
    }
    WRECT(RECT r) {
        this->top = r.top;
        this->bottom = r.bottom;
        this->right = r.right;
        this->left = r.left;
    }
    WRECT(RECT *r) {
        this->top = r->top;
        this->bottom = r->bottom;
        this->right = r->right;
        this->left = r->left;
    }

    void operator+=(RECT* r) {
        this->left += r->left;
        this->top += r->top;
        this->bottom += r->top;
        this->right += r->left;
    }
    void operator+=(RECT r) {
        this->left += r.left;
        this->top += r.top;
        this->bottom += r.top;
        this->right += r.left;
    }
    void operator*=(RECT* r) {
        this->left += r->left;
        this->top += r->top;
        this->bottom += r->bottom;
        this->right += r->right;
    }
    void operator=(RECT* r) {
        this->left = r->left;
        this->top = r->top;
        this->bottom = r->bottom;
        this->right = r->right;
    }
    void operator=(RECT r) {
        this->left = r.left;
        this->top = r.top;
        this->bottom = r.bottom;
        this->right = r.right;
    }
    void operator-=(RECT r) {
        this->left-= r.left;
        this->top-= r.top;
        this->right-= r.right;
        this->bottom-= r.bottom;
    }
    int width() { return right-left;}
    int height() { return bottom-top;}
};
#endif