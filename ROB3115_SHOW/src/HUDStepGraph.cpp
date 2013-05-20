#include "HUDStepGraph.h"

//--------------------------------------------------------------
void HUDStepGraph::setup(float _maxBlocks, float _graphWidth, float _graphHeight, float _distBetweenBlocks, ofColor _blockColor, float _xLocation, float _yLocation){
    
    maxBlocks = _maxBlocks;
    graphWidth = _graphWidth;
    graphHeight = _graphHeight;
    distBetweenBlocks = _distBetweenBlocks;
    blockColor = _blockColor;
    
    xLocation = _xLocation;
    yLocation = _yLocation;
    
    cout << "YLOCATION" << yLocation << endl;
    cout << "Window Height: " << ofGetWindowHeight() << endl;
    
    blockWidth = graphWidth;
    blockHeight = (graphHeight - ((maxBlocks-1.0)*distBetweenBlocks)) / (maxBlocks);
    
    currentBlockCount = maxBlocks;
    
    previousBlockCount = 0.0;
    currentBlockCount = 0.0;
    nextBlockCount = 0.0;
    
    previousSignalQuality = 0.0;
    changeTime = 0;
    

}

//--------------------------------------------------------------
void HUDStepGraph::update(float _currentAttValue, float _currentSignalQuality){
    currentSignalQuality = _currentSignalQuality;
    float cur = ofGetElapsedTimef();
    float progress = cur - changeTime;
    currentBlockCount = ofxTweenLite::tween(previousBlockCount, nextBlockCount, progress, OF_EASE_SINE_INOUT);
    
    if(currentSignalQuality != previousSignalQuality){
        previousSignalQuality = currentSignalQuality;
        previousBlockCount = nextBlockCount;
        nextBlockCount = ofMap(currentSignalQuality, 0, 100, 0, maxBlocks);
        changeTime = ofGetElapsedTimef();
    }
    
//    cout << "CURRENT SIGNAL QUALITY: " << _currentSignalQuality << endl;
    
//    currentBlockCount = maxBlocks * (_currentSignalQuality/100);
//    currentBlockCount = maxBlocks * (float)(_currentSignalQuality/100);
//    blockColor = (blockColor.r, blockColor.g, blockColor.b, (75/100));
    
}

//--------------------------------------------------------------
void HUDStepGraph::draw(){
    
//    cout << "currentBlockCount" << currentBlockCount << endl;
//    cout << "Window Height" << ofGetWindowHeight() << endl;
    
    
    ofPushStyle();
    if (currentBlockCount != maxBlocks) { //turn graph red to indicate bad signal
        ofSetColor(99, 42, 42);
    }
    else{
        ofSetColor(blockColor);
    }
    for(int i = 0; i < currentBlockCount; i++){
        ofRect(xLocation, yLocation + distBetweenBlocks - (blockHeight+distBetweenBlocks)*((float)i+1.0), blockWidth, blockHeight);
    }
    ofPopStyle();
    
}
