#include "../../../../headers/graphics_techniques/bloom/blur/Blur.h"

Blur::Blur(unsigned int windowWidth, unsigned int windowHeight, GLuint programBlur):
	blurAmount(40), programBlur(programBlur), blurFramebuffer(windowWidth, windowHeight)
{
}

GLuint Blur::blur(ScreenQuad screenQuad, GLuint brightLightsTexture)
{
    bool horizontal = true, first_iteration = true;
    int amount = blurAmount;
    glUseProgram(programBlur);
    for (unsigned int i = 0; i < amount; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, blurFramebuffer.getFBOs()[horizontal]);
        glUniform1i(glGetUniformLocation(programBlur, "horizontal"), horizontal);
        glBindTexture(
            GL_TEXTURE_2D, first_iteration ? brightLightsTexture : blurFramebuffer.getColorBuffers()[!horizontal]
        );
        screenQuad.render();
        horizontal = !horizontal;
        if (first_iteration)
            first_iteration = false;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return blurFramebuffer.getColorBuffers()[0];
}

void Blur::setBlurAmount(int blurAmount)
{
    this->blurAmount = blurAmount;
}

int Blur::getBlurAmount()
{
    return blurAmount;
}
