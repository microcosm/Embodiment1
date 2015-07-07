#include "ofApp.h"

void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofEnableSmoothing();
    
    sketches.push_back(&sketch20150701);
    
    for(int i = 0; i < sketches.size(); i++) {
        sketches.at(i)->setup();
        patterns.push_back(designer.newPattern(sketches.at(i)->width, sketches.at(i)->height));
    }
    designer.setup(HOMOGRAPHY);
    //designer.setup(HOMOGRAPHY, PRESETS_PRODUCTION);
}

void ofApp::update(){
    designer.update(mouseX, mouseY);
    for(int i = 0; i < sketches.size(); i++) {
        sketches.at(i)->update();
    }
}

void ofApp::draw(){
    for(int i = 0; i < sketches.size(); i++) {
        patterns.at(i)->begin();
        {
            sketches.at(i)->draw();
        }
        patterns.at(i)->end();
    }
    designer.draw();
}

void ofApp::keyReleased(int key){
    designer.keyReleased(key);
}

void ofApp::mouseDragged(int x, int y, int button){
    designer.mouseDragged();
}

void ofApp::mousePressed(int x, int y, int button){
    designer.mousePressed();
}

void ofApp::mouseReleased(int x, int y, int button){
    designer.mouseReleased();
}

void ofApp::keyPressed(int key){}
void ofApp::mouseMoved(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}