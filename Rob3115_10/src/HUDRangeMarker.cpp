
#include "HUDRangeMarker.h"

//--------------------------------------------------------------
void HUDRangeMarker::setup(ofVec3f _rangeBound1, ofVec3f _rangeBound2, int _numIncrements, ofImage _img, float _imgWidth, float _imgHeight, ofColor _color, float _chanceToUpdate){

    rangeBound1 = _rangeBound1;
    rangeBound2 = _rangeBound2;
    numIncrements = _numIncrements;
    img = _img;
    imgWidth = _imgWidth;
    imgHeight = _imgHeight;
    color = _color;
    
    currentIncrement = (int)ofRandom(numIncrements);
//    cout << "CURRENTINCREMENT: " << currentIncrement << endl;
    
    chanceToUpdate = .01;
    
}

//--------------------------------------------------------------
void HUDRangeMarker::update(){
    
    if(ofRandom(1) < chanceToUpdate){
        float upOrDown = ofRandom(1);
        if (upOrDown <= 0.5 && currentIncrement != 0) {
            currentIncrement--;
        }
        if(upOrDown > 0.5 && currentIncrement != numIncrements){
            currentIncrement++;
        }
    }
    
    //update increment
//    currentIncrement = 0;
//    currentIncrement = numIncrements;
    
    //set markter to appropriate location based on currentIncrement
    curLocation.x = rangeBound1.x + ((float)currentIncrement/(float)numIncrements)*(rangeBound2.x-rangeBound1.x);
    curLocation.y = rangeBound1.y + ((float)currentIncrement/(float)numIncrements)*(rangeBound2.y-rangeBound1.y);
    curLocation.z = rangeBound1.z + ((float)currentIncrement/(float)numIncrements)*(rangeBound2.z-rangeBound1.z);
}

//--------------------------------------------------------------
void HUDRangeMarker::draw(){
    
    ofPushStyle();
    ofSetColor(color);
    img.draw(curLocation.x-imgWidth/2, curLocation.y-imgHeight/2, imgWidth, imgHeight);
    
    //Test Range Line
//    ofLine(rangeBound1.x, rangeBound1.y, rangeBound2.x, rangeBound2.y); //imgWidth/2 to account for ofSet of center of img
    
    ofPopStyle();

}