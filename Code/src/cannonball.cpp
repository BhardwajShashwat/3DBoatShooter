#include "cannonball.h"
#include "main.h"

Cannonball::Cannonball(float x, float y, float z, color_t color, glm::vec3 vec) {
    this->vec = vec;
    this->position = glm::vec3(x, y, z);
    this->speed_x = this->vec.x;
    this->speed_z = this->vec.z;
    this->speed_y = 0;
    static const GLfloat vertex_buffer_data[] = {
        //Head begin
        -0.5f, 1.0f,-0.5f,
        -0.5f, 1.0f, 0.5f,
        -0.5f, 1.5f, 0.5f,
         0.5f, 1.5f,-0.5f,
        -0.5f, 1.0f,-0.5f,
        -0.5f, 1.5f,-0.5f,
         0.5f, 1.0f, 0.5f,
        -0.5f, 1.0f,-0.5f,
         0.5f, 1.0f,-0.5f,
         0.5f, 1.5f,-0.5f,
         0.5f, 1.0f,-0.5f,
        -0.5f, 1.0f,-0.5f,
        -0.5f, 1.0f,-0.5f,
        -0.5f, 1.5f, 0.5f,
        -0.5f, 1.5f,-0.5f,
         0.5f, 1.0f, 0.5f,
        -0.5f, 1.0f, 0.5f,
        -0.5f, 1.0f,-0.5f,
        -0.5f, 1.5f, 0.5f,
        -0.5f, 1.0f, 0.5f,
         0.5f, 1.0f, 0.5f,
         0.5f, 1.5f, 0.5f,
         0.5f, 1.0f,-0.5f,
         0.5f, 1.5f,-0.5f,
         0.5f, 1.0f,-0.5f,
         0.5f, 1.5f, 0.5f,
         0.5f, 1.0f, 0.5f,
         0.5f, 1.5f, 0.5f,
         0.5f, 1.5f,-0.5f,
        -0.5f, 1.5f,-0.5f,
         0.5f, 1.5f, 0.5f,
        -0.5f, 1.5f,-0.5f,
        -0.5f, 1.5f, 0.5f,
         0.5f, 1.5f, 0.5f,
        -0.5f, 1.5f, 0.5f,
         0.5f, 1.0f, 0.5f,
    };

        this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color, GL_FILL);
    }

void Cannonball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    //glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Cannonball::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

bounding_box_t Cannonball::bounding_box() {
    float x = this->position.x, z = this->position.z;
    bounding_box_t bbox = { x, z, 1, 1 };
    return bbox;
}

void Cannonball::tick() {
    //this->rotation += speed;
     this->position.x += speed_x;
     this->position.z += speed_z;
}
