#include "Sketch.h"

void Sketch::setup(){

}

void Sketch::update(){
    
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