/*
 *  ofxDelaunay.h
 *
 *  Created by Pat Long on 29/10/09.
 *  Copyright 2009 Tangible Interaction. All rights reserved.
 *
 *  Some parts based on demo code by Gilles Dumoulin. 
 *  Source: http://local.wasp.uwa.edu.au/~pbourke/papers/triangulate/cpp.zip
 *
 *	Cleaned up by Lukasz Karluk, 19/05/2010
 *
 *  Refactored for 0071 + ofMesh by James George on 21/06/2012
 */

#include "ofxDelaunay.h"

void ofxDelaunay::setupColors()
{
    /*for(int i = 0; i < 10; i++)
    {
        colors.push_back(ofColor(175 + ofRandom(-20,20),89+ ofRandom(-20,20),62+ ofRandom(-20,20)));
    }*/
    
    colors.push_back(ofColor(244,164,96	));
    colors.push_back(ofColor(255, 235, 205));
    colors.push_back(ofColor(255, 222, 173));
    colors.push_back(ofColor(238, 207, 161));
    colors.push_back(ofColor(205, 179, 139));
    colors.push_back(ofColor(139, 121, 94));
    colors.push_back(ofColor(252, 230, 201));
    colors.push_back(ofColor(210, 180, 140));
    colors.push_back(ofColor(156, 102, 31));

}
void ofxDelaunay::reset(){
    vertices.clear();
    triangles.clear();
	triangleMesh.clear();
}

int ofxDelaunay::addPoint( const ofPoint& point ){
	return addPoint( point.x, point.y, point.z );
}

int ofxDelaunay::addPoint( float x, float y, float z ){
    XYZ v;
    v.x = x;
    v.y = y;
    v.z = z;
    vertices.push_back(v);
	return vertices.size();
}

int ofxDelaunay::addPoints( vector<ofPoint>& points ){
	for(int i = 0; i < points.size(); i++){
        addPoint( points[i] );
    }
    return vertices.size();
}

int ofxDelaunay::triangulate(){
    
    if(vertices.size() < 3){
        return NULL;
    }
    
    int nv = vertices.size();
    //add 3 emptly slots, required by the Triangulate call
    vertices.push_back(XYZ());
    vertices.push_back(XYZ());
    vertices.push_back(XYZ());
    
    //allocate space for triangle indices
    triangles.resize(3*nv);
    
	int ntri;
	qsort( &vertices[0], vertices.size()-3, sizeof( XYZ ), XYZCompare );
	Triangulate( nv, &vertices[0], &triangles[0], ntri );
	
	// copy triangle data to ofxDelaunayTriangle.
	triangleMesh.clear();
    
    //copy vertices
	for (int i = 0; i < nv; i++){
        triangleMesh.addVertex(ofVec3f(vertices[i].x,vertices[i].y,vertices[i].z));
    }
    
    //copy triagles
	for(int i = 0; i < ntri; i++){
        
		triangleMesh.addIndex(triangles[ i ].p1);
		triangleMesh.addIndex(triangles[ i ].p2);
		triangleMesh.addIndex(triangles[ i ].p3);
        triangleMesh.addColor(colors[0]);//int(ofRandom(0,colors.size()-1))]);
	}
	
    //erase the last three triangles
    vertices.erase(vertices.end()-1);
    vertices.erase(vertices.end()-1);
    vertices.erase(vertices.end()-1);
    setNormals(triangleMesh);
	return ntri;
}

void ofxDelaunay::draw(){
	//if(ofGetStyle().bFill){
    triangleMesh.setMode(OF_PRIMITIVE_TRIANGLES);
	    triangleMesh.draw();
    //}
    //else{
    ofSetColor(0,0,0);
    	triangleMesh.drawWireframe();
    //}
}

void ofxDelaunay::setNormals( ofMesh &mesh )
{
    
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
