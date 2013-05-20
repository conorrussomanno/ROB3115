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
    
    ofSetFrameRate(30);
    ofEnableAlphaBlending();
    ofSetFullscreen(TRUE);
    ofSetVerticalSync(TRUE);
    ofSetCircleResolution(200);
    ofEnableSmoothing();
    
    //cout << "hello world." << endl;
    
    mode = -2;

    font1.loadFont("font/Orbitron_Light.ttf", (18.0/1680)*ofGetWidth());
    connectText = false;
    
    appPicker.loadImage("background.jpg");
    

//    intro.loadImage("Intro_slide"+ofToString(number)+".png");
    intro.loadImage("MAIN.jpg");
    neuroSkyDevices.loadImage("NeuroSky.png");
    description.loadImage("description.jpg");
    tutorial.loadImage("tutorial.jpg");
    
        
    number = 1;
    
    storySetUp = false;
    
    chapterAttValue = 0.0;
    currentAttValue = 0.0;
    blink = 0;
    
    timeOfFadeIn = 3000;
    
    cursorHidden = false;
    

    
}

//--------------------------------------------------------------
void testApp::update(){
    
    if(mode > 1 && cursorHidden == false){
        ofHideCursor();
        cursorHidden = true;
    }
    
    if(ofGetFrameNum() > 3 && storySetUp == false){  //set story up after frame 3 to ensure full screen... can't switch screensize yet because graphics are setup based on screensize.
        //cout << "story setting up" << endl;
        //cout << ofGetElapsedTimeMillis() << endl;
        story.setup();
        storySetUp = true;

        
        //cout << "story finished setting up" << endl;
        //cout << ofGetElapsedTimeMillis() << endl;
    }
    
    //cout << "MODE: " << mode << endl;
    
    //TEST MODE---------------------
    if(mode==100){
        story.update(0,100);
        
    }
    //END TEST MODE-----------------
    
    
    if(mode==3){ //Story
        
        blink = eeg.updateNew(); // 1 = single 2 = double  ... each time EEG updates determines if there is a single or double blink to be sent to story.turnPage
        //cout << "BLINK: " << blink << endl;
        chapterAttValue = eeg.getChapterAttention();
        
//        //---For Testing Purposes---//
//        chapterAttValue = 40;
//        //--------------------------//
        
        if(eeg.attValues.size()>0){
            currentAttValue = eeg.attValues[eeg.attValues.size()];
        }
        currentSignalQuality = eeg.signalQuality;
        
        //cout << "Signal Quality TestApp: " << currentSignalQuality << endl;
        
        story.update(currentAttValue, currentSignalQuality);
        
//        story.update(currentAttValue, currentSignalQuality);
//        story.turnPage(blink, chapterAttValue); // turn on to activate BLINK TURN PAGE
//        story.turnPage(0, chapterAttValue);
//        blink = 0;
    
    }
    
    if(mode==2){ //Minigame
        
//        minigame.update();
        
        minigame.update();
        if(minigame.textDone){
            blink = eeg.updateNew(); // 1 = single 2 = double
            //cout << "BLINK: " << blink << endl;
            if(blink==2){
                mode = 3;
//                blink = 0;
            }
        }
    }
    
    if(mode == 15 || mode == 16){
        eeg.updateNew();
        chapterAttValue = eeg.getChapterAttention();
        currentSignalQuality = eeg.signalQuality;
        if(mode == 16){
            story.hud1.update(currentAttValue, currentSignalQuality);
        }
    }
    
    
    if(mode==1 && connectText==true){ //Connecting to EEG
        bool connection;
        
        try {
            connection = eeg.setup(deviceNumber);
//            throw false;
        } catch (bool _notSureHowToUseThis) {
            connection = false;
            //cout << "Failed Attempt... Trying Choosing Another Device or Restarting Your Current Device." << endl;
        }
//
//        connection = eeg.setup(deviceNumber);
        
        if (connection==true) {
            connection = false;
            connectText = false;
            minigame.setup();
            mode=15;
            
            
        }
        else{
            mode = 0;
            
            //cout << "Try Again" << endl;
            font1.drawString("Try Again", 100, 100);
            connectText = false;
        }
        
//        loadScreen.stopThread();
        
    }
    
//    //give slight delay before story setup to make application open more quickly... 
//    if(mode==0 && storySetUp==false && ofGetFrameNum() > 1){
//        
////    if(mode==0 && storySetUp==false){
//        //cout << "FRAME: " << ofGetFrameNum() << endl;
//        //cout << "ofGetWidth: " << ofGetWidth() << endl;
//        //cout << "ofGetWindowWidth: " << ofGetWindowWidth() << endl;
//        //cout << "screenWidth: " << ofGetScreenWidth() << endl;
//        
//        story.setup();
//        storySetUp = true;
//    }
    
    if(mode==-1){
        if(ofGetElapsedTimeMillis()-timeOfNegativeOne > timeOfFadeIn){
            mode = 0;
            timeOfZero = ofGetElapsedTimeMillis();
        }
        
    }
    
    if(mode==-2){
        if(storySetUp){
            mode = -1;
            timeOfNegativeOne = ofGetElapsedTimeMillis();
        }
//        if(ofGetFrameNum() > 3 && storySetUp == false){  //set story up after frame 3 to ensure full screen... can't switch screensize yet because graphics are setup based on screensize.
//            //cout << "story setting up" << endl;
//            //cout << ofGetElapsedTimeMillis() << endl;
//            story.setup();
//            storySetUp = true;
//            
//            //cout << "story finished setting up" << endl;
//            //cout << ofGetElapsedTimeMillis() << endl;
//        }
    }
    
    //-- WRITE TO TEXT FILE ---//
    if (eeg.chapValues.size()>0) {
        if(mode == 2 || mode == 15 || mode ==3){ //after EEG is setup and updating...
            if(ofGetFrameNum()%30 ==0){ //write to text file once per second
                myFile << ofGetElapsedTimeMillis() << ", " << deviceNumber << ", " << eeg.signalQuality << ", " << eeg.getStoryAttention()<< ", "<< eeg.getChapterAttention() << ", " << eeg.chapValues[eeg.chapValues.size()-1] << ", " << story.currentChapter << ", " << story.currentPage << ", " << story.currentTier << ", " << mode << endl;
            }
        }
    }
//-------------------------//
    
    //resets story if chpt3 is finished or if the application has been idle for 2 min...
    if(story.chpt3.exitRob==true || ((ofGetElapsedTimeMillis()-timeOfLastMouseRelease) > 120000 && mode > 1)){
        
        if (story.chpt3.exitRob==false) {
            myFile << "File closed due to inactivity..." << endl;
        }
        
        myFile.close();
        
        ofShowCursor();
        cursorHidden = false;
        
        eeg.attValues.clear();
        story.chpt3.clips.clear();
        eeg.chapValues.clear();


        story.segwayTier=0;
        
        eeg.thinkGear.TG_Disconnect(eeg.thinkGear.connectionID);
        story.currentChapter=0;
        story.currentTier=1;
        story.currentPage=0;
        
        story.chpt3.alphaAnimateStartTime = 0;
        story.chpt3.currentClip = 0;
        story.chpt3.alphaAnimateFactor = 1.0;
        story.chpt3.isFinished = false;
        story.chpt3.exitRob=false;
        
        mode = -2;
    }
    
}

//--------------------------------------------------------------
void testApp::draw(){
    
    if(mode==-8){
        if (firstPlaySeq == false){
            blur.draw();
            blur.begin();
            welcomescreen.draw(0.0, 0.0, ofGetWidth(), ofGetHeight());
            welcomescreen.play();
            blur.end();
        } else {
            if (attention < openThreshold) {
                blur.draw();
                blur.begin();
                welcomescreen.draw(0.0, 0.0, ofGetWidth(), ofGetHeight());
                welcomescreen.play();
                blur.end();
            }
        }
        if (incident == true && welcome == false && extreme == true){
            gameplay.draw(0.0, 0.0, ofGetWidth(), ofGetHeight());
            gameplay.play();
            float wave = sin(ofGetElapsedTimef());
            transparency.draw(ofGetWidth()/3 + (wave * 100), ofGetWidth()/3);
        }
        else if (incident == true && welcome == false){
            gameplay.draw(0.0, 0.0, ofGetWidth(), ofGetHeight());
            gameplay.play();
        }
        
        if (over == true && lastPlaySeq == false) {
            gameover.draw(0.0, 0.0, ofGetWidth(), ofGetHeight());
            gameover.play();
        }
        
        ofPushMatrix();
        ofTranslate(0, 30);
        ofPushStyle();
        ofSetColor(ofColor::yellow);
        font.drawString("Attention", 10, ofGetHeight()/15 - 20);
        ofFill();
        ofRect(10, ofGetHeight()/20-10, currAw/10, 10);
        
        if (attention > 0.0)
        {
            ofSetColor(ofColor::yellow, ofMap(currAw, 0.0, ofGetWidth()/2, 50, 100));
            font.drawString(ofToString(attention), 100, ofGetHeight()/20 - 10);
        }
        ofPopStyle();
        ofPopMatrix();
    }
    
    if(mode == -9){
        introX.draw(0,0,ofGetWidth(), ofGetHeight());
    }
    
//    //cout << "mainThread Printing" << endl;
    
    //TEST MODE----------------------
    if(mode == 100){
        story.draw(blink);
        blink = 0;
        
    }
    //END TEST MODE------------------
    
    if(mode==3){
        //        story.draw(blink); // turn on to activate blink visual
        story.draw(0);
//        ofPushStyle();
//        ofSetColor(0, 0, 0);
//        ofRect(0, 0, ofGetWidth(), ofGetHeight());
//        ofPopStyle();
        eeg.draw();
        blink = 0; //reset for new reading in next frame (to be read in update as well)
    }
    
    if(mode==2){
        minigame.draw();
        eeg.draw();
        blink = 0;
    }
    
    if(mode == 16){
        tutorial.draw(0,0,ofGetWidth(),ofGetHeight());
        story.hud1.drawMini(2);
        eeg.draw();
    }
    
    if(mode == 15){
        description.draw(0, 0, ofGetWidth(), ofGetHeight());
        eeg.draw();
    }
    
    if(mode==1){
        ofPushStyle();
        ofSetColor(0);
//        ofRect(0, 0, ofGetScreenWidth(), ofGetScreenHeight());
        ofRect(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
        ofSetColor(255);
        font1.drawString("Connecting to device...", 100, 100);
        ofPopStyle();
        connectText = true;
    }
    
    if(mode==0){
//        intro.draw(0,0, ofGetScreenWidth(), ofGetScreenHeight());
        intro.draw(0,0, ofGetWindowWidth(), ofGetWindowHeight());
        
        //Animate w/ Sin smoothing the NeuroSky Devices sliding in
        if(ofGetElapsedTimeMillis()-timeOfZero < (PI/2)*1200.0){
            neuroSkyDevices.draw(0, ((250/768.0)*ofGetScreenHeight())*(1-sin((ofGetElapsedTimeMillis()-timeOfZero)/1200.0)), ofGetWidth(), ofGetHeight());
        }
        else{
            neuroSkyDevices.draw(0,0,ofGetWidth(), ofGetHeight());
        }
    }
    
    ofSetWindowTitle("fps = " + ofToString(ofGetFrameRate()));
    
    if(mode==-1){
        intro.draw(0,0, ofGetWidth(), ofGetHeight());
        ofPushStyle();
        ofSetColor(0, 0, 0, ((timeOfFadeIn-(ofGetElapsedTimeMillis()-timeOfNegativeOne))/timeOfFadeIn)*355);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
        ofPopStyle();
    }
    
    if(mode==-2){
        ofPushStyle();
        ofSetColor(0);
        ofRect(0, 0, ofGetWidth(), ofGetHeight());
        ofPopStyle();
    }
    
    if(mode == -10){
        appPicker.draw(0, 0, ofGetWidth(), ofGetHeight());
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
    if(key=='f'){
        ofToggleFullscreen();
    }
    
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
        if(key=='m'){
            minigame.setup();
            mode = 100;
        }
        
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
    
    timeOfLastMouseRelease = ofGetElapsedTimeMillis();
    
    if(mode==100){
        
        minigame.randomizeQuote();
    }
    
    if(mode==3){
        bool resetAttention = false;
        resetAttention = story.turnPage(2, chapterAttValue);
        if (resetAttention){
            
//            for(int i = 0; i < eeg.chapValues.size(); i++){
//                eeg.chapValues.pop_back();
//            }
            eeg.chapValues.clear();
        }
    }
    
    if(mode==2){
        mode=3;
        
    }
    
    
    if(mode == 16){
        mode = 2;
    }
    
    if(mode == 15){
        mode = 16;
    }
    
    if(mode==0 || mode ==-1){
        
        string temp = ofToString((int)ofRandom(10000,20000));
        string session = "session";
        string txt = ".txt";
        
        string _fileName = temp+session+txt;
        //    strcat_s("session",Max_Char,FirstName);
        
        fileName = &_fileName[0];
        myFile.open(fileName);
        myFile << "Time (Milliseconds)" << ", " << "Device Number(1:MW,2:MS,3:BB)"<< ", "<< "Signal Quality(0-100)"<< ", "<< "Story Average Attention (0-100)" <<", " << "Chapter Attention Value" <<", " << "Current Attention Value" << ", " << "Chapter(0,1,2)" << ", " << "Page" <<", " << "Tier(0,1,2)" << ", " << "Mode" <<  endl;
        
        if(mouseX>=(897.0/1280.0)*ofGetWidth() && mouseX <= (999.0/1280.0)*ofGetWidth() && mouseY >= (653.0/768.0)*ofGetHeight() && mouseY <= (754.0/768.0)*ofGetHeight()){ //select Mindwave Mobile on intro screen
            mode=1;
            deviceNumber = 1;
//            loadScreen.startThread(false,true);
            
        }
        if(mouseX>=(1028.0/1280.0)*ofGetWidth() && mouseX <= (1129.0/1280.0)*ofGetWidth() && mouseY >= (653.0/768.0)*ofGetHeight() && mouseY <= (754.0/768.0)*ofGetHeight()){ //select Mindset on intro screen
            mode=1;
            deviceNumber = 2;
        }
        if(mouseX>=(1157.0/1280.0)*ofGetWidth() && mouseX <= (1259.0/1280.0)*ofGetWidth() && mouseY >= (653.0/768.0)*ofGetHeight() && mouseY <= (754.0/768.0)*ofGetHeight()){ //select Mindband
            mode=1;
            deviceNumber = 3;
        }
    }
    //cout << "XXXXXXXXXXXXXXXXX mouseX: " << mouseX << " || mouseY: " << mouseY << endl;  }
    

}

void testApp::attentionListener(float &param)
{
    attention = param;
    distAw = ofMap(attention, 0.0, 100.0, 0, ofGetWidth());
    atChangeTime = ofGetElapsedTimef();
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