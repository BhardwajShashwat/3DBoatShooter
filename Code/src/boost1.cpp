#include "boost1.h"
#include "main.h"

Boost1::Boost1(float x, float y, float z, color_t color)
{
    this->position = glm::vec3(x, y, z);

    static const GLfloat vertex_buffer_data[] = {
        //Raft
        -3.0f,-1.0f,-3.0f,
        -3.0f,-1.0f, 3.0f,
        -3.0f, 0.0f, 3.0f,
         3.0f, 0.0f,-3.0f,
        -3.0f,-1.0f,-3.0f,
        -3.0f, 0.0f,-3.0f,
         3.0f,-1.0f, 3.0f,
        -3.0f,-1.0f,-3.0f,
         3.0f,-1.0f,-3.0f,
         3.0f, 0.0f,-3.0f,
         3.0f,-1.0f,-3.0f,
        -3.0f,-1.0f,-3.0f,
        -3.0f,-1.0f,-3.0f,
        -3.0f, 0.0f, 3.0f,
        -3.0f, 0.0f,-3.0f,
         3.0f,-1.0f, 3.0f,
        -3.0f,-1.0f, 3.0f,
        -3.0f,-1.0f,-3.0f,
        -3.0f, 0.0f, 3.0f,
        -3.0f,-1.0f, 3.0f,
         3.0f,-1.0f, 3.0f,
         3.0f, 0.0f, 3.0f,
         3.0f,-1.0f,-3.0f,
         3.0f, 0.0f,-3.0f,
         3.0f,-1.0f,-3.0f,
         3.0f, 0.0f, 3.0f,
         3.0f,-1.0f, 3.0f,
         3.0f, 0.0f, 3.0f,
         3.0f, 0.0f,-3.0f,
        -3.0f, 0.0f,-3.0f,
         3.0f, 0.0f, 3.0f,
        -3.0f, 0.0f,-3.0f,
        -3.0f, 0.0f, 3.0f,
         3.0f, 0.0f, 3.0f,
        -3.0f, 0.0f, 3.0f,
         3.0f,-1.0f, 3.0f,
    };

    this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, color, GL_FILL);

}

void Boost1::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

bounding_box_t Boost1::bounding_box() {
    float x = this->position.x, z = this->position.z;
    bounding_box_t bbox = { x, z, 6, 6 };
    return bbox;
}


