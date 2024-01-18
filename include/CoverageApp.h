#pragma once

#include <vector>
#include <array>

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>

#define PI 3.1415
#define DEG2RAD (PI / 180.0)
#define RAD2DEG 1.0 / DEG2RAD

#define GRID_SIZE (8.0)
#define FIELD_WIDTH (54.0 * 12 + 1)
#define FIELD_HEIGHT (27.0 * 12 + 7)
#define CAMERA_HEIGHT (10.0)
#define MAX_RANGE (15.0 * 12)
#define CAMERA_VERTICAL_FOV 49.0
#define CAMERA_Z 10.0

typedef std::array<std::array<bool, int(FIELD_WIDTH / GRID_SIZE) + 1>, int(FIELD_HEIGHT / GRID_SIZE) + 1> Grid;

class CoverageApp : public ci::app::App {
public:

	CoverageApp();

	void setup() override;
	void update() override;
	void draw() override;

private:

	void generateMaps();
	bool isCovered(glm::vec3 cameraPos, glm::vec4 tagPos);

	std::vector<glm::vec4> m_tags;
	std::vector<Grid> m_coverageGrids;

	ci::gl::Texture2dRef m_fieldTex;

	float m_cameraTilt {20};

	bool m_showSpeaker{ true };
	bool m_showStage{ true };
	bool m_showSource{ true };
	bool m_showAmp{ true };

};

CINDER_APP(CoverageApp, ci::app::RendererGl)