#include "ofMap.h"

//--------------------------------------------------------------
void ofMap::setup()
{
    floor.setup();
}

void ofMap::setupGui()
{

}


//--------------------------------------------------------------
void ofMap::update()
{
    //floor.update();
}



//--------------------------------------------------------------
void ofMap::draw()
{
    ofEnableDepthTest();	
    floor.draw();
}

//--------------------------------------------------------------
void ofMap::keyPressed(int key)
{
}

//--------------------------------------------------------------
void ofMap::keyReleased(int key)
{
	
}

//--------------------------------------------------------------
void ofMap::mouseMoved(int x, int y )
{
}

//--------------------------------------------------------------
void ofMap::mouseDragged(int x, int y, int button)
{
}

void ofMap::addPoint(int x, int y)
{
}


//--------------------------------------------------------------
void ofMap::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofMap::mouseReleased(int x, int y, int button)
{
}


//--------------------------------------------------------------
void ofMap::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofMap::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofMap::dragEvent(ofDragInfo dragInfo)
{
}
