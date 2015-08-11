#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofMath.h"
#include "floor.h"

class ofMap : public ofBaseApp
{
    
public:
    void setup();
    void setupGui();
    void update();
    void draw();
		
    void drawFboTest(); // draws some test graphics into the two fbos
		
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void addPoint(int x, int y);
    void removePoint(int x, int y);
    void connectPoint(int x, int y);
    int figureIndex(int index);
    
    offFloor floor;
   
};
