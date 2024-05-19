#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    
    // Midi ports listing
    
    midi.listInPorts();
    midi.openPort("APC mini mk2 Notes");
    midi.openPort("APC mini mk2 Control");
    midi.addListener(this);
    
    // Setting the Mesh characteristics
    mainMesh.setMode(OF_PRIMITIVE_LINES);
    width = ofGetWidth();
    height = ofGetHeight();
    
    // Variables for parameters to be manipulated
    
    perlinHeight = 5.0;
    camXpos = 0;
    camYpos = 0;
    camZpos = 80;
    speed = 4;
    sb = 0;
    cb = 0;
    Recs = 3;
    Circs = 3;
    rad = 100;
    ofSetBackgroundColor(0, 0, 0);
    sW = 10;
    sH = 10;
    brightness = 0;
    invert = false;
    triangles_move = false;
    rand = false;
    ill = false;
    square_move = false;
    circs_move = false;
    mesh1 = false;
    meshD = false;
    square_2 = false;
    
  // Sets the x and y coordinates of the mesh
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            mainMesh.addVertex(ofPoint(x- width /2, y - height / 2,10));
        }
    }
    
    // For loop joins vertices together as indices to make triangles that make the wireframe grid
    for(int y = 0; y<height-1; y++){
        for(int x= 0; x <width-1; x++){
            mainMesh.addIndex(x+y*width);
            mainMesh.addIndex ((x+1)+y*width);
            mainMesh.addIndex(x+(y+1)*width);
            mainMesh.addIndex((x+1)+y*width);
            mainMesh.addIndex((x+1)+ (y+1)*width);
            mainMesh.addIndex(x+(y+1)*width);
        }
    }
    
    // Setting background color and camera position
    ofBackground(0);
    ofSetColor(255);
    mainCam.setPosition(camXpos,camYpos,camZpos);
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // Controls the brightness for the squares in the final section
    
    brightness += speed;
    if (brightness >= 255) {
        brightness = 255;
    }
    
    if (brightness < 0) {
        brightness = 0;
    }
    
    // Sets color for mesh
    ofColor newColor;
    
    // vector for mesh positions
    ofVec3f newPosition, oldPosition;
    

    ofSetColor(255);
    if(mesh1){
        for (int i = 0; i < mainMesh.getNumVertices(); i++){
            newPosition = mainMesh.getVertex(i);
            newPosition.z = ofRandom(-perlinHeight, perlinHeight);
            mainMesh.setVertex(i, newPosition);
        }
    }
    mainCam.setPosition(camXpos,camYpos,camZpos);
    
}
//--------------------------------------------------------------
void ofApp::draw(){
    
    mainCam.begin();
    
    // Statements to determine when the mesh is visible
    if(meshD == true){
        ofSetColor(0);
        ofBackground(255);
    }
    
    if(meshD == false){
        ofBackground(0);
    }
    
    if(meshD == true){
        mainMesh.drawWireframe();
    }
    mainCam.end();
    
    // Squares for first section
    ofSetColor(255,255,255);
    if(square_move == true){
        for(int i = 0; i < Recs; i++){
            float x = ofRandom(ofGetWidth());
            float y = ofRandom(ofGetHeight());
            ofDrawRectangle(x, y, sW, sH);
        }
    }
    
    // Squares last section
    ofSetColor(255, 255, 255,brightness);
    if(rand == true){
        for(int i = 0; i < 100; i++){
            ofDrawRectangle(xPos[i], yPos[i], 50, 50);
        }
    }
    
}
//--------------------------------------------------------------
void ofApp::exit(){
    midi.closePort();
    midi.removeListener(this);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

void ofApp::newMidiMessage(ofxMidiMessage &message){
    messages.push_back(message);
    
    // Midi Messages to control parameters using the Midi controller
    
    if(message.pitch == 56){
        square_move = true;
    }
    
    if(message.pitch == 48){
        square_move = false;
    }
    
    if(message.pitch == 57){
        sW += 5;
        sH += 5;
    }
    
    if(message.pitch == 49){
        sW -= 10;
        sH -= 10;        
    }
    
    if(message.pitch == 63){
        mesh1 = true;
    }
    
    if(message.pitch == 24){
        mesh1 = true;
        meshD = true;
        invert = true;
    }
    
    if(message.pitch == 16){
        mesh1 = false;
        meshD = false;
    }
    
    if(message.pitch == 25){
        camZpos -= 10;
    }
    
    if(message.pitch == 26){
        perlinHeight +=0.1;
    }
    
    if(message.pitch == 27){
        invert = true;
    }
    
    if(message.pitch == 19){
        invert = false;
    }
    
    if(message.pitch == 18){
        perlinHeight -=0.1;
    }
    
    if(message.pitch == 17){
        camZpos += 10;
    }
    
    if(message.pitch == 52){
        Recs += 1;
    }
    
    if(message.pitch == 58){
        Recs += 10;
    }
    
    if(message.pitch == 50){
        sW -= 10;
        sH -= 10;
        Recs -= 10;
    }
    
    if(message.pitch == 33){
        rad += 10;
    }
    
    if(message.pitch == 34){
        rad -= 10;
    }
    
    if(message.pitch == 35){
        circs_move = false;
    }
    
    if(message.pitch == 63){
        meshD = true;
        invert = true;
    }
    
    if(message.pitch == 55){
        meshD = false;
    }
    
    if(message.pitch == 40){
        triangles_move = true;
    }
    
    if(message.pitch == 32){
        triangles_move = false;
    }
    
    if(message.pitch == 26){
        triangles_move = false;
    }
    
    if(message.pitch == 0){
        rand = false;
    }
    
    if(message.status == MIDI_NOTE_ON && message.pitch == 8){
        rand = true;
        brightness = 0;
   
        // Moves the x and y positions by a random amount
        for(int i = 0; i < 100; i++){
            xPos[i] = ofRandom(0, ofGetWidth());
            yPos[i] = ofRandom(0, ofGetHeight());
        }
    }
    
    if(message.status == MIDI_NOTE_OFF && message.pitch == 8){
        rand = false;
    }
        
    if(messages.size() > 32){
        messages.erase(messages.begin());
    }
    
}


