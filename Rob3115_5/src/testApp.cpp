#include "testApp.h"

/* -- ROB3115 - A Neuro Immersive Narrative ------------------------------------------/
 
 System Modes:
 0 = Intro Screen (sequence)
 1 = Connecting to Device
 2 = Mini-game Splash Screen
 3 = Story (Series of Chapters and Pages)
 4 = Close Sequence
 
 */

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetFrameRate(60);
    ofEnableAlphaBlending();
    ofSetFullscreen(TRUE);
    
    cout << "hello world." << endl;
    
    mode = 0;
    font1.loadFont("font/venus_rising.ttf", 12);
    connectText = false;
    
    number = 1;
    intro.loadImage("Intro_slide"+ofToString(number)+".png");
    
    story.setup();
//    minigame.setup();
    
    chapterAttValue = 0.0;
    blink = 0;
    
}

//--------------------------------------------------------------
void testApp::update(){
    
//    cout << "MODE: " << mode << endl;
    
    //TEST MODE---------------------
    if(mode==100){
        story.update();
        
    }
    //END TEST MODE-----------------
    
    
    if(mode==3){
        
        story.update();
        
        blink = eeg.updateNew(); // 1 = single 2 = double  ... each time EEG updates determines if there is a single or double blink to be sent to story.turnPage
        cout << "BLINK: " << blink << endl;
        chapterAttValue = eeg.getChapterAttention();
        story.turnPage(blink, chapterAttValue);
//        blink = 0;
    
    }
    
    if(mode==2){
        
//        minigame.update();
        
        minigame.update();
        if(minigame.textDone){
            blink = eeg.updateNew(); // 1 = single 2 = double
            cout << "BLINK: " << blink << endl;
            if(blink==2){
                mode = 3;
//                blink = 0;
            }
        }
    }
    
    
    if(mode==1 && connectText==true){
        bool connection;
        connection = eeg.setup(deviceNumber);
        
        if (connection==true) {
            minigame.setup();
            mode=2;
            
            
        }
        else{
            mode = 0;
            
            cout << "Try Again" << endl;
            font1.drawString("Try Again", 100, 100);
            connectText = false;
        }
        
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    //TEST MODE----------------------
    if(mode == 100){
        story.draw(blink);
        blink = 0;
        
    }
    //END TEST MODE------------------
    
    if(mode==3){
        story.draw(blink);
        eeg.draw();
        blink = 0; //reset for new reading in next frame (to be read in update as well)
    }
    
    if(mode==2){
        minigame.draw();
        eeg.draw();
        blink = 0;
    }
    
    if(mode==1){
        ofPushStyle();
        ofSetColor(255,255,255);
//        ofRect(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
        ofRect(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
        ofSetColor(0, 0, 0);
        font1.drawString("Connecting to Device", 100, 100);
        ofPopStyle();
        connectText = true;
    }
    
    if(mode==0){
//        intro.draw(0,0, ofGetScreenWidth(), ofGetScreenHeight());
        intro.draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
    }
    
    ofSetWindowTitle("fps = " + ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    if(mode == 100){
        if(key==' '){
            chapterAttValue = eeg.getChapterAttention();
            story.turnPage(blink, chapterAttValue);
        }
        
    }
    
    if(mode==3){
        if(key==' '){
            
            blink = 1;
            chapterAttValue = eeg.getChapterAttention();
            story.turnPage(blink, chapterAttValue);
            blink = 0;
        }
        
    }
    
    if(mode>1){
        if(key=='g'){
            eeg.graphOn = !eeg.graphOn;
        }
    }
    
    if(mode == 0){  //connect without EEG
        minigame.setup();
        mode = 100;
        
    }
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
    if(mode==100){
        
        minigame.randomizeQuote();
    }
    
    if(mode==3){
        story.turnPage(2, chapterAttValue);
    }
    
    if(mode==2){
        mode=3;
        
    }
    
    if(mode==0){
        if(mouseX>=0.6*ofGetWindowWidth() && mouseX <= 0.95*ofGetWindowWidth() && mouseY >= 0.45*ofGetWindowHeight() && mouseY <= 0.6*ofGetWindowHeight()){ //select Mindwave Mobile on intro screen
            mode=1;
            deviceNumber = 1;
        }
        if(mouseX>=0.6*ofGetWindowWidth() && mouseX <= 0.95*ofGetWindowWidth() && mouseY >= 0.625*ofGetWindowHeight() && mouseY <= 0.775*ofGetWindowHeight()){ //select Mindset on intro screen
            mode=1;
            deviceNumber = 2;
        }
        if(mouseX>=0.6*ofGetWindowWidth() && mouseX <= 0.95*ofGetWindowWidth() && mouseY >= 0.8*ofGetWindowHeight() &&mouseY <= 0.95*ofGetWindowHeight()){ //select Mindband
            mode=1;
            deviceNumber = 3;
        }
    }
    cout << "XXXXXXXXXXXXXXXXX mouseX: " << mouseX << " || mouseY: " << mouseY << endl;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}