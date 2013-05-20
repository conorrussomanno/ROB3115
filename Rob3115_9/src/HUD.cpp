//
//  Page.cpp
//  neuroStory
//
//  Created by Conor Russomanno on 3/20/13.
//
//

#include "HUD.h"

void HUD::setup(){
    
    //Colors for HUDSpinners below
    ofColor c5(12,60,104);
    ofColor stepGraphColor(39,39,34);
    
    spinner5.setup(15 /*count*/, 0 /*avgRotSpd*/, 3 /*rotVariation*/, c5 /*color*/, 40 /*resolution*/, (22.0/1280.0)*ofGetWidth() /*minRad*/, (85.0/1280.0) * ofGetWidth() /*maxRad*/, (7.0/1280)*ofGetWidth() /*minWidth*/, (30.0/1280.0)*ofGetWidth() /*maxWidth*/, false);
    
    HUDimg.loadImage("HUD_AGUS_3.png");
    
    
    //Lower Right Inner
    for (int i = 0; i < 3; i++){
        HUDUnit tempy;
        tempy.setup(.5 /*rotSpeed*/, c5 /*color*/, 40 /*numSeg*/, .333 *i /*startSweep*/, .1 /*sweep (0-1)*/, (90.0/1680)*ofGetWidth() /*innerRad*/, (93.0/1680)*ofGetWidth()/*outerRad*/, true /*hasTail*/);
        unit1_1.push_back(tempy);
    }
    
    //Lower RIght Outer
    for (int i = 0; i < 4; i++){
        HUDUnit tempy;
        tempy.setup(-.7 /*rotSpeed*/, c5 /*color*/, 40 /*numSeg*/, 0.25*i + .125 /*startSweep*/, .1 /*sweep (0-1)*/, (105.0/1680)*ofGetWidth() /*innerRad*/, (109.0/1680)*ofGetWidth()/*outerRad*/, true/*hasTail*/);
        unit1_2.push_back(tempy);
    }
    
    //Left inner
    for (int i = 0; i < 4; i++){
        HUDUnit tempy;
        tempy.setup(.5 /*rotSpeed*/, c5 /*color*/, 40 /*numSeg*/, 0.25*i + ofRandom(-.03,.03) /*startSweep*/, ofRandom(.06, .08) /*sweep (0-1)*/, (51.0/1680)*ofGetWidth() /*innerRad*/, (54.0/1680)*ofGetWidth()/*outerRad*/, true/*hasTail*/);
        unit2_1.push_back(tempy);
    }
    
    //Left Outer
    for (int i = 0; i < 4; i++){
        HUDUnit tempy;
        tempy.setup(-.5 /*rotSpeed*/, c5 /*color*/, 40 /*numSeg*/, 0.25*i + ofRandom(-.03,.03) /*startSweep*/, ofRandom(.07, .1) /*sweep (0-1)*/, (65.0/1680)*ofGetWidth() /*innerRad*/, (69.0/1680)*ofGetWidth()/*outerRad*/, true/*hasTail*/);
        unit2_2.push_back(tempy);
    }
    
    //Setup of Signal Quality Graph on Left of Screen
    stepGraph1.setup(100/*maxBlocks*/, (38.0/1280.0)*ofGetWidth()/*graphWidth*/, (388.0/768.0)*ofGetHeight()/*graphHeight*/, (2.5/1280.0)*ofGetWidth()/*distBetBlocks*/, stepGraphColor/*color*/, (0.019)*ofGetWindowWidth()/*xLoc*/, (0.768) *ofGetWindowHeight() /*yLoc*/);
    
    
    //Setup of ticker beneath central graph on right
    rangeMarker1Img.loadImage("RangeMarker_North.png");
    rangeMarker1Color.set(100, 102, 90);
    ofVec3f v1((.9123)*ofGetWindowWidth(), (.6125)*ofGetWindowHeight(), 0);
    ofVec3f v2((.9773)*ofGetWindowWidth(), (.6125)*ofGetWindowHeight(), 0);
    rangeMarker1.setup(v1/*VEC3,rangeBound1*/, v2/*VEC3,rangeBound2*/, 10/*numIncrements*/, rangeMarker1Img/*img*/, (10.0/1680)*ofGetWidth()/*imgW*/, (12.0/1660)*ofGetWidth()/*imgH*/, rangeMarker1Color/*color*/, .005/*chanceToUpdate(0-1)*/);
    
    // Setup of ticker to the left of graph on top
    rangeMarker2Img.loadImage("RangeMarker_East.png");
    rangeMarker2Color.set(100, 102, 90);
    ofVec3f v3((1040.0/1280.0)*ofGetWindowWidth(), (11.5/768.0)*ofGetWindowHeight(), 0);
    ofVec3f v4((1040.0/1280.0)*ofGetWindowWidth(), (76.0/768.0)*ofGetWindowHeight(), 0);
    rangeMarker2.setup(v3/*VEC3,rangeBound1*/, v4/*VEC3,rangeBound2*/, 10/*numIncrements*/, rangeMarker2Img/*img*/, (12.0/1680)*ofGetWidth()/*imgW*/, (8.0/1660)*ofGetWidth()/*imgH*/, rangeMarker2Color/*color*/, .005/*chanceToUpdate(0-1)*/);
    
    // Setup array of tickers in graph on right
    markerGraphImg.loadImage("RangeMarker_RectVert.png");
    markerGraphColor.set(100, 102, 90);
    for(int i = 0; i < 15; i++){
        HUDRangeMarker temp;
        ofVec3f v5((1168.5/1280.0)*ofGetWindowWidth()+((7.8/1680.0)*ofGetWidth())*(float)i, (300.0/768.0)*ofGetWindowHeight(), 0);
        ofVec3f v6((1168.5/1280.0)*ofGetWindowWidth()+((7.8/1680.0)*ofGetWidth())*(float)i, (322.0/768.0)*ofGetWindowHeight(), 0);
        temp.setup(v5/*VEC3,rangeBound1*/, v6/*VEC3,rangeBound2*/, 6/*numIncrements*/, markerGraphImg/*img*/, (3.0/1680)*ofGetWidth()/*imgW*/, (7.0/1680)*ofGetWidth()/*imgH*/, markerGraphColor/*color*/, 0.001*i /*chanceToUpdate(0-1)*/);
        markerGraph.push_back(temp);
    }
    
    
    singleBlink = false;
    doubleBlink = false;

}

//--------------------------------------------------------------
void HUD::update(float _currentAttValue, float _currentSignalQuality){
    
    spinner5.update(_currentAttValue, _currentSignalQuality);
    for (int i = 0; i < unit1_1.size(); i++){
        unit1_1[i].update(_currentSignalQuality);
    }
    for (int i = 0; i < unit1_2.size(); i++){
        unit1_2[i].update(_currentSignalQuality);
    }
    for (int i = 0; i < unit2_1.size(); i++){
        unit2_1[i].update(_currentSignalQuality);
    }
    for (int i = 0; i < unit2_2.size(); i++){
        unit2_2[i].update(_currentSignalQuality);
    }
    stepGraph1.update(_currentAttValue, _currentSignalQuality);
    rangeMarker1.update();
    rangeMarker2.update();
    for (int i = 0; i < markerGraph.size(); i++) {
        markerGraph[i].update();
    }

}

//--------------------------------------------------------------
void HUD::draw(int _blink){
    
//    cout << "------------BLINK--------------" << _blink << endl;
    
    HUDimg.draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
    
    //Attention Spinner (TOP LEFT of HUD)
    spinner5.draw((0.080)*ofGetWindowWidth(),(0.126)*ofGetWindowHeight());
    
    //inner ring of bottom right animation around globe
    for (int i = 0; i < unit1_1.size(); i++){
        unit1_1[i].draw((.9109)*ofGetWindowWidth(), (.865) * ofGetWindowHeight());
    }
    //outer ring
    for (int i = 0; i < unit1_2.size(); i++){
        unit1_2[i].draw((.9109)*ofGetWindowWidth(), (.865) * ofGetWindowHeight());
    }
    
    for (int i = 0; i < unit2_1.size(); i++){
        ofPushStyle();
        ofSetColor(8,66,118);
        ofNoFill();
        ofEllipse((0.128)*ofGetWindowWidth(), (.7045)*ofGetWindowHeight(), (103.0/1680)*ofGetWidth(), (103.0/1680)*ofGetWidth());
        ofPopStyle();
        unit2_1[i].draw((.128)*ofGetWindowWidth(), (.7045) * ofGetWindowHeight());
    }
    for (int i = 0; i < unit2_2.size(); i++){
        ofPushStyle();
        ofSetColor(8,66,118);
        ofNoFill();
        ofEllipse((0.128)*ofGetWindowWidth(), (.7045)*ofGetWindowHeight(), (131.0/1680)*ofGetWidth(), (131.0/1680)*ofGetWidth());
        ofPopStyle();
        unit2_2[i].draw((.128)*ofGetWindowWidth(), (.7045) * ofGetWindowHeight());
    }
    
    
    //draw range Markers
    stepGraph1.draw();
    
    rangeMarker1.draw();
    rangeMarker2.draw();
    for (int i = 0; i < markerGraph.size(); i++) {
        markerGraph[i].draw();
    }
    
    
//Trigger HUD Light Indicating a blink has been recorded...
    
//    unit1_1.draw((.9109)*ofGetWindowWidth(), (.865) * ofGetWindowHeight());
    
    if (_blink == 1){
        singleBlink = true;
        singleTriggerTime = ofGetElapsedTimeMillis();
        cout << "TRIGGER1" << endl;
    }
    if (_blink == 2 && singleBlink == true){
        doubleBlink = true;
        doubleTriggerTime = ofGetElapsedTimeMillis();
    }
    
    if (singleBlink) {
        activateSingle();
    }
    
    if (doubleBlink) {
        activateDouble();
    }
    
    
}

void HUD::activateSingle(){
    if(ofGetElapsedTimeMillis()-singleTriggerTime < 1000){
        ofPushStyle();
        ofSetColor(40,240,60, 125);
        ofRect((0.033)*ofGetWindowWidth(),(0.860)*ofGetWindowHeight(), (0.052)*ofGetWindowWidth(), (0.083)*ofGetWindowHeight());
        ofPopStyle();
    }
    else{
        singleBlink = false;
    }
    
}

void HUD::activateDouble(){
    if(ofGetElapsedTimeMillis()-doubleTriggerTime < 1000){
        ofPushStyle();
        ofSetColor(40,240,60, 255);
        ofRect((0.033)*ofGetWindowWidth(),(0.860)*ofGetWindowHeight(), (0.052)*ofGetWindowWidth(), (0.083)*ofGetWindowHeight());
        ofPopStyle();
    }
    else{
        doubleBlink = false;
    }
}
