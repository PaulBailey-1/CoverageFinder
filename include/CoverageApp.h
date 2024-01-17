#pragma once

#include <vector>

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>

#define GRID_SIZE 1.0
#define FIELD_WIDTH 54 + 1 / 12.0
#define FIELD_HEIGHT 27 + 7 / 12.0

class CoverageApp : public ci::app::App {
public:

	CoverageApp();

	void setup() override;
	void draw() override;

private:

	bool isCovered(glm::vec3 cameraPos, glm::vec3 cameraPos);

	std::array<std::array<bool, floor(FIELD_HEIGHT / GRID_SIZE)>, floor(FIELD_HEIGHT / GRID_SIZE)> m_coverageGrid;

};

CINDER_APP(CoverageApp, ci::app::RendererGl)