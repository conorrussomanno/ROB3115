//
//  Clip.cpp
//  Rob3115
//
//  Created by Conor Russomanno on 5/7/13.
//
//

#include "Clip.h"

void Clip::setup(string _text, bool _requiresClick, float _waitTime, int _speaker){
    
    text = _text;
    
    isDebugClip = false;
    isAlertClip = false;
    isBugFoundClip = false;
    isAlphaMoveClip = false;
    
    waitTime = _waitTime;
    requiresClick = _requiresClick;
    speaker = _speaker;
    
    if (speaker == 0) { //SYSTEM
        textColor.set(128, 128, 128);
    }
    if (speaker == 1) { //ALPHA
        textColor.set(143, 0, 0);
    }
    if (speaker == 2) { //ROB
        textColor.set(14, 94, 179);
    }
    
    textBlock.init("font/Orbitron_Light.ttf", (18.0/1680)*ofGetWidth());
    textBlock.setText(text);
    textBlock.wrapTextX((0.6)*ofGetWindowWidth());
    
    wordNumber = 0;
    timeOfLastWord = ofGetElapsedTimeMillis();
    timeTilNextWord = 40 + ofRandom(-30,30);
    
    textFinished = false;
    
    if (speaker == 1){
        eyes.loadImage("alpha_eyes.png");
    }
}

void Clip::setup(string _text, bool _requiresClick, float _waitTime, int _speaker, int _animationClip){
    
    text = _text;
    
    waitTime = _waitTime;
    requiresClick = _requiresClick;
    speaker = _speaker;
    
    isDebugClip = false;
    isAlertClip = false;
    isBugFoundClip = false;
    isAlphaMoveClip = false;
    
    if(_animationClip == 1){
        isDebugClip = true;
    }
    if(_animationClip == 2){
        isAlertClip = true;
    }
    if(_animationClip == 3){
        isBugFoundClip = true;
    }
    if(_animationClip == 4){
        isAlertClip = true;
        isAlphaMoveClip = true;
    }
    if(_animationClip == 5){
        isBugFoundClip = true;
        isAlphaMoveClip = true;
    }
    
    
    if (speaker == 0) { //SYSTEM
        textColor.set(125, 125, 125);
    }
    if (speaker == 1) { //ALPHA
        textColor.set(200, 60, 30);
    }
    if (speaker == 2) { //ROB
        textColor.set(30, 60, 200);
    }
    
    textBlock.init("font/Orbitron_Light.ttf", (18.0/1680)*ofGetWidth());
    textBlock.setText(text);
    textBlock.wrapTextX((0.6)*ofGetWindowWidth());
    
    wordNumber = 0;
    timeOfLastWord = ofGetElapsedTimeMillis();
    timeTilNextWord = 40 + ofRandom(-30,30);
    
    textFinished = false;
    
    if (_speaker == 1){
        eyes.loadImage("alpha_eyes.png");
    }
}

//--------------------------------------------------------------
void Clip::update(){
    
    if(ofGetElapsedTimeMillis()-timeTilNextWord >= timeOfLastWord){
        wordNumber++;
        timeOfLastWord = ofGetElapsedTimeMillis();
        timeTilNextWord = 40; + ofRandom(-30,30);
    }
    
    if (wordNumber == textBlock.words.size()){
        textFinished = true;
    }
}

//--------------------------------------------------------------
void Clip::draw(){
    
    ofPushStyle();
//    cout << "textcolor: " << textColor << endl;
    ofSetColor(textColor);
    if (speaker == 0) { //SYSTEM
        ofSetColor(128, 128, 128);
    }
    if (speaker == 1) { //ALPHA
        ofSetColor(143, 30, 30);
    }
    if (speaker == 2) { //ROB
        ofSetColor(14, 94, 179);
    }
    textBlock.drawLeftAndType((0.16)*ofGetWindowWidth(), (0.86) * ofGetWindowHeight(), wordNumber);
    ofPopStyle();
    
    if(speaker == 1 && textFinished != true){
        ofPushStyle();
        ofSetColor(143, 0, 0);
        eyes.draw(0,0, ofGetWidth(), ofGetHeight());
        ofPopStyle();
    }

}

//--------------------------------------------------------------
void Clip::alphaBlink(){
    
    
}