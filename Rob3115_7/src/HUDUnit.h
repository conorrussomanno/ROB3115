//
//  HUDSpinner.h
//  emptyExample
//
//  Created by Conor Russomanno on 4/24/13.
//
//
#include "ofMain.h"

class HUDUnit : public ofBaseApp{
    
public:
    
    int numSegments;
    float rotateSpeed, startSweep, sweep, radius1, radius2;
    ofColor color;
    
    void setup(float _rotateSpeed, ofColor _color, int _numSegments, float _startSweep, float _sweep, float _radius1, float _radius2){
        
        rotateSpeed = _rotateSpeed;
        numSegments = _numSegments;
        startSweep = _startSweep;
        sweep = _sweep;
        radius1 = _radius1;
        radius2 = _radius2;
        color = _color;
        
    }
    //--------------------------------------------------------------
    void update(){

    }
    
    //--------------------------------------------------------------
    void draw(float x, float y){
        ofPushMatrix();
        ofTranslate(x,y);
        ofRotate(ofGetElapsedTimef()*rotateSpeed, 0, 0, 1);
        ofSetColor(color);
        ofSetLineWidth(0);
        ofFill();
        ofSetPolyMode(OF_POLY_WINDING_ODD);
        ofBeginShape();
        float angleStep 	= TWO_PI/(((float)numSegments)*(1/sweep));
        for (int i = 0; i <= numSegments; i++){
            float vertexAngle = (TWO_PI * startSweep) + (i) * angleStep;
            float x2 = radius1 * cos(vertexAngle);
            float y2 = radius1 * sin(vertexAngle);
            ofVertex(x2,y2);
        }
        for (int i = 0; i <= numSegments; i++){
            float vertexAngle = (TWO_PI * startSweep) + ((float)numSegments)*angleStep - ((i) * angleStep);
            float x2 = (radius2) * cos(vertexAngle);
            float y2 = (radius2) * sin(vertexAngle);
            ofVertex(x2,y2);
        }
        ofEndShape(OF_CLOSE);
        ofPopMatrix();
    }
};


