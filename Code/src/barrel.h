#include "main.h"

#ifndef BARREL_H
#define BARREL_H


class Barrel
{
public:
    Barrel(){}
    Barrel (float x, float y, float z, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BARREL_H
