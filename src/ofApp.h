#pragma once

#include "ofMain.h"
#include "Polyline.h"
#include "Circle.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
    
    vector<Polyline> polylines;
    int buttonPos; //マウスのボタン位置
    int count; //現在の線のかたまり数
    int vertexNum; //頂点数
    void deletePos();
    
    ofImage myImage;
    float dist, radius, initTime;
    Circle circle;
    
    // gui
    ofxPanel gui;
    ofParameterGroup parameters;
    ofParameter<float> lineWidth;
    ofParameter<bool> bWire;
    ofParameter<bool> bGradation;
    ofParameterGroup linecap;
    ofParameter<bool> capParameter[3];
    ofParameterGroup linejoin;
    ofParameter<bool> joinParameter[3];
    ofParameterGroup color;
    ofParameter<ofColor> backColor;
    ofParameter<ofColor> color1;
    ofParameter<ofColor> color2;
    ofParameter<ofColor> color3;
    
    void setGui();
    void setLineCap();
    void checkLineCap();
    int cap, join;
    bool bHide, check[3], jcheck[3];
    void setLineJoin();
    void checkLineJoin();
    ofTrueTypeFont font;
};
