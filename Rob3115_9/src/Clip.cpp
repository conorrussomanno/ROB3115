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
    
    waitTime = _waitTime;
    requiresClick = _requiresClick;
    speaker = _speaker;
    
    if (speaker == 0) { //SYSTEM
        textColor.set(125, 125, 125);
    }
    if (speaker == 1) { //ALPHA
        textColor.set(200, 60, 30);
    }
    if (speaker == 2) { //ROB
        textColor.set(30, 60, 200);
    }
    
    textBlock.init("font/Orbitron_Light.ttf", (20.0/1680)*ofGetWidth());
    textBlock.setText(text);
    textBlock.wrapTextX((0.6)*ofGetWindowWidth());
    
    wordNumber = 0;
    timeOfLastWord = ofGetElapsedTimeMillis();
    timeTilNextWord = 40 + ofRandom(-30,30);
    
    textFinished = false;
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
    cout << "textcolor: " << textColor << endl;
    ofSetColor(textColor);
    if (speaker == 0) { //SYSTEM
        ofSetColor(75, 75, 75);
    }
    if (speaker == 1) { //ALPHA
        ofSetColor(200, 60, 30);
    }
    if (speaker == 2) { //ROB
        ofSetColor(30, 60, 200);
    }
    textBlock.drawLeftAndType((0.16)*ofGetWindowWidth(), (0.86) * ofGetWindowHeight(), wordNumber);
    ofPopStyle();

}

//--------------------------------------------------------------
void Clip::alphaBlink(){
    
    
}