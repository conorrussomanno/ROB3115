
#include "ofMain.h"
#include "Page.h"

class Story : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    bool turnPage(float _attValue); //returns true if last page in chapter
    void nextChapter(float att);
    
    bool chapterFinished;
    
    int numChapters;
    int numTiers;
    
    int currentChapter;
    int currentTier;
    int currentPage;
    
    vector<vector<vector<Page> > > pages; // (chapter#, attention tier, page#)
    
    //Segway passages
    Page s2H_H;
    Page s2H_M;
    Page s2H_L;
    Page s2M_H;
    Page s2M_M;
    Page s2M_L;
    Page s2L_H;
    Page s2L_M;
    Page s2L_L;
    
};
