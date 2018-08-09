#include "main.h"

#ifndef ROCK_H
#define ROCK_H


class Rock
{
public:
    Rock(){}
    Rock (float x, float y, float z, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // ROCK_H
