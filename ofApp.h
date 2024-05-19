#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

class ofApp : public ofBaseApp, public ofxMidiListener{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;
        void newMidiMessage(ofxMidiMessage &message);

		void keyPressed(int key) override;
		void keyReleased(int key) override;
		void mouseMoved(int x, int y ) override;
		void mouseDragged(int x, int y, int button) override;
		void mousePressed(int x, int y, int button) override;
		void mouseReleased(int x, int y, int button) override;
		void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
		void mouseEntered(int x, int y) override;
		void mouseExited(int x, int y) override;
		void windowResized(int w, int h) override;
		void dragEvent(ofDragInfo dragInfo) override;
		void gotMessage(ofMessage msg) override;
    
        ofxMidiIn midi;
        vector <ofxMidiMessage> messages;

        ofMesh mainMesh;
        ofEasyCam mainCam;
        ofSpherePrimitive sphere;
        ofMaterial material;
    
        int width,height,depth;
        bool mesh1;
        float perlinRange, perlinHeight;
        int camXpos, camYpos, camZpos;
        bool invert;
    
    float sb;
    float cb;
    int Recs;
    int Circs;
    int rad;
    bool ill;
    bool square_move;
    bool circs_move;
    bool meshD;
    bool triangles_move;
    bool rand;
    int sW;
    int sH;
    float brightness;
    int xPos[100];
    int yPos[100];
    bool maxBrightnessReached;
    float speed;
    bool square_2;


};
