#include "objectsInSpace/renderables/orbitables/Moon.h"

Moon::Moon(glm::vec3 position, const RenderData &renderData,
	glm::vec3 scale, Planet* orbitAround, glm::vec3 orbitPlaneVec2, float orbitSpeed, GLuint programDraw, TextureData textureData):
	Orbitable(position, renderData, scale, orbitAround, orbitPlaneVec2, orbitSpeed, programDraw, textureData)
{
}
