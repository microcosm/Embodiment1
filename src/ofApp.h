#pragma once

#include "ofMain.h"
#include "ofxProjectionMask.h"
#include "ofxLayerMask.h"
#include "ofxKinectV2OSC.h"
#include "Sketch.h"
#include "sketch20150701.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    ofxProjectionMask projectionMask;
    vector<ofxLayerMask*> patterns;
    vector<Sketch*> sketches;

    sketch20150701 sketch20150701;

    ofxKinectV2OSC kinect;
    Skeleton* skeleton;
    vector<Skeleton>* skeletons;
    ofTrueTypeFont smallFont, largeFont;
    BodyRenderer renderer;
    bool drawKinect;
};