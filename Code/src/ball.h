#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float z, color_t color, float rotation, glm::vec3 vec);
    glm::vec3 position, vec;
    float rotation;
    int health;
    int damage;
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
};

#endif // BALL_H
