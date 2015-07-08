#include "sketch20150701.h"

void sketch20150701::setup(vector<Skeleton>* _skeletons){
    Sketch::setup(_skeletons);
    setSize(500, 500);

    minInfluenceX = -0.01;
    maxInfluenceX = 0.01;
    minInfluenceY = -0.015;
    maxInfluenceY = 0.003;
    minInfluenceZ = 0.2;
    maxInfluenceZ = 0.4;

    ofEnableSmoothing();
    shapeSystem.setup();
    masker.setup(8);
    
    for(int i = 0; i < 8; i++) {
        textures.push_back(texture);
        textures.at(i).setup("2015-07-01/road" + ofToString(i % 4 + 1) + ".png", (i+1) * 0.3);
    }
    
    shapeSize = 100;
    thickness = 100;
    halfShapeSize = shapeSize * 0.5;
    
    for(int i = 0; i < width; i += shapeSize) {
        for(int j = 0; j < height; j += shapeSize) {
            shape.setupHollowArc(30, thickness, shapeSize, 180);
            shape.setColor(ofColor::fromHsb(ofRandom(255), ofRandom(100, 255), ofRandom(100, 255)));
            shape.setBlur(30);
            shape.setPosition(ofVec3f(i + halfShapeSize, j + halfShapeSize, 0));
            shape.rotateZ(ofRandom(360));
            shapes.push_back(shape);
        }
    }
    
    for(int i = 0; i < shapes.size(); i++) {
        shapeSystem.add(shapes.at(i));
    }
}

void sketch20150701::update(){
    Sketch::update();
    for(int i = 0; i < shapes.size(); i++) {
        i % 2 == 0 ?
        shapes.at(i).incrementRotateZ(1) :
        shapes.at(i).incrementRotateZ(-1);
    }

    if(skeletons->size() > 0) {
        leftInfluence.x = ofMap(skeletons->at(0).getLeftHandNormal().x, 0, 1, minInfluenceX, maxInfluenceX);
        leftInfluence.y = ofMap(skeletons->at(0).getLeftHandNormal().y, 0, 1, minInfluenceY, maxInfluenceY);
        leftInfluence.z = ofMap(skeletons->at(0).getLeftHandNormal().z, 0, 1, minInfluenceZ, maxInfluenceZ);
        rightInfluence.x = ofMap(skeletons->at(0).getRightHandNormal().x, 0, 1, minInfluenceX, maxInfluenceX);
        rightInfluence.y = ofMap(skeletons->at(0).getRightHandNormal().y, 0, 1, minInfluenceY, maxInfluenceY);
        rightInfluence.z = ofMap(skeletons->at(0).getRightHandNormal().z, 0, 1, minInfluenceZ, maxInfluenceZ);

        for(int i = 0; i < textures.size(); i++) {
            if(i % 2 == 0) {
                textures.at(i).incrementTextureOffset(leftInfluence);
                textures.at(i).setTextureScale(leftInfluence.z * (i+1));
            } else {
                textures.at(i).incrementTextureOffset(rightInfluence);
                textures.at(i).setTextureScale(rightInfluence.z * (i+1));
            }
        }
    }
    
    for(int i = 0; i < masker.numLayers(); i++) {
        masker.beginLayer(i);
        {
            ofBackground(ofColor::black);
            ofEnableAlphaBlending();
            rotateScreen(90 * i);
            shapeSystem.draw();
            ofDisableAlphaBlending();
        }
        masker.endLayer(i);
        
        masker.beginMask(i);
        {
            ofEnableAlphaBlending();
            if(ofGetFrameNum() == 0) {
                ofBackground(ofColor::black);
            } else {
                ofSetColor(ofColor::black, 10);
                ofRect(0, 0, width, height);
            }
            
            ofSetColor(ofColor::white, 196);
            textures.at(i % textures.size()).draw();
            if(ofRandom(1) < 0.0066666) {
                for(int j = 0; j < 4; j++) {
                    ofSetColor(j % 2 == 0 ? ofColor(ofColor::white, ofRandom(64, 196)) : ofColor::black);
                    ofTriangle(ofRandom(-width, 0), ofRandom(-height, 0),
                               ofRandom(0, width), ofRandom(0, height),
                               ofRandom(width, doubleWidth), ofRandom(height, doubleHeight));
                    rotateScreen(90);
                }
            }
            ofDisableAlphaBlending();
        }
        masker.endMask(i);
    }
}

void sketch20150701::draw(){
    Sketch::draw();
    ofBackground(ofColor::black);
    masker.draw();
    masker.drawOverlay();
    
/*    ofBackground(ofColor::black);
    ofEnableAlphaBlending();
    shapeSystem.draw();
    ofDisableAlphaBlending();*/
}

void sketch20150701::rotateScreen(float degrees) {
    ofTranslate(halfWidth, halfHeight, 0);
    ofRotate(degrees);
    ofTranslate(-halfWidth, -halfHeight, 0);
}