#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy {
public:
    Enemy() {}
    Enemy(float x, float y, float z, color_t color, float rotation, glm::vec3 vec);
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
};

#endif // ENEMY_H
