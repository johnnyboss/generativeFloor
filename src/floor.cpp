//
//  floor.cpp
//  Generative floor
//
//
//
//
int W = 1000;		//Grid size
int H = 1000;
#include "floor.h"

void offFloor::setup()
{
    tri.setupColors();
    nTri = ofRandom(1000,2000);
    nVert = nTri * 3;
    float Rad = 250;
    float rad = 1000;
    vertices.resize(nVert);
    
    
    for(int i = 0; i < nTri; i++)
    {
        tri.addPoint(ofRandom(-ofGetWidth(),ofGetWidth()), ofRandom(-ofGetHeight(),ofGetHeight()), ofRandom(20));
        /*ofPoint center (ofRandom(-1,1), ofRandom(-1,1),0);// ofRandom(-1,1));
        center.normalize();
        center *= ofRandom(100,Rad);
        
        
        tri.addPoint(center + ofPoint(ofRandom(200, rad), ofRandom(200, rad), ofRandom(0,50)));
        for(int j = 0; j < 3; j++)
        {
            vertices[i*3 + j] = center + ofPoint(ofRandom(-rad, rad), ofRandom(-rad, rad), 0);//ofRandom( -rad, rad ));
        }*/
    }
    //Fill the array of triangles' colors
    colors.resize( nTri );
    for (int i=0; i<nTri; i++) {
        //Take a random color from black to red
        colors[i] = ofColor( ofRandom( 0, 255 ), 0, 0 );
    }
    //Set up vertices and colors
    tri.triangulate();
    ofEnableSmoothing();
    ofSetGlobalAmbientColor(ofColor(0, 0, 0));
    ofSetSmoothLighting(true);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    ofSetSphereResolution(100);
    amb.setAmbientColor(ofColor(200.0, 200.0, 200.0, 200.0));

}

void offFloor::update()
{
}

void offFloor::draw()
{
   // ofEnableDepthTest();				//Enable z-buffering
    
    cam.begin();
    //Set a gradient background from white to gray
   // ofBackgroundGradient( ofColor( 255 ), ofColor( 128 ) );
    //draw x/y/z axis
    ofSetLineWidth(5);
    ofSetColor(255, 0, 0);
    ofLine(0, 0, 200, 0);
    ofSetColor(0, 255, 0);
    ofLine(0, 0, 0, 200);
    ofSetColor(0, 0, 255);
    ofLine(0, 0, 0, 0, 0, 200);
    amb.enable();
    ofPushMatrix();						//Store the coordinate system
    
    //Move the coordinate center to screen's center
    //ofTranslate( ofGetWidth()/2, ofGetHeight()/2, 0 );
    
    //Calculate the rotation angle
    float time = ofGetElapsedTimef();   //Get time in seconds
    float angle = time * 20;			//Compute angle. We rotate at speed
    //20 degrees per second
   // ofRotate( 30, 1, 0, 0 );			//Rotate coordinate system
    //ofRotate( angle, 0, 0, 1 );
    
    //Draw mesh
    //Here ofSetColor() does not affects the result of drawing,
    //because the mesh has its own vertices' colors
    //Calculate the rotation angle
      //Draw the triangles
    ofTranslate( -ofGetWidth()/2, -ofGetHeight()/2, 0 );

    tri.draw();
    
    ofPopMatrix();      //Restore the coordinate system
    cam.end();
    /*ofEnableDepthTest();				//Enable z-buffering
    
    //Set a gradient background from white to gray
    //for adding an illusion of visual depth to the scene
    ofBackgroundGradient( ofColor( 255 ), ofColor( 128 ) );
    
    ofPushMatrix();						//Store the coordinate system
    
    //Move the coordinate center to screen's center
    ofTranslate( ofGetWidth()/2, ofGetHeight()/2, 0 );
    
    //Calculate the rotation angle
    float time = ofGetElapsedTimef();	//Get time in seconds
    float angle = time * 10;			//Compute angle. We rotate at speed 10 degrees per second
    ofRotate( angle, 0, 1, 0 );			//Rotate the coordinate system along y-axe
    
    //Draw the triangles
    for (int i=0; i<nTri; i++) {
        ofSetColor( colors[i] );		//Set color
        ofTriangle( vertices[ i*3 ],
                   vertices[ i*3 + 1 ],
                   vertices[ i*3 + 2 ] );		//Draw triangle
    }
    
    ofPopMatrix();	//Restore the coordinate system
     */
}

void offFloor::setLightOri(ofLight &light, ofVec3f rot)
{
    ofVec3f xax(1, 0, 0);
    ofVec3f yax(0, 1, 0);
    ofVec3f zax(0, 0, 1);
    ofQuaternion q;
    q.makeRotate(rot.x, xax, rot.y, yax, rot.z, zax);
    light.setOrientation(q);
}
//--------------------------------------------------------------
//Universal function which sets normals for the triangle mesh
void offFloor::setNormals( ofMesh &mesh ){
    
    //The number of the vertices
    int nV = mesh.getNumVertices();
    
    //The number of the triangles
    int nT = mesh.getNumIndices() / 3;
    
    vector<ofPoint> norm( nV ); //Array for the normals
    
    //Scan all the triangles. For each triangle add its
    //normal to norm's vectors of triangle's vertices
    for (int t=0; t<nT; t++) {
        
        //Get indices of the triangle t
        int i1 = mesh.getIndex( 3 * t );
        int i2 = mesh.getIndex( 3 * t + 1 );
        int i3 = mesh.getIndex( 3 * t + 2 );
        
        //Get vertices of the triangle
        const ofPoint &v1 = mesh.getVertex( i1 );
        const ofPoint &v2 = mesh.getVertex( i2 );
        const ofPoint &v3 = mesh.getVertex( i3 );
        
        //Compute the triangle's normal
        ofPoint dir = ( (v2 - v1).crossed( v3 - v1 ) ).normalized();
        
        //Accumulate it to norm array for i1, i2, i3
        norm[ i1 ] += dir;
        norm[ i2 ] += dir;
        norm[ i3 ] += dir;
    }
    
    //Normalize the normal's length
    for (int i=0; i<nV; i++) {
        norm[i].normalize();
    }
    
    //Set the normals to mesh
    mesh.clearNormals();
    mesh.addNormals( norm );
}
