#include "HUDSpinner.h"

//--------------------------------------------------------------
void HUDSpinner::setup(int count, float avgRotateSpeed, float rotationVariation, ofColor baseColor, float resolution, float minRadius, float maxRadius, float minWidth, float maxWidth){
    
    for (int i = 0; i < count; i++){
        HUDUnit tempUnit;
        float rotateSpeed_ = avgRotateSpeed + ofRandom(-rotationVariation, rotationVariation);
        ofColor color_;
        color_.set(baseColor.r, baseColor.g, baseColor.b, ofRandom(20, 130));
        float numSegments_ = resolution;
        float startSweep_ = ofRandom(1);
        float sweep_ = ofRandom(1);
        float width = ofRandom(minWidth, maxWidth);
        float radius = ofRandom(minRadius, maxRadius);
        float innerEdge = radius - width/2;
        float outerEdge = radius + width/2;
        tempUnit.setup(rotateSpeed_, color_, numSegments_, startSweep_, sweep_, innerEdge, outerEdge);
        units.push_back(tempUnit);
    }
}

//--------------------------------------------------------------
void HUDSpinner::update(){
    
}

//--------------------------------------------------------------
void HUDSpinner::draw(float x, float y){
    
    for(int i = 0; i < units.size(); i++ ){
        units[i].draw(x,y);     
    }
      
}
