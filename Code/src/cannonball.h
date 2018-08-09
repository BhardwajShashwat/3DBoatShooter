#include "main.h"

#ifndef CANNONBALL_H
#define CANNONBALL_H


class Cannonball {
public:
    Cannonball() {}
    Cannonball(float x, float y, float z, color_t color, glm::vec3 vec);
    glm::vec3 position, vec;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed_x;
    double speed_y;
    double speed_z;
    bounding_box_t bounding_box();

private:
    VAO *object;
};

#endif // CANNONBALL_H
