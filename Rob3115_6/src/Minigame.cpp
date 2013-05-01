//
//  Page.cpp
//  neuroStory
//
//  Created by Conor Russomanno on 3/20/13.
//
//

#include "Minigame.h"

void Minigame::setup(){
    
    bg.loadImage("minigame_bg.png");
    font.loadFont("font/venus_rising.ttf", 12);
    
    ofxTextBlock temp;
    
    temp.init("font/venus_rising.ttf", 16);
    temp.setText("\"Deep in the human unconscious is a pervasive need for a logical universe that makes sense. But the real universe is always one step beyond logic.\" \n - Frank Herbert, Dune");
    temp.wrapTextX(ofGetWindowWidth()/2);
//    temp.wrapTextArea(ofGetWindowWidth()/2, ofGetWindowHeight()/2);
    quotes.push_back(temp);
    
    temp.setText("\"...It is when we act freely, for the sake of the action itself rather than for ulterior motives, that we learn to become more than what we were.\" \n - Mihaly Csikszentmihalyi, Flow");
    temp.wrapTextX(ofGetWindowWidth()/2);
//    temp.wrapTextArea(ofGetWindowWidth()/2, ofGetWindowHeight()/2);
    quotes.push_back(temp);
    
    temp.setText("\"Without change something sleeps inside us, and seldom awakens. The sleeper must awaken.\" \n - Frank Herbert, Dune");
    temp.wrapTextX(ofGetWindowWidth()/2);
//    temp.wrapTextArea(ofGetWindowWidth()/2, ofGetWindowHeight()/2);
    quotes.push_back(temp);
    

    randomQuote = (int)ofRandom(quotes.size());
                     cout << randomQuote << endl;
    
    wordNumber = 0;
    timeOfLastWord = ofGetElapsedTimeMillis();
    timeTilNextWord = 40 + ofRandom(-30,30);
                     
                     
                     
}

//--------------------------------------------------------------
void Minigame::update(){
    
    if(ofGetElapsedTimeMillis()-timeTilNextWord >= timeOfLastWord){
        wordNumber++;
        timeOfLastWord = ofGetElapsedTimeMillis();
        timeTilNextWord = 40 + ofRandom(-30,30);
    }
    
    if (wordNumber == quotes[randomQuote].words.size()){
        textDone = true;
    }
}

//--------------------------------------------------------------
void Minigame::draw(){
    
    bg.draw(0,0,ofGetScreenWidth(), ofGetScreenHeight());
    
    ofPushStyle();
    ofSetColor(0, 0, 0);
    ofRect(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
    ofPopStyle();
    
    cout << "Random Quote: " << randomQuote << endl;
    cout << quotes[randomQuote].rawText << endl;
    quotes[randomQuote].setColor(255, 255, 255, 255);
    cout << "word1_color: " << quotes[randomQuote].words[0].color << endl;
    
    cout << "----------------" << endl;
    cout << "# of Lines: " << quotes[randomQuote].lines.size() << endl;
    quotes[randomQuote].drawLeftAndType(ofGetWindowWidth()/8, ofGetWindowHeight()/8, wordNumber);
    cout << "----------------" << endl;
    
}

void Minigame::randomizeQuote(){
    randomQuote = (int)ofRandom(quotes.size());
}