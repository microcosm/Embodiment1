#pragma once

#include "ofMain.h"
#include "Sketch.h"
#include "ofxLayerMask.h"
#include "ofxTexturePlane.h"
#include "ofxShapeSystem.h"

class sketch20150701 : public Sketch {

public:
    void setup();
    void update();
    void draw();
    
    void rotateScreen(float degrees);
    ofxShapeSystem shapeSystem;
    vector<ofxShape> shapes;
    ofxShape shape;
    
    float shapeSize, halfShapeSize, thickness;
    vector<ofxTexturePlane> textures;
    ofxTexturePlane texture;
    ofxLayerMask masker;
    int finalFrame, frameDecay, lastDrawableFrameForLoop;
};