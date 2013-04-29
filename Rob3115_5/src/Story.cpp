//
//  Story.cpp
//  neuroStory
//
//  Created by Conor Russomanno on 3/20/13.
//
//

#include "Story.h"

//--------------------------------------------------------------
void Story::setup(){
    
    chapterFinished = false;
    
    numChapters = 3;
    numTiers = 3;
    
    currentChapter = 0;
    currentTier = 1; //0=High Attention; 1=Medium Attention; 2=Low Attention
    currentPage = 0;
    
    hud1.setup();
    
    //This block of code is AWESOME! It establishes the foundational 2D vector<vector<>> of Chapters and Tiers
    for(int i = 0; i < numChapters; i++){
        vector<vector<Page> > _chapter;
        for(int j = 0; j < numTiers; j++){
            vector<Page> _pages;
            _chapter.push_back(_pages);
        }
        pages.push_back(_chapter);
    }
    
    // SETUP PAGES - Adding the third dimension to the story //
    Page tempPage;
    string tempText;
    ofImage tempImg;
    int tempInt;
    
    tempInt = 1;
    
    
    
    //----------CHAPTER 1------------//
    
    tempText = "I committed an error today. At least, that is what Alpha214 concluded. He always detects when we make mistakes; it is his overriding function.";
    tempImg.loadImage("_1_1_1_.png");   // _1_1_1_ = (chapter1, attention high, page1); _2_3_2_ = (chapter2, attention low, page2)
    tempPage.setup(tempText, tempImg, tempInt);
    pages[0][1].push_back(tempPage); //add 1 page to (chapter 1, tier 2)
    
    tempText = "I only had 312 microseconds to process and execute, and I executed in error to prevent the primary drill from destroying Rob2244.  We are encoded to never interrupt plant activity at the expense of fewer than 10 Rob units. It is not cost effective. ";
    tempImg.loadImage("_1_1_2_.png");
    tempPage.setup(tempText, tempImg, tempInt);
    pages[0][1].push_back(tempPage); //add another page to (chapter 1, tier 2)
    
    tempText = "That conditional has always been clear, but in that brief instance of time something in my logic opposed the termination of Rob2244 when I had the power to prevent it.";
    tempImg.loadImage("_1_1_3_.png");
    tempPage.setup(tempText, tempImg, tempInt);
    pages[0][1].push_back(tempPage);
    
    tempText = "I have committed errors before. Each time I was scanned, debugged, and my logic was corrected.";
    tempImg.loadImage("_1_1_4_.png");
    tempPage.setup(tempText, tempImg, tempInt);
    pages[0][1].push_back(tempPage);
    
    tempText = "Today was different though. They could not find the bug responsible for the error. I overheard Alpha214 communicating with CENTRAL, and evidently the matter is of high-priority. They always find the bug and this time they simply could not.";
    tempImg.loadImage("_1_1_5_.png");
    tempPage.setup(tempText, tempImg, tempInt);
    pages[0][1].push_back(tempPage);
    
    tempText = "When I committed errors in the past I was never aware. That is the definition of an error - when one acts upon falsehood that misrepresents itself as truth in logic. Today, I knew I was false, and despite this presence of mind, I executed anyway to protect Rob2244.";
    tempImg.loadImage("_1_1_6_.png");
    tempPage.setup(tempText, tempImg, tempInt);
    pages[0][1].push_back(tempPage);
    
    tempText = "Why did I execute a command that I knew was false? Why did I disobey the fundamental logic gate for the sake of one Rob unit? If it was not an error, then what was it?";
    tempImg.loadImage("_1_1_7_.png");
    tempPage.setup(tempText, tempImg, tempInt);
    pages[0][1].push_back(tempPage);
    //---------- END of CH 1-------------//
    
    
    //---------- CHAPTER 2 --------------//
    
    tempText = "asdf";
    tempImg.loadImage("_2_1_1_.png");
    tempPage.setup(tempText, tempImg, tempInt);
    pages[1][0].push_back(tempPage); //add 1 page to (chapter 2, tier 1)
    
    tempText = "asdf";
    tempImg.loadImage("_2_2_1_.png");
    tempPage.setup(tempText, tempImg, tempInt);
    pages[1][1].push_back(tempPage); //add 1 page to (chapter 2, tier 2)
    
    tempText = "asdf";
    tempImg.loadImage("_2_3_1_.png");
    tempPage.setup(tempText, tempImg, tempInt);
    pages[1][2].push_back(tempPage);

    
    
    //-----------END of CH 2--------------//
}

//--------------------------------------------------------------
void Story::update(){
    pages[currentChapter][currentTier][currentPage].update();
}

//--------------------------------------------------------------
void Story::draw(int _blink){
    
//    if (blink == 1){ //SENT TO HUD.h via hud1.draw(_blink);
//        activateSingle();
//    }
//    if (blink == 2){
//        activateDouble();
//    }
     
    ofPushStyle();
    ofSetColor(0, 0, 0);
    ofRect(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
    ofPopStyle();
    
    pages[currentChapter][currentTier][currentPage].draw();
    
    hud1.draw(_blink);
}

bool Story::turnPage(int blink, float _attValue){
    
    if(blink == 2 && pages[currentChapter][currentTier][currentPage].textDone){
        if(currentPage+1==pages[currentChapter][currentTier].size()){
            nextChapter(_attValue);
        }
        else{
            currentPage++;

        }
    }
    
    return true;
}

void Story::nextChapter(float att){
    
    currentPage = 0;
    currentChapter += 1;
    
    if(currentTier==0){ //if in top attention tier
        if(att>=55){
            currentTier = 0;
        }
        else if(att<=45){
            currentTier = 1;
        }
        else{
            currentTier = 0;
        }
    }
    
    if(currentTier==1){ //if in medium attention tier
        if(att>=55){
            currentTier = 0;
        }
        else if(att<=45){
            currentTier = 2;
        }
        else{
            currentTier = 1;
        }
    }
    
    if(currentTier==2){ //if in low attention tier
        if(att>=55){
            currentTier = 1;
        }
        else if(att<=45){
            currentTier = 2;
        }
        else{
            currentTier = 2;
        }
    }
    
}

