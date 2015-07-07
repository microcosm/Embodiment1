#include "ofApp.h"

void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofEnableSmoothing();

    sketches.push_back(&sketch20150701);

    for(int i = 0; i < sketches.size(); i++) {
        sketches.at(i)->setup();
        patterns.push_back(projectionMask.newPattern(sketches.at(i)->width, sketches.at(i)->height));
    }
    projectionMask.setup(HOMOGRAPHY);
    //designer.setup(HOMOGRAPHY, PRESETS_PRODUCTION);

    smallFont.loadFont("selena.otf", 16);
    largeFont.loadFont("selena.otf", 48);

    kinect.setup(12345, smallFont);
    skeletons = kinect.getSkeletons();
    renderer.setup(skeletons, largeFont);
    renderer.hideAll();
    drawKinect = false;
}

void ofApp::update(){
	kinect.update();
    projectionMask.update(mouseX, mouseY);
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
    projectionMask.draw();
    kinect.drawDebug();

    if(drawKinect) {
        ofEnableAlphaBlending();
        ofSetColor(ofColor::black, 200);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
        ofDisableAlphaBlending();
        renderer.draw();
    }

    string commands = "COMMANDS\n\n";
    commands.append("d = show debug\n");
    commands.append("k = show kinect\n");

    ofSetColor(ofColor::white);
    smallFont.drawString(commands, ofGetWidth() - 220, 40);
    largeFont.drawString("fps:\n" + ofToString(ofGetFrameRate()), ofGetWidth() - 220, ofGetHeight() - 100);
}

void ofApp::keyReleased(int key){
    if(key == 'k') {
        drawKinect = true;
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