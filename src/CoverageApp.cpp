
#include <string>

#include "cinder/CinderImGui.h"

#include "CoverageApp.h"

CoverageApp::CoverageApp() {

	m_tags.push_back({ 593.68, 9.68, 53.38, 120.0}); // 1
	m_tags.push_back({637.21, 34.79, 53.38, 120.0}); // 2
	m_tags.push_back({652.73, 196.17, 57.13, 180.0}); // 3
	m_tags.push_back({ 652.73, 218.42, 57.13, 180.0}); // 4
	m_tags.push_back({ 578.77, 323.0, 53.38, 270.0 }); // 5
	m_tags.push_back({ 72.5, 323.0, 53.38, 270.0 }); // 6
	m_tags.push_back({ -1.5, 218.42, 57.13, 0.0 }); // 7
	m_tags.push_back({ -1.5, 196.17, 57.13, 0.0}); // 8
	m_tags.push_back({ 14.02, 34.79, 53.38, 60.0 }); // 9
	m_tags.push_back({ 57.54, 9.68, 53.38, 60.0 }); // 10
	m_tags.push_back({ 468.69, 146.19, 52.0, 300.0 }); // 11
	m_tags.push_back({ 468.69, 177.1, 52.0, 60.0 }); // 12
	m_tags.push_back({ 441.74, 161.62, 52.0, 180.0 }); // 13
	m_tags.push_back({ 209.48, 161.62, 52.0, 0.0 }); // 14
	m_tags.push_back({ 182.73, 177.1, 52.0, 120.0}); // 15
	m_tags.push_back({ 182.73, 146.19, 52.0, 240.0}); // 16

	generateMaps();
}

void CoverageApp::setup() {

	auto img = loadImage(loadAsset("field.png"));
	m_fieldTex = ci::gl::Texture2d::create(img);

	setWindowSize({ img.get()->getWidth(), img.get()->getHeight() });

	ImGui::Initialize();
}

void CoverageApp::update() {

	ImGui::Begin("Coverage Finder");

	
	bool changed = ImGui::DragFloat("Camera Tilt", &m_cameraTilt);

	ImGui::Separator();
	ImGui::Checkbox("Speaker", &m_showSpeaker);
	ImGui::Checkbox("Stage", &m_showStage);
	ImGui::Checkbox("Source", &m_showSource);
	ImGui::Checkbox("Amp", &m_showAmp);

	ImGui::End();

	if (changed) {
		generateMaps();
	}
}

void CoverageApp::draw() {
	ci::gl::clear();

	ci::gl::setMatricesWindow(getWindowSize());
	//ci::gl::enableAlphaBlending();

	ci::gl::color(ci::Color(1.0, 1.0, 1.0));
	ci::gl::draw(m_fieldTex);

	ci::gl::translate({ 0.0, getWindowSize().y });
	ci::gl::scale(getWindowSize().x / FIELD_WIDTH, getWindowSize().y / FIELD_HEIGHT);

	std::vector<int> tags;
	if (m_showSpeaker) {
		tags.push_back(3);
		tags.push_back(4);
		tags.push_back(6);
		tags.push_back(7);
	}
	if (m_showStage) {
		tags.push_back(10);
		tags.push_back(11);
		tags.push_back(12);
		tags.push_back(13);
		tags.push_back(14);
		tags.push_back(15);
	}
	if (m_showSource) {
		tags.push_back(0);
		tags.push_back(1);
		tags.push_back(8);
		tags.push_back(9);
	}
	if (m_showAmp) {
		tags.push_back(4);
		tags.push_back(5);
	}

	for (int tag : tags) {
	//int tag = 3;
		ci::gl::color(ci::ColorA(ci::CM_HSV, double(tag) / m_tags.size(), 1, 1, 0.2));
		for (int row = 0; row < m_coverageGrids[tag].size(); row++) {
			for (int col = 0; col < m_coverageGrids[tag][row].size(); col++) {
				if (m_coverageGrids[tag][row][col]) {
					ci::gl::pushModelMatrix();
					ci::gl::translate({col * GRID_SIZE, -row * GRID_SIZE });
					float halfSquare = GRID_SIZE / 2.0;
					ci::gl::drawSolidRect(ci::Rectf({-halfSquare, -halfSquare}, { halfSquare, halfSquare}));
					ci::gl::popModelMatrix();
				}
			}
		}
	}

}

void CoverageApp::generateMaps() {
	m_coverageGrids.clear();
	for (int tag = 0; tag < m_tags.size(); tag++) {
		Grid coverageGrid;
		for (int row = 0; row < coverageGrid.size(); row++) {
			for (int col = 0; col < coverageGrid[row].size(); col++) {
				coverageGrid[row][col] = isCovered({ col * GRID_SIZE, row * GRID_SIZE, CAMERA_HEIGHT }, m_tags[tag]);
			}
		}
		m_coverageGrids.push_back(coverageGrid);
	}
}

bool CoverageApp::isCovered(glm::vec3 cameraPos, glm::vec4 tagPos) {
	glm::vec3 tagPosOnly = { tagPos.x, tagPos.y, tagPos.z };
	if (glm::length(cameraPos - tagPosOnly) > MAX_RANGE) {
		return false;
	}
	glm::vec2 tag2D = { tagPos.x, tagPos.y };
	glm::vec2 camera2D = { cameraPos.x, cameraPos.y };
	glm::vec2 diff = camera2D - tag2D;
	float highestZ = glm::length(diff)* tan((m_cameraTilt + CAMERA_VERTICAL_FOV / 2.0) * DEG2RAD) + CAMERA_Z;
	if (tagPos.z + 3.0 > highestZ) {
		return false;
	}
	//double camAngle = atan2f(diff.y, diff.x) * RAD2DEG;
	//if (camAngle < 0) {
	//	if (camAngle < -90) {
	//		camAngle = 360 - abs(camAngle);
	//	} else {
	//		camAngle = abs(camAngle);
	//	}
	//}
	float theta = tagPos.w * DEG2RAD;
	float x = diff.x * cos(theta) + diff.y * sin(theta);
	float y = -diff.x * sin(theta) + diff.y * cos(theta);

	if (abs(atan2f(y, x) * RAD2DEG) > 30) {
		return false;
	}
	return true;
}