#pragma once

#include "ofMain.h"
#include "ofxLayerMask.h"
#include "ofxTexturePlane.h"
#include "ofxKinectV2OSC.h"

class Sketch {

public:
    virtual void setup(vector<Skeleton>* _skeletons);
    virtual void update();
    virtual void draw();
    void setSize(int _width, int _height);
    void setTopSpeed(int speed);
    void setLocation(float x, float y);
    void setAcceleration(float x, float y);
    void accelerateTowards(ofVec2f target, float multiplier);

    int width, height, halfWidth, halfHeight, doubleWidth, doubleHeight, tripleWidth, tripleHeight;
    vector<Skeleton>* skeletons;

    ofVec2f location, velocity, acceleration;
    int topspeed;
};
