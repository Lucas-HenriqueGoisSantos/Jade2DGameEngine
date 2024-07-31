#ifndef KEYBOARDCONTROLLEDCOMPONENT_H
#define KEYBOARDCONTROLLEDCOMPONENT_H


#include <glm/glm.hpp>


struct KeyboardContrelledComponent {

    glm::vec2 upVelocity;
    glm::vec2 rightVelocity;
    glm::vec2 downVelocity;
    glm::vec2 leftVelocity;

    KeyboardContrelledComponent() {

    }
};


#endif