
#include <string>

#include "CoverageApp.h"

CoverageApp::CoverageApp() {
	m_validGrid.fill(false);
}

void CoverageApp::setup() {
}

void CoverageApp::draw() {
	ci::ColorA grey = ci::Color::gray(0.4);

	ci::gl::clear(grey);

	ci::gl::setMatricesWindow(getWindowSize());
	//ci::gl::enableAlphaBlending();

	float scale = getWindowSize().x / FIELD_WIDTH);
	ci::gl::scale(scale, scale);

	ci::gl::translate({20, 20});
	ci::gl::color(ci::Color(0, 1.0, 0));
	ci::gl::drawSolidRect(ci::Rectf({0, 0}, {1, 1}));

}

bool isCovered(glm::vec3 cameraPos, glm::vec3 cameraPos) {

}