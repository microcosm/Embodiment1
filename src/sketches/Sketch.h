#pragma once

#include "ofMain.h"
#include "ofxLayerMask.h"
#include "ofxTexturePlane.h"

class Sketch {

public:
    virtual void setup();
    virtual void update();
    virtual void draw();
    void setSize(int _width, int _height);

    int width, height, halfWidth, halfHeight, doubleWidth, doubleHeight, tripleWidth, tripleHeight;
};
