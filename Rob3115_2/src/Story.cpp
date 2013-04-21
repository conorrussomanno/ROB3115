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
    currentTier = 0; //0=High Attention; 1=Medium Attention; 2=Low Attention
    currentPage = 0;
    
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
    
    tempText = "void";
    tempImg.loadImage("_1_1_1_.png");   // _1_1_1_ = (chapter1, attention high, page1); _2_3_2_ = (chapter2, attention low, page2)
    tempInt = 1;
    
    tempPage.setup(tempText, tempImg, tempInt);
    pages[0][0].push_back(tempPage); //add 1 page to (chapter 1, tier 1)
    
    tempImg.loadImage("_1_1_2_.png");
    tempPage.setup(tempText, tempImg, tempInt);
    pages[0][0].push_back(tempPage); //add another page to (chapter 1, tier 1)
    
    tempImg.loadImage("_1_1_3_.png");
    tempPage.setup(tempText, tempImg, tempInt);
    pages[0][0].push_back(tempPage);
    
    tempImg.loadImage("_1_1_4_.png");
    tempPage.setup(tempText, tempImg, tempInt);
    pages[0][0].push_back(tempPage);
    
    tempImg.loadImage("_1_1_5_.png");
    tempPage.setup(tempText, tempImg, tempInt);
    pages[0][0].push_back(tempPage);
    
    tempImg.loadImage("_1_1_6_.png");
    tempPage.setup(tempText, tempImg, tempInt);
    pages[0][0].push_back(tempPage);
    
    
    tempImg.loadImage("_2_1_1_.png");
    tempPage.setup(tempText, tempImg, tempInt);
    pages[1][0].push_back(tempPage); //add 1 page to (chapter 2, tier 1)
    
    tempImg.loadImage("_2_2_1_.png");
    tempPage.setup(tempText, tempImg, tempInt);
    pages[1][1].push_back(tempPage); //add 1 page to (chapter 2, tier 2)
    
    tempImg.loadImage("_2_3_1_.png");
    tempPage.setup(tempText, tempImg, tempInt);
    pages[1][2].push_back(tempPage);
}

//--------------------------------------------------------------
void Story::update(){
    
}

//--------------------------------------------------------------
void Story::draw(){
    
    pages[currentChapter][currentTier][currentPage].draw();
}

bool Story::turnPage(float _attValue){
    
    
    if(currentPage+1==pages[currentChapter][currentTier].size()){
        nextChapter(_attValue);
    }
    else{
        currentPage++;
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

