#pragma once

#include <vector>

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>
#include <cinder/gl/gl.h>

class CoverageApp : public ci::app::App {
public:

	CoverageApp();

	void setup() override;
	void draw() override;

private:

	

};

CINDER_APP(CoverageApp, ci::app::RendererGl)