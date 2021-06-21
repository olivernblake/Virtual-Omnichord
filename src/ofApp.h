#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "OSCReceiver.h"
#include "DrawBoxes.h"
#include "DrawHarp.h"
#include "BubbleSystem.h"
#include "Bubble.h"
#include "Beam.h"
#include "ofxMaxim.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();
        void updateTrigNum();
        void updateModes();
        void drawInstructions();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    // Webcam Vars
    ofVideoGrabber vidGrabber;
    ofImage currentFrame;
    
    // Draw Boxes and Harp;
    DrawBoxes drawBoxes;
    DrawHarp drawHarp;
    
    // OSC Stuff;
    OSCReceiver oscRec;
    
    // Wood/Space and Sin/Saw;
    bool woodMode, spaceMode;
    bool sin, saw;
    int modeNum;
    
    ofBitmapFont text;
    bool drawInst;
};
