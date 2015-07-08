#include "Sketch.h"

void Sketch::setup(vector<Skeleton>* _skeletons){
    skeletons = _skeletons;
    topspeed = 1000;
    setLocation(ofGetWidth() * 0.5, ofGetHeight() * 0.5);
    setAcceleration(0, 0.02);
}

void Sketch::update(){
    velocity += acceleration;
    velocity.limit(topspeed);
    location += velocity;
}

void Sketch::draw(){
    
}

void Sketch::setSize(int _width, int _height) {
    width = _width;
    height = _height;
    halfWidth = width * 0.5;
    halfHeight = height * 0.5;
    doubleWidth = width * 2;
    doubleHeight = height * 2;
    tripleWidth = width * 3;
    tripleHeight = height * 3;
}

void Sketch::setTopSpeed(int speed) {
    topspeed = speed;
}

void Sketch::setLocation(float x, float y) {
    location.set(x, y);
}

void Sketch::setAcceleration(float x, float y) {
    acceleration.set(x, y);
}

void Sketch::accelerateTowards(ofVec2f target, float multiplier) {
    acceleration = target - location;
    acceleration.normalize();
    acceleration *= multiplier;
}