#pragma once

#include "glew.h"
#include "freeglut.h"
#include <iostream>

class BlurFramebuffer
{
public:
	BlurFramebuffer(unsigned int windowWidth, unsigned int windowHeight);
	unsigned int* getFBOs();
	unsigned int* getColorBuffers();
private:
	unsigned int FBOs[2];
	unsigned int colorBuffers[2];

	void checkIfFramebufferComplete();
};

