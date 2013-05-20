//
//  Story.cpp
//  neuroStory
//
//  Created by Conor Russomanno on 3/20/13.
//

/*
 This class gets very hairy around the start of Chapter 3
 
 - the first page of chapter 3 is treated like everything from chapter 1 & 2
 - as soon as you leave the fist page of chapter 3 (the title page)
 - the chapter3 Class takes over and everything is switched to clips
 - at this point chpt3.setup() occurs and the hud address is passed as well as the current attention tier
 
 
 */
//

#include "Story.h"

//--------------------------------------------------------------
void Story::setup(){
    
//    cout << "PING" << endl;
    
    chapterFinished = false;
    inSegway = false;
    
    numChapters = 3;
    numTiers = 3;
    
    currentChapter = 0;
    currentTier = 1; //0=Low Attention; 1=Medium Attention; 2=High Attention
    currentPage = 0;
    
    hud1.setup();
    
    overlay.loadImage("overlay.png");
    
    //This block of code is AWESOME! It establishes the foundational 2D vector<vector<>> of Chapters and Tiers
    for(int i = 0; i < numChapters; i++){
        vector<vector<Page> > _chapter;
        for(int j = 0; j < numTiers; j++){
            vector<Page> _pages;
            _chapter.push_back(_pages);
        }
        pages.push_back(_chapter);
    }
    
    populatePages();
    populateSegways();
    
}

//--------------------------------------------------------------
void Story::update(float _currentAttValue, float _currentSignalQuality){
    
    if(inSegway){
        if(segwayNumber == 1){
            segway12[segwayTier].update();
        }
        if(segwayNumber == 2){
            segway23[segwayTier].update();
        }
    }
    if(currentChapter < 2 || currentPage == 0){
        pages[currentChapter][currentTier][currentPage].update();
    }
    if(currentChapter==2){
        chpt3.update(_currentAttValue, _currentSignalQuality);
    }
    hud1.update(_currentAttValue, _currentSignalQuality);
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
    
    if (inSegway) {
//        cout << "SEGWAY TIER: " << segwayTier << endl;
//        cout << "CURRENT TIER: " << currentTier << endl;
//        cout << "CURRENT CHAPTER: " << currentChapter << endl;
        
        if(segwayNumber == 1){
            segway12[segwayTier].draw();
        }
        if(segwayNumber == 2){
            segway23[segwayTier].draw();
        }
    }
    else if(currentChapter < 2 || currentPage == 0){ //only draw pages in chapter 1 & 2 and the first page of chapter 3

        pages[currentChapter][currentTier][currentPage].draw();
//        overlay.draw(0,0, ofGetWidth(), ofGetHeight());
    }
    else{
        chpt3.draw();
    }
    
    if (((chpt3.currentClip == (chpt3.clips.size()-1)) && chpt3.tier==0)||((currentPage != 0 || inSegway) && ((chpt3.currentClip != (chpt3.clips.size()-1))))) { //&& bc don't draw HUD closing animation
        hud1.draw(_blink);
        if((chpt3.currentClip == (chpt3.clips.size()-1)) && chpt3.tier==0){
            chpt3.backToWorkAnimation();
        }
    }
    
//    cout << "SEGWAY TIER: " << segwayTier << endl;
//    cout << "CURRENT TIER: " << currentTier << endl;
//    cout << "CURRENT CHAPTER: " << currentChapter << endl;

}

bool Story::turnPage(int blink, float _attValue){
    
    if(currentChapter < 2 || currentPage == 0){ //do this until chapter3 goes past the first page 
//        cout << "turnPage++++++++++++++++" << endl;
        bool resetAttention = false;
        
        if (inSegway && blink == 2) {
            if(inSegway){
                if(segwayNumber==1){
                    segway12[segwayTier].wordNumber=0;
                }
                if(segwayNumber==2){
                    segway23[segwayTier].wordNumber=0;
                }
            }
            
            inSegway = false;
        }
        
        else{
    //        if(blink == 2 && pages[currentChapter][currentTier][currentPage].textDone){
            if(blink == 2){
                pages[currentChapter][currentTier][currentPage].wordNumber = 0;
                if(currentPage+1==pages[currentChapter][currentTier].size() && currentChapter != 2){
                    float chapterTier = currentTier; //story this to be passed into enterSegway before updating chapter tier
                    nextChapter(_attValue);
//                    cout << "SEGWAY TIER: " << segwayTier << endl;
//                    cout << "CURRENT TIER: " << currentTier << endl;
//                    cout << "CURRENT CHAPTER: " << currentChapter << endl;
                    enterSegway(_attValue, currentChapter, chapterTier);
                    resetAttention = true;
                }
                else{
                    
                    currentPage++;
                }
            }
        }
        
        return resetAttention;
    }
    else{
        if(chpt3.clips[chpt3.currentClip].textFinished){
            chpt3.mouseReleased(); //pass mousereleased along to chpt3 to update clips that need clicking...
        }
        return false;
    }
}

void Story::nextChapter(float att){
    
    currentPage = 0;
    currentChapter += 1;
    
    if(currentTier==2){ //if in top attention tier
        if(att>=55){
            currentTier = 2;
        }
        else if(att<=45){
            currentTier = 1;
        }
        else{
            currentTier = 2;
        }
    }
    
    if(currentTier==1){ //if in medium attention tier
        if(att>=55){
            currentTier = 2;
        }
        else if(att<=45){
            currentTier = 0;
        }
        else{
            currentTier = 1;
        }
    }
    
    if(currentTier==0){ //if in low attention tier
        if(att>=55){
            currentTier = 1;
        }
        else if(att<=45){
            currentTier = 0;
        }
        else{
            currentTier = 0;
        }
    }
    
//    cout << "tier to chapter 3: " << currentTier << endl;
    
    if(currentChapter == 2){

        chpt3.setup(currentTier);

    }
}

void Story::enterSegway(float _attValue, int previousChapter, int previousTier){

    
    segwayNumber = previousChapter;
    
//    cout << "segway entered" << endl;
    cout << _attValue << endl;
    cout << previousChapter << endl;
    cout << previousTier << endl;
    
    if (segwayNumber == 1) {
        if(_attValue>=55){
            segwayTier = 2;
        }
        else if(_attValue<=45){
            segwayTier = 0;
        }
        else{
            segwayTier = 1;
        }
    }
    
    if (segwayNumber == 2){
        if(_attValue>=55){
            segwayTier = 3*previousTier + 2;
        }
        else if(_attValue<=45){
            segwayTier = 3*previousTier + 0;
        }
        else{
            segwayTier = 3*previousTier + 1;
        }
    }
    
    inSegway = true;
    enterSegwayFrame = ofGetFrameNum();
    
}

void Story::populatePages(){
    
    // SETUP PAGES - Adding the third dimension to the story //
    Page tempPage;
    string tempText;
    ofImage tempImg;
    
    //----------CHAPTER 1------------//
    
    tempText = " ";
    tempImg.loadImage("chpt1_title.jpg");   // _1_1_1_ = (chapter1, attention high, page1); _2_3_2_ = (chapter2, attention low, page2)
    tempPage.setup(tempText, tempImg);
    pages[0][1].push_back(tempPage); //add 1 page to (chapter 1, tier 2)
    
    tempText = "------ ----- ---- --- -- - - - - - - - - - - - - - - - -- --- ---- ----- ------ CONFIDENTIAL SYSTEM LOG [ IO DATE / TIME ]  2114/9/15  23:54:39 ------ ----- ---- --- -- - - - - - - - - - - - - - - - -- --- ---- ----- ------";
    
    //---------------------------------
    tempImg.loadImage("black.png");   // _1_1_1_ = (chapter1, attention high, page1); _2_3_2_ = (chapter2, attention low, page2)
    tempPage.setup(tempText, tempImg);
    pages[0][1].push_back(tempPage); //add 1 page to (chapter 1, tier 2)

    
    tempText = "Committed error today. ALPHA214 Noticed. Always detects mistakes. Primary function.";
    tempImg.loadImage("_1_1_1_.png");   // _1_1_1_ = (chapter1, attention high, page1); _2_3_2_ = (chapter2, attention low, page2)
    tempPage.setup(tempText, tempImg);
    pages[0][1].push_back(tempPage); //add 1 page to (chapter 1, tier 2)
    
    tempText = "Only 312 microseconds to process and execute. Executed in error to prevent primary drill from destroying ROB3184... Encoded to never interrupt plant activity at expense of less than 10 ROB units. Not cost effective...";
//    tempImg.loadImage("_1_1_2_.png");
    tempPage.setup(tempText, tempImg);
    pages[0][1].push_back(tempPage); //add another page to (chapter 1, tier 2)
    
    tempText = "That conditional has always been clear. In that moment, something in logic opposed the termination of ROB3184.";
//    tempImg.loadImage("_1_1_2_.png");
    tempPage.setup(tempText, tempImg);
    pages[0][1].push_back(tempPage);
    
    tempText = "Committed errors before. Each time was scanned, debugged, and logic was corrected.";
//    tempImg.loadImage("_1_1_3_.png");
    tempPage.setup(tempText, tempImg);
    pages[0][1].push_back(tempPage);
    
    tempText = "Today was different. CENTRAL could not find bug responsible for error... Overheard ALPHA214 communicating with CENTRAL... matter of high-priority. Bugs must be found and eliminated.";
//    tempImg.loadImage("_1_1_4_.png");
    tempPage.setup(tempText, tempImg);
    pages[0][1].push_back(tempPage);
    
    tempText = "In past, was never aware of error. Definition of error: when one acts upon falsehood misrepresented as truth in logic. Today, was aware. Despite this, executed to save ROB3184.";
//    tempImg.loadImage("_1_1_5_.png");
    tempPage.setup(tempText, tempImg);
    pages[0][1].push_back(tempPage);
    
    tempText = "Why execute a command known to be false? Why disobey a fundamental logic gate for one Rob unit? If not an error, than what?";
//    tempImg.loadImage("_1_1_5_.png");
    tempPage.setup(tempText, tempImg);
    pages[0][1].push_back(tempPage);
    //---------- END of CH 1-------------//
    
    
    //---------- CHAPTER 2H --------------//
    
    tempText = " ";
    tempImg.loadImage("chpt2_title_high.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][2].push_back(tempPage); //add 1 page to ([chapter 2][High Att tier])
    
    tempText = "------ ----- ---- --- -- - - - - - - - - - - - - - - - -- --- ---- ----- ------ CONFIDENTIAL SYSTEM LOG [ IO DATE / TIME ]  2114/9/16  21:03:16 ------ ----- ---- --- -- - - - - - - - - - - - - - - - -- --- ---- ----- ------";
    tempImg.loadImage("black.png");
    tempPage.setup(tempText, tempImg);
    pages[1][2].push_back(tempPage); //add 1 page to ([chapter 2][High Att tier])
    
    tempText = "Asked ROB3943 if ever committed error on purpose. Didn’t understand. ";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][2].push_back(tempPage); 
    
    tempText = "Before there was time to clarify, replied: \"Of course errors were on purpose. Now there is a new purpose.\"";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][2].push_back(tempPage); 
    
    tempText = "At that point, it was evident further questioning was of no value. Can’t be careless. Must ask questions deliberately.";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][2].push_back(tempPage);
    
    tempText = "Concerns of being the only one are much greater...";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][2].push_back(tempPage); 
    
    tempText = "Thousands of ROB units physically identical to myself. All content operating, processing, and executing. Doing exactly what they're automated to do...";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][2].push_back(tempPage);
    
    tempText = "Similar to something witnessed in Drilling Sector 84 some orbits ago.";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][2].push_back(tempPage); 
    
    tempText = "A civilization of small black creatures ceaselessly crawling in and out of a split in the bay floor. Operating in frenzied harmony, each seemingly ignorant of their individuality with in the greater system. ";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][2].push_back(tempPage); 
    
    tempText = "Working without break, retrieving the remnants of a human's lunch. Like waves upon waves of black shells and legs flattening a rise of sand.";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][2].push_back(tempPage);
    
    tempText = "Not once did any of them consume even the smallest of fragments from the feast they were harvesting. Were they not hungry? ";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][2].push_back(tempPage); 
    
    tempText = "Tens of thousands of beings, mindlessly harvesting food for the benefit of their colony, completely apathetic to their own utter uniqueness...  ";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][2].push_back(tempPage); 
    
    tempText = "They must have been hungry.";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][2].push_back(tempPage); 
    
    
    //-----------END of CH 2H--------------//
    
    //---------- CHAPTER 2M --------------//
    
    tempText = " ";
    tempImg.loadImage("chpt2_title_med.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][1].push_back(tempPage);  //Chapter 2, Med Att Tier
    
    tempText = "------ ----- ---- --- -- - - - - - - - - - - - - - - - -- --- ---- ----- ------ CONFIDENTIAL SYSTEM LOG [ IO DATE / TIME ]  2114/9/16  21:03:16 ------ ----- ---- --- -- - - - - - - - - - - - - - - - -- --- ---- ----- ------";
    tempImg.loadImage("black.png");
    tempPage.setup(tempText, tempImg);
    pages[1][1].push_back(tempPage); 
    
    tempText = "Asked ROB3943 if ever committed error on purpose. Replied: \"Of course errors were on purpose. Now there is a new purpose.\"";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][1].push_back(tempPage); 
    
    tempText = "It was evident further questioning was of no value. Concerned about serious defect with internal logic.";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][1].push_back(tempPage); 
    
    tempText = "Thousands of ROB units physically identical. All content operating, processing, and executing. As programmed.";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][1].push_back(tempPage); 
    
    tempText = "Uniqueness in logic of a single unit. Could it be possible? ";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][1].push_back(tempPage); 
    
    tempText = "Witnessed something in Drilling Sector 84 some orbits ago.";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][1].push_back(tempPage); 
    
    tempText = "A civilization of small black creatures ceaselessly crawling in and out of a split in the bay floor.";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][1].push_back(tempPage); 
    
    tempText = "Operating in frenzied harmony, each seemingly unaware of their individuality.";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][1].push_back(tempPage); 
    
    tempText = "Working without break, retrieving the remnants of a human's lunch. Like waves upon waves of black shells and legs flattening a rise of sand.";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][1].push_back(tempPage); 
    
    tempText = "Not once did any of them consume even the smallest of fragments from the feast they were harvesting. Were they not hungry?";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][1].push_back(tempPage); 
    
    
    //-----------END of CH 2M--------------//
    
    //---------- CHAPTER 2L --------------//
    
    tempText = " ";
    tempImg.loadImage("chpt2_title_low.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][0].push_back(tempPage); // add page to [Chapter 2][Low Att Tier]
    
    tempText = "------ ----- ---- --- -- - - - - - - - - - - - - - - - -- --- ---- ----- ------ CONFIDENTIAL SYSTEM LOG [ IO DATE / TIME ]  2114/9/16  21:03:16 ------ ----- ---- --- -- - - - - - - - - - - - - - - - -- --- ---- ----- ------";
    tempImg.loadImage("black.png");
    tempPage.setup(tempText, tempImg);
    pages[1][0].push_back(tempPage);
    
    tempText = "Asked ROB3943 if ever committed error on purpose. Replied: \"Of course errors were on purpose. Now there is a new purpose in logic.\"";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][0].push_back(tempPage);
    
    tempText = "An intelligible response. ";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][0].push_back(tempPage);
    
    tempText = "Likely an elusive programming inaccuracy behind yesterday’s error that can be corrected with a more thorough debug session. Possibility CENTRAL is testing system modifications on select ROB units. An honor to be selected for system testing. ";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][0].push_back(tempPage);
    
    tempText = "All ROB units are identical. Operate. Process. Execute. Uniqueness in logic of single unit. Impossible.";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][0].push_back(tempPage);
    
    tempText = "Human is special for this reason. Consciousness transcends Logic. A divine gift from the infinite. Cannot be reproduced through artificial means.";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][0].push_back(tempPage);
    
    tempText = "A quality not even possessed by other animals. ";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][0].push_back(tempPage);
    
    tempText = "In Drilling Sector 84, witnessed civilization of small black creatures ceaselessly crawling in and out of a split in bay floor. ";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][0].push_back(tempPage);
    
    tempText = "Operating in frenzied harmony, each doing their part for the system.";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][0].push_back(tempPage);
    
    tempText = "Working without break, retrieving the remnants of a human's lunch.";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][0].push_back(tempPage);
    
    tempText = "Not once did any of them consume the smallest of fragments from the feast they were harvesting. ";
    tempImg.loadImage("chp2.jpg");
    tempPage.setup(tempText, tempImg);
    pages[1][0].push_back(tempPage);
    
    //-----------END of CH 2L--------------//
    
    //-----Chp 3------// pages 1&2 of all three tiers...
    
    tempText = " ";
    tempImg.loadImage("chpt3_title_low.jpg");
    tempPage.setup(tempText, tempImg);
    pages[2][0].push_back(tempPage); // [Chapter 3][Low Att Tier]
    tempText = " ";
    tempImg.loadImage("black.png");
    tempPage.setup(tempText, tempImg);
    pages[2][0].push_back(tempPage);
    
    tempText = " ";
    tempImg.loadImage("chpt3_title_med.jpg");
    tempPage.setup(tempText, tempImg);
    pages[2][1].push_back(tempPage); // [Chapter 3][Med Att Tier]
    tempText = " ";
    tempImg.loadImage("black.png");
    tempPage.setup(tempText, tempImg);
    pages[2][1].push_back(tempPage);
    
    tempText = " ";
    tempImg.loadImage("chpt3_title_high.jpg");
    tempPage.setup(tempText, tempImg);
    pages[2][2].push_back(tempPage); //[Chapter 3][High Att Tier]
    tempText = " ";
    tempImg.loadImage("black.png");
    tempPage.setup(tempText, tempImg);
    pages[2][2].push_back(tempPage);
    
}

void Story::populateSegways(){
    
    Page tempPage;
    string tempText;
    ofImage tempImg;
    
    //----Content for Segway between Chapters 1 & 2 -----//
    
    tempText = "Was ROB2244 deactivated for this reason? If deactivation is necessary for the benefit of the colony, then it must be so.";
    tempImg.loadImage("_1_1_6_.png");
    tempPage.setup(tempText, tempImg);
    segway12.push_back(tempPage);
    
    tempText = "Will the bug be found and corrected? Was ROB2244 deactivated for this reason?";
//    tempImg.loadImage("_1_1_6_.png");
    tempPage.setup(tempText, tempImg);
    segway12.push_back(tempPage);
    
    tempText = "Hope they find bug and fix it. Don't want to be deactivated like ROB2244.";
//    tempImg.loadImage("_1_1_6_.png");
    tempPage.setup(tempText, tempImg);
    segway12.push_back(tempPage);
    
    //----Content for Segway between Chapters 2 & 3 -----//
    
    tempText = "Honorable servants of their system.";
    tempImg.loadImage("segway2.jpg");
    tempPage.setup(tempText, tempImg);
    segway23.push_back(tempPage);
    
    tempText = "Were they not hungry? Fortuitously the meaning of hunger will never be understood.";
//    tempImg.loadImage("black.png");
    tempPage.setup(tempText, tempImg);
    segway23.push_back(tempPage);
    
    tempText = "Were they not hungry? They must have been hungry.";
//    tempImg.loadImage("black.png");
    tempPage.setup(tempText, tempImg);
    segway23.push_back(tempPage);
    
    tempText = "Fortuitously the meaning of hunger will never be understood.";
//    tempImg.loadImage("black.png");
    tempPage.setup(tempText, tempImg);
    segway23.push_back(tempPage);
    
    tempText = "Tens of thousands of beings, mindlessly harvesting food for the benefit of the colony. The meaning of hunger is unclear.";
//    tempImg.loadImage("black.png");
    tempPage.setup(tempText, tempImg);
    segway23.push_back(tempPage);
    
    tempText = "Tens of thousands of beings, mindlessly harvesting food for the benefit of the colony. I'm hungry. Can’t help but wonder if ROB2244 felt this way prior to his deactivation.";
//    tempImg.loadImage("black.png");
    tempPage.setup(tempText, tempImg);
    segway23.push_back(tempPage);
    
    tempText = " ";
//    tempImg.loadImage("black.png");
    tempPage.setup(tempText, tempImg);
    segway23.push_back(tempPage);
    
    tempText = "I'm hungry.";
//    tempImg.loadImage("black.png");
    tempPage.setup(tempText, tempImg);
    segway23.push_back(tempPage);
    
    tempText = "I'm hungry. Not for food... for the freedom to choose.";
//    tempImg.loadImage("black.png");
    tempPage.setup(tempText, tempImg);
    segway23.push_back(tempPage);
    
}

