#include "main.h"

#ifndef BOOST1_H
#define BOOST1_H


class Boost1
{
public:
    Boost1(){}
    Boost1 (float x, float y, float z, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BOOST1_H
