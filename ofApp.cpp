#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->font.loadFont("fonts/msgothic.ttc", 50, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	string word = "0123456789";
	ofColor color;

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.333333333333);
	ofRotateX(ofGetFrameNum() * 0.666666666666);

	ofNoFill();
	auto len = 200;
	for (int i = 0; i < 8; i++) {

		if (i < 4) {

			ofRotateX(90);
		}
		else if (i < 5) {

			ofRotateY(90);
		}
		else {

			ofRotateY(180);
		}

		for (int k = 0; k < 30; k++) {

			auto location = glm::vec3(ofRandom(-len * 0.5, len * 0.5), ofRandom(-len * 0.5, len * 0.5), len * 0.5);
			auto radius = (int)(ofRandom(1000) + ofGetFrameNum()) % 150 - 100;
			color.setHsb(ofRandom(255), 180, 255);

			auto angle = ofRandom(-PI * 2, PI * 2);
			auto rotation = glm::rotate(glm::mat4(), angle, glm::vec3(0, 0, 1));

			if (radius > 0) {

				ofSetColor(color, radius > 25 ? ofMap(radius, 25, 50, 255, 0) : 255);

				ofPath chara_path = this->font.getCharacterAsPoints(word[k % word.size()], true, false);
				vector<ofPolyline> outline = chara_path.getOutline();

				ofFill();
				ofBeginShape();
				for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

					ofNextContour(true);

					outline[outline_index] = outline[outline_index].getResampledByCount(60);
					vector<glm::vec3> vertices = outline[outline_index].getVertices();

					for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

						glm::vec3 vertex = location + glm::vec4(((vertices[vertices_index] - glm::vec2(25, -25)) / 50) * radius * 2, 0) * rotation;
						vertex.z += k;

						if (vertex.y > len * 0.5) { vertex.y = len * 0.5; }
						if (vertex.y < -len * 0.5) { vertex.y = -len * 0.5; }
						if (vertex.x > len * 0.5) { vertex.x = len * 0.5; }
						if (vertex.x < -len * 0.5) { vertex.x = -len * 0.5; }

						ofVertex(vertex);
					}
				}
				ofEndShape(true);

				ofSetColor(color, radius > 25 ? ofMap(radius, 25, 80, 32, 0) : 32);

				ofNoFill();
				ofBeginShape();
				for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

					ofNextContour(true);

					outline[outline_index] = outline[outline_index].getResampledByCount(60);
					vector<glm::vec3> vertices = outline[outline_index].getVertices();

					for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

						glm::vec3 vertex = location + glm::vec4(((vertices[vertices_index] - glm::vec2(25, -25)) / 50) * radius * 2, 0) * rotation;
						vertex.z += k;

						if (vertex.y > len * 0.5) { vertex.y = len * 0.5; }
						if (vertex.y < -len * 0.5) { vertex.y = -len * 0.5; }
						if (vertex.x > len * 0.5) { vertex.x = len * 0.5; }
						if (vertex.x < -len * 0.5) { vertex.x = -len * 0.5; }

						ofVertex(vertex);
					}
				}
				ofEndShape(true);
			}
		}

		ofSetColor(0);
		ofFill();
		ofDrawBox(len * 0.95);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}