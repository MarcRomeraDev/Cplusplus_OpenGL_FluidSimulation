#pragma once
#include <glm/glm.hpp> 
#include <glm/vec3.hpp>

static float Pitagoras(float x, float y)
{
	return glm::sqrt(glm::pow(x, 2) + glm::pow(y, 2));
}