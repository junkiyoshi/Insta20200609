#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key) {};
	void keyReleased(int key) {};
	void mouseMoved(int x, int y) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void windowResized(int w, int h) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};

	void setBoxToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float size,  pair<ofColor, ofColor> colors);
	void setBoxToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float height, float width, float depth, pair<ofColor, ofColor> colors);

	ofEasyCam cam;
	ofMesh face, frame;

	vector<glm::vec3> location_list;
	vector<pair<ofColor, ofColor>> colors_list;
	vector<int> param_list;
	vector<vector<int>> route_info_list;

	vector<int> index_list;
};