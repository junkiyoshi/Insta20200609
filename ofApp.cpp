#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	int span = 20;
	for (int x = -180; x <= 180; x += span) {

		for (int y = -180; y <= 180; y += span) {

			for (int z = -180; z <= 180; z += span) {

				bool x_flag = x < -140 || x > 140;
				bool y_flag = y < -140 || y > 140;
				bool z_flag = z < -140 || z > 140;

				if (((x_flag || y_flag) && z_flag) || ((y_flag || z_flag) && x_flag)) {

					for (int tmp_x = -180; tmp_x <= 180; tmp_x += 360) {

						for (int tmp_y = -180; tmp_y <= 180; tmp_y += 360) {

							for (int tmp_z = -180; tmp_z <= 180; tmp_z += 360) {

								this->location_list.push_back(glm::vec3(x + tmp_x, y + tmp_y, z + tmp_z));
								this->colors_list.push_back(make_pair<ofColor, ofColor>(ofColor(39), ofColor(239, 39, 39)));
								this->param_list.push_back(0);
							}
						}
					}
				}
			}
		}
	}

	for (int x = -250; x <= 250; x += span) {

		for (int y = -250; y <= 250; y += span) {

			for (int z = -250; z <= 250; z += span) {

				bool x_flag = x < -180 || x > 180;
				bool y_flag = y < -180 || y > 180;
				bool z_flag = z < -180 || z > 180;

				if (((x_flag || y_flag) && z_flag) || ((y_flag || z_flag) && x_flag)) {

					this->location_list.push_back(glm::vec3(x, y, z));
					this->colors_list.push_back(make_pair<ofColor, ofColor>(ofColor(239, 39, 39), ofColor(39)));
					this->param_list.push_back(0);
				}
			}
		}
	}

	for (auto& location : this->location_list) {

		vector<int> route_info = vector<int>();
		int index = -1;
		for (auto& other : this->location_list) {

			index++;
			if (location == other) { continue; }

			float distance = glm::distance(location, other);
			if (distance <= span) {

				route_info.push_back(index);
			}
		}

		this->route_info_list.push_back(route_info);
	}

	for (int i = 0; i < 200; i++) {

		this->index_list.push_back((int)ofRandom(this->location_list.size()));
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->frame.clear();

	for (int i = 0; i < this->index_list.size(); i++) {

		int tmp_index = (int)ofRandom(this->route_info_list[this->index_list[i]].size());
		for (int k = 0; k < this->route_info_list[this->index_list[i]].size(); k++) {

			int next_index = this->route_info_list[this->index_list[i]][(tmp_index + k) % this->route_info_list[this->index_list[i]].size()];
			if (this->param_list[next_index] <= 0) {

				this->param_list[next_index] = 60;
				this->index_list[i] = next_index;
				break;
			}
		}
	}

	for (int i = 0; i < this->location_list.size(); i++) {

		if (this->param_list[i] > 0) {

			this->setBoxToMesh(this->face, this->frame, this->location_list[i], 20, this->colors_list[i]);
		}

		if (this->param_list[i] > 0) { this->param_list[i] -= 1; }
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.55);
	ofRotateX(ofGetFrameNum() * 0.35);

	ofSetColor(239);
	this->face.draw();

	ofSetColor(39);
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::setBoxToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float size, pair<ofColor, ofColor> colors) {

	this->setBoxToMesh(face_target, frame_target, location, size, size, size, colors);
}

//--------------------------------------------------------------
void ofApp::setBoxToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float height, float width, float depth, pair<ofColor, ofColor> colors) {

	int face_index = face_target.getNumVertices();
	int frame_index = frame_target.getNumVertices();

	face_target.addVertex(location + glm::vec3(width * -0.5 * 0.99, height * 0.5 * 0.99, depth * -0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * 0.5 * 0.99, height * 0.5 * 0.99, depth * -0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * 0.5 * 0.99, height * 0.5 * 0.99, depth * 0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * -0.5 * 0.99, height * 0.5 * 0.99, depth * 0.5 * 0.99));

	face_target.addVertex(location + glm::vec3(width * -0.5 * 0.99, height * -0.5 * 0.99, depth * -0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * 0.5 * 0.99, height * -0.5 * 0.99, depth * -0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * 0.5 * 0.99, height * -0.5 * 0.99, depth * 0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * -0.5 * 0.99, height * -0.5 * 0.99, depth * 0.5 * 0.99));

	face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 1); face_target.addIndex(face_index + 2);
	face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 2); face_target.addIndex(face_index + 3);

	face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 6);
	face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 6); face_target.addIndex(face_index + 7);

	face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 1);
	face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 1);

	face_target.addIndex(face_index + 1); face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 6);
	face_target.addIndex(face_index + 6); face_target.addIndex(face_index + 2); face_target.addIndex(face_index + 1);

	face_target.addIndex(face_index + 2); face_target.addIndex(face_index + 6); face_target.addIndex(face_index + 7);
	face_target.addIndex(face_index + 7); face_target.addIndex(face_index + 3); face_target.addIndex(face_index + 2);

	face_target.addIndex(face_index + 3); face_target.addIndex(face_index + 7); face_target.addIndex(face_index + 4);
	face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 3);

	frame_target.addVertex(location + glm::vec3(width * -0.5, height * 0.5, depth * -0.5));
	frame_target.addVertex(location + glm::vec3(width * 0.5, height * 0.5, depth * -0.5));
	frame_target.addVertex(location + glm::vec3(width * 0.5, height * 0.5, depth * 0.5));
	frame_target.addVertex(location + glm::vec3(width * -0.5, height * 0.5, depth * 0.5));

	frame_target.addVertex(location + glm::vec3(width * -0.5, height * -0.5, depth * -0.5));
	frame_target.addVertex(location + glm::vec3(width * 0.5, height * -0.5, depth * -0.5));
	frame_target.addVertex(location + glm::vec3(width * 0.5, height * -0.5, depth * 0.5));
	frame_target.addVertex(location + glm::vec3(width * -0.5, height * -0.5, depth * 0.5));

	frame_target.addIndex(frame_index + 0); frame_target.addIndex(frame_index + 1);
	frame_target.addIndex(frame_index + 1); frame_target.addIndex(frame_index + 2);
	frame_target.addIndex(frame_index + 2); frame_target.addIndex(frame_index + 3);
	frame_target.addIndex(frame_index + 3); frame_target.addIndex(frame_index + 0);

	frame_target.addIndex(frame_index + 4); frame_target.addIndex(frame_index + 5);
	frame_target.addIndex(frame_index + 5); frame_target.addIndex(frame_index + 6);
	frame_target.addIndex(frame_index + 6); frame_target.addIndex(frame_index + 7);
	frame_target.addIndex(frame_index + 7); frame_target.addIndex(frame_index + 4);

	frame_target.addIndex(frame_index + 0); frame_target.addIndex(frame_index + 4);
	frame_target.addIndex(frame_index + 1); frame_target.addIndex(frame_index + 5);
	frame_target.addIndex(frame_index + 2); frame_target.addIndex(frame_index + 6);
	frame_target.addIndex(frame_index + 3); frame_target.addIndex(frame_index + 7);

	for (int i = 0; i < 8; i++) {

		face_target.addColor(colors.first);
		frame_target.addColor(colors.second);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}