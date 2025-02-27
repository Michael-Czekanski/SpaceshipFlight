#pragma once

#include "glew.h"
#include "freeglut.h"

#include "ScreenQuad.h"
#include "blur/Blur.h"
#include "hdr/HDRFramebuffer.h"

#include "../../utils/Texture.h"

class Bloom
{
public:
	Bloom(unsigned int windowWidth, unsigned int windowHeight, GLuint programBlur, GLuint programBloomFinalBlend);
	void beforeRendering();
	void afterRendering();

	void setExposure(float exp);
	float getExposure();

	void setGamma(float gamma);
	float getGamma();

	void setBlurAmount(int blurAmount);
	int getBlurAmount();
private:
	GLuint programBloomFinalBlend;
	float exposure;
	float gamma;
	ScreenQuad screenQuad;
	Blur blur;
	HDRFramebuffer hdrFramebuffer;

	void bloomBlend(GLuint sceneTexture, GLuint blurredBrightLightsTexture);
};

