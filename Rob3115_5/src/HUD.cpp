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
    ofColor c(36,96,150);
    ofColor c2(36,180,150);
    ofColor c3(93,5,255);
    ofColor c4(254,173,69);
    ofColor c5(5,209,245);
    ofColor c6(40,240,60);
    
    spinner1.setup(10 /*count*/, 200.0 /*avgRotSpd*/, 100 /*rotVariation*/, c /*color*/, 30 /*resolution*/, 20 /*minRad*/, 55 /*maxRad*/, 15 /*minWidth*/, 30 /*maxWidth*/);
    spinner2.setup(10 /*count*/, 150 /*avgRotSpd*/, 50 /*rotVariation*/, c2 /*color*/, 40 /*resolution*/, 15 /*minRad*/, 55 /*maxRad*/, 10 /*minWidth*/, 20 /*maxWidth*/);
    spinner3.setup(15 /*count*/, 150 /*avgRotSpd*/, 140 /*rotVariation*/, c3 /*color*/, 40 /*resolution*/, 20 /*minRad*/, 55 /*maxRad*/, 10 /*minWidth*/, 20 /*maxWidth*/);
    spinner4.setup(15 /*count*/, 150 /*avgRotSpd*/, 140 /*rotVariation*/, c4 /*color*/, 40 /*resolution*/, 30 /*minRad*/, 55 /*maxRad*/, 10 /*minWidth*/, 20 /*maxWidth*/);
    spinner5.setup(20 /*count*/, 150 /*avgRotSpd*/, 140 /*rotVariation*/, c5 /*color*/, 40 /*resolution*/, 20 /*minRad*/, 80 /*maxRad*/, 10 /*minWidth*/, 20 /*maxWidth*/);
    spinner6.setup(15 /*count*/, -150 /*avgRotSpd*/, 100 /*rotVariation*/, c6 /*color*/, 40 /*resolution*/, 30 /*minRad*/, 200 /*maxRad*/, 20 /*minWidth*/, 100 /*maxWidth*/);
    
    HUDimg.loadImage("HUD3.png");
    
    singleBlink = false;
    doubleBlink = false;

}

//--------------------------------------------------------------
void HUD::update(){

}

//--------------------------------------------------------------
void HUD::draw(int _blink){
    
    cout << "------------BLINK--------------" << _blink << endl;
    
    HUDimg.draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
    
    spinner1.draw((0.952)*ofGetWindowWidth(),(0.217)*ofGetWindowHeight());
    spinner2.draw((0.952)*ofGetWindowWidth(),(0.358)*ofGetWindowHeight());
    spinner3.draw((0.952)*ofGetWindowWidth(),(0.495)*ofGetWindowHeight());
    spinner4.draw((0.952)*ofGetWindowWidth(),(0.638)*ofGetWindowHeight());
    spinner5.draw((0.053)*ofGetWindowWidth(),(0.103)*ofGetWindowHeight());
//    spinner6.draw(ofGetWindowWidth()/2,ofGetWindowHeight()/2);.
    
    //Trigger HUD Light Indicating a blink has been recorded...
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
