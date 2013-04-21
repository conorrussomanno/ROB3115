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
    
    temp.init("font/venus_rising.ttf", 12);
    temp.setText("'Deep in the human unconscious is a pervasive need for a logical universe that makes sense. But the real universe is always one step beyond logic.'― Frank Herbert, Dune");
    quotes.push_back(temp);
    
    temp.setText("'...It is when we act freely, for the sake of the action itself rather than for ulterior motives, that we learn to become more than what we were.'― Mihaly Csikszentmihalyi, Flow");
    quotes.push_back(temp);
    
    temp.setText("'Without change something sleeps inside us, and seldom awakens. The sleeper must awaken.'― Frank Herbert, Dune");
    quotes.push_back(temp);
    

    randomQuote = (int)ofRandom(quotes.size());
                     cout << randomQuote << endl;
                     
                     
                     
}

//--------------------------------------------------------------
void Minigame::update(){
    
}

//--------------------------------------------------------------
void Minigame::draw(){
    
    bg.draw(0,0,ofGetScreenWidth(), ofGetScreenHeight());
    
    ofPushStyle();
    ofSetColor(125, 125, 125);
    ofRect(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
    ofPopStyle();
    
    cout << "Random Quote: " << randomQuote << endl;
    cout << quotes[randomQuote].rawText << endl;
    quotes[randomQuote].draw(0,0);
    
}