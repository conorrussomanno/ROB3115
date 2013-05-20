//
//  Page.cpp
//  neuroStory
//
//  Created by Conor Russomanno on 3/20/13.
//
//

#include "Page.h"

void Page::setup(string _text, ofImage _img){
    //setup textbox with values passed through setup
    text = _text;
    img = _img;
    
    textBlock.init("font/Orbitron_Light.ttf", (20.0/1680)*ofGetWidth());
    textBlock.setText(text);
    textBlock.wrapTextX((0.6)*ofGetWindowWidth());
    
    wordNumber = 0;
    timeOfLastWord = ofGetElapsedTimeMillis();
    timeTilNextWord = 40 + ofRandom(-30,30);
    
    textDone = false;
    
}

//--------------------------------------------------------------
void Page::update(){
    
    if(ofGetElapsedTimeMillis()-timeTilNextWord >= timeOfLastWord){
        wordNumber++;
        timeOfLastWord = ofGetElapsedTimeMillis();
        timeTilNextWord = 40; + ofRandom(-30,30);
    }
    
    if (wordNumber == textBlock.words.size()){
        textDone = true;
    }
    
}

//--------------------------------------------------------------
void Page::draw(){
    
    img.draw(0,0,ofGetWindowWidth(), ofGetWindowHeight());
    textBlock.drawLeftAndType((0.16)*ofGetWindowWidth(), (0.86) * ofGetWindowHeight(), wordNumber);
    
    //draw textbox
    
}