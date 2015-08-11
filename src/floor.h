//
//  generativeDelaunayFloor.h
//  Mapping
//
//  Created by Joao Freire on 10/08/15.
//
//

#ifndef __generativeDelaunayFloor__
#define __generativeDelaunayFloor__

#include "ofMain.h"
#include "ofxDelaunay.h"

class offFloor
{
public:
    void setup();
    void update();
    void draw();
    void setNormals( ofMesh &mesh );
    void setLightOri(ofLight &light, ofVec3f rot);

private:
    vector<ofPoint> vertices;
    vector <ofColor> colors;
    int nTri;
    int nVert;
    ofMesh mesh;		//Mesh
    ofLight light;		//Light
    ofEasyCam cam;
    
    ofxDelaunay tri;

    ofLight spot;
    ofLight point;
    ofLight dir;
    ofLight amb;
    ofMaterial material;
    bool guiAlloc;
    
    ofVec3f dir_rot;
    ofVec3f spot_rot;
};

#endif /* defined(__generativeDelaunayFloor__) */
