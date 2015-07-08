#include "ofApp.h"

void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofEnableSmoothing();

    smallFont.loadFont("selena.otf", 16);
    largeFont.loadFont("selena.otf", 48);
    
    kinect.setup(12345, smallFont);
    skeletons = kinect.getSkeletons();
    renderer.setup(skeletons, largeFont);
    renderer.hideAll();
    drawKinect = false;
    
    kinectCommands = "KINECT\n\n";
    kinectCommands.append("d = show debug\n");
    kinectCommands.append("k = show kinect\n");

    sketch20150701.setup(skeletons);
    initFbo(slicingFbo, sketch20150701.width, sketch20150701.height);
    numProjectionMaskBuffers = 3;
    projectionMaskBufferWidth = sketch20150701.width / numProjectionMaskBuffers;
    for(int i = 0; i < numProjectionMaskBuffers; i++) {
        patterns.push_back(projectionMask.newPattern(projectionMaskBufferWidth, sketch20150701.height));
    }

    //projectionMask.setup(HOMOGRAPHY);
    projectionMask.setup(HOMOGRAPHY, PRESETS_PRODUCTION);
}

void ofApp::update(){
	kinect.update();
    projectionMask.update(mouseX, mouseY);
    sketch20150701.update();
}

void ofApp::draw(){
    slicingFbo.begin();
    {
        sketch20150701.draw();
    }
    slicingFbo.end();

    for(int i = 0; i < numProjectionMaskBuffers; i++) {
        patterns.at(i)->begin();
        {
            slicingFbo.draw(-(projectionMaskBufferWidth * i), 0);
        }
        patterns.at(i)->end();
    }
    projectionMask.draw();

    if(drawKinect) {
        ofEnableAlphaBlending();
        ofSetColor(ofColor::black, 200);
        ofFill();
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
        ofDisableAlphaBlending();
        ofSetColor(ofColor::white);
        kinect.drawDebug();
        renderer.draw();
        smallFont.drawString(kinectCommands, ofGetWidth() - 200, 60);
        largeFont.drawString("fps:\n" + ofToString(ofGetFrameRate()), ofGetWidth() - 220, ofGetHeight() - 100);
    } else {
        kinect.drawDebug();
        smallFont.drawString(kinectCommands, ofGetWidth() - 200, 60);
    }
}

void ofApp::keyReleased(int key){
    if(key == 'k') {
        drawKinect = !drawKinect;
        renderer.toggleJoints();
        renderer.toggleBones();
        renderer.toggleHands();
        renderer.toggleRanges();
    } else if(key == 'd') {
        kinect.toggleDebug();
    } else {
        projectionMask.keyReleased(key);
    }
}

void ofApp::initFbo(ofFbo &fbo, int width, int height) {
    fbo.allocate(width, height, GL_RGB);
    fbo.begin();
    ofBackground(ofColor::white);
    fbo.end();
}

void ofApp::mouseDragged(int x, int y, int button){
    projectionMask.mouseDragged();
}

void ofApp::mousePressed(int x, int y, int button){
    projectionMask.mousePressed();
}

void ofApp::mouseReleased(int x, int y, int button){
    projectionMask.mouseReleased();
}

void ofApp::keyPressed(int key){}
void ofApp::mouseMoved(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}