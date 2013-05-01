
#include "ofMain.h"
#include "Page.h"
#include "HUD.h"

class Story : public ofBaseApp{
    
public:
    void setup();
    void update(float _currentAttValue, float _currentSignalQuality);
    void draw(int _blink);
    
    bool turnPage(int blink, float _attValue); //returns true if last page in chapter
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
    
    HUD hud1;
    
};
