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
    ofColor c5(14,110,198);
    
    spinner5.setup(15 /*count*/, 0 /*avgRotSpd*/, 140 /*rotVariation*/, c5 /*color*/, 40 /*resolution*/, 22 /*minRad*/, 110 /*maxRad*/, 10 /*minWidth*/, 40 /*maxWidth*/);
    
    HUDimg.loadImage("HUD_AGUS_3.png");
    
    for (int i = 0; i < 4; i++){
        HUDUnit tempy;
        tempy.setup(10 /*rotSpeed*/, c5 /*color*/, 40 /*numSeg*/, 0.25 *i /*startSweep*/, .125 /*sweep (0-1)*/, 90 /*innerRad*/, 93/*outerRad*/);
        unit1_1.push_back(tempy);
    }
    
    for (int i = 0; i < 4; i++){
        HUDUnit tempy;
        tempy.setup(-15 /*rotSpeed*/, c5 /*color*/, 40 /*numSeg*/, 0.25*i + .125 /*startSweep*/, .15 /*sweep (0-1)*/, 105 /*innerRad*/, 109/*outerRad*/);
        unit1_2.push_back(tempy);
    }
    
    for (int i = 0; i < 4; i++){
        HUDUnit tempy;
        tempy.setup(10 /*rotSpeed*/, c5 /*color*/, 40 /*numSeg*/, 0.25*i + ofRandom(-.03,.03) /*startSweep*/, ofRandom(.125, .22) /*sweep (0-1)*/, 51 /*innerRad*/, 54/*outerRad*/);
        unit2_1.push_back(tempy);
    }
    
    for (int i = 0; i < 4; i++){
        HUDUnit tempy;
        tempy.setup(-15 /*rotSpeed*/, c5 /*color*/, 40 /*numSeg*/, 0.25*i + ofRandom(-.03,.03) /*startSweep*/, ofRandom(.125, .22) /*sweep (0-1)*/, 65 /*innerRad*/, 69/*outerRad*/);
        unit2_2.push_back(tempy);
    }
    
    stepGraph1.setup(100/*maxBlocks*/, 50/*graphWidth*/, 530/*graphHeight*/, 4/*distBetBlocks*/, c5/*color*/, (0.019)*ofGetWindowWidth()/*xLoc*/, (0.768) *ofGetWindowHeight() /*yLoc*/);
    
    singleBlink = false;
    doubleBlink = false;

}

//--------------------------------------------------------------
void HUD::update(float _currentAttValue, float _currentSignalQuality){
    
    spinner5.update(_currentAttValue, _currentSignalQuality);
    stepGraph1.update(_currentAttValue, _currentSignalQuality);

}

//--------------------------------------------------------------
void HUD::draw(int _blink){
    
    cout << "------------BLINK--------------" << _blink << endl;
    
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
        ofEllipse((0.128)*ofGetWindowWidth(), (.7045)*ofGetWindowHeight(), 103, 103);
        ofPopStyle();
        unit2_1[i].draw((.128)*ofGetWindowWidth(), (.7045) * ofGetWindowHeight());
    }
    for (int i = 0; i < unit2_2.size(); i++){
        ofPushStyle();
        ofSetColor(8,66,118);
        ofNoFill();
        ofEllipse((0.128)*ofGetWindowWidth(), (.7045)*ofGetWindowHeight(), 131, 131);
        ofPopStyle();
        unit2_2[i].draw((.128)*ofGetWindowWidth(), (.7045) * ofGetWindowHeight());
    }
    
    stepGraph1.draw();
    
    
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
