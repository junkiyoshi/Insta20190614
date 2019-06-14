#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	auto R = 300.f;
	auto r = 100.f;
	auto u = 0.f;
	auto u_step = 10.f;
	auto v_step = 5.f;
	ofColor color;

	for (int i = 0; i < 9; i++) {

		auto v_start = i * 20;
		vector<glm::vec3> vertices;
		for (auto v = v_start; v < v_start + 360; v += v_step) {

			vertices.clear();
			vertices.push_back(this->make_point(R, r, u, v));
			vertices.push_back(this->make_point(R, r, u + u_step, v + v_step));
			vertices.push_back(this->make_point(R, r, u, v + v_step));
			vertices.push_back(this->make_point(R, r, u - u_step, v));

			ofFill();
			ofSetColor(239);
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape(true);

			ofSetColor(39);
			ofDrawLine(this->make_point(R, r, u + 0.5, v), this->make_point(R, r, u + u_step + 0.5, v + v_step));
			ofDrawLine(this->make_point(R, r, u - 0.5, v + v_step), this->make_point(R, r, u - u_step - 0.5, v));

			u += u_step;
		}
	}

	auto frame_count = ofGetFrameNum();
	for (int i = 0; i < 30; i++) {

		auto tmp_r = ofRandom(20, r - 20);
		auto tmp_u = ofRandom(360) + frame_count * ofRandom(0.5, 1.0);
		auto tmp_v = ofRandom(360) + frame_count * ofRandom(0.5, 1.0);

		ofDrawSphere(this->make_point(R, tmp_r, tmp_u, tmp_v), 10);
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}