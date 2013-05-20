#include "ofMain.h"

class HUDRangeMarker : public ofBaseApp{
public:
    
    void setup(ofVec3f _rangeBound1, ofVec3f _rangeBound2, int _numIncrements, ofImage _img, float _imgWidth, float _imgHeight, ofColor _color, float _chanceToUpdate);
    void update();
    void draw();
    
    //variables passed in setup
    ofVec3f rangeBound1;
    ofVec3f rangeBound2;
    int numIncrements;
    ofImage img;
    float imgWidth, imgHeight;
    
    ofColor color;
    
    ofVec3f curLocation;
    int currentIncrement;
    
    float chanceToUpdate;
    
};