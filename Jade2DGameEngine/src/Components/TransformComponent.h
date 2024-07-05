#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <glm/glm.hpp>

struct TranformComponent {
	glm::vec2 position;
	glm::vec2 scale;
	double rotation;
};

#endif // TRANSFORMCOMPONENT_H