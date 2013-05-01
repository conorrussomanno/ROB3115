
#include "ofMain.h"

//HUDSpinner @ Bottom (2 Classes in this file)


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
    void update(float _currentAttValue){
        
    }
    
    //--------------------------------------------------------------
    void draw(float x, float y){
        ofPushStyle();
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
        ofPopStyle();
    }
};

class HUDSpinner : public ofBaseApp{
public:
    
    void setup(int count, float avgRotateSpeed, float rotationVariation, ofColor baseColor, float resolution, float minRadius, float maxRadius, float minWidth, float maxWidth);
    void update(float _currentAttValue, float _currentSignalQuality);
    void draw(float x, float y);
    
    vector <HUDUnit> units;

};
