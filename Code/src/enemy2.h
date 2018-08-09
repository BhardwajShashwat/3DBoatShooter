#include "main.h"

#ifndef ENEMY2_H
#define ENEMY2_H


class Enemy2 {
public:
    Enemy2() {}
    Enemy2(float x, float y, float z, color_t color, float rotation, glm::vec3 vec);
    glm::vec3 position, vec;
    float rotation;
    int health;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    double speed_x;
    double speed_y;
    double speed_z;
    bounding_box_t bounding_box();

private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif // ENEMY2_H
