#include "enemy2.h"
#include "main.h"

Enemy2::Enemy2(float x, float y, float z, color_t color, float rotation, glm::vec3 vec) {
    this->vec = vec;
    this->position = glm::vec3(x, y, z);
    this->rotation = rotation;
    this->health=100;
    this->speed_x = 0;
    this->speed_z = 0;
    this->speed_y = 0;
    //speed = 1;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    static const GLfloat vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f, //Body begins
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        //Body ends


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

        //Head
        -3.0f, 3.0f,-3.0f,
        -3.0f, 3.0f, 3.0f,
         0.0f,0.0f, 0.0f,

        -3.0f, 3.0f, 3.0f,
         3.0f, 3.0f, 3.0f,
         0.0f,0.0f, 0.0f,

         3.0f, 3.0f, 3.0f,
         3.0f, 3.0f, -3.0f,
         0.0f,0.0f, 0.0f,

         3.0f, 3.0f,-3.0f,
        -3.0f, 3.0f,-3.0f,
         0.0f, 0.0f, 0.0f,

        -3.0f, 3.0f,-3.0f,
        -3.0f, 3.0f, 3.0f,
         0.0f,8.0f, 0.0f,

        -3.0f, 3.0f, 3.0f,
         3.0f, 3.0f, 3.0f,
         0.0f,8.0f, 0.0f,

         3.0f, 3.0f, 3.0f,
         3.0f, 3.0f,-3.0f,
         0.0f,8.0f, 0.0f,

         3.0f, 3.0f,-3.0f,
        -3.0f, 3.0f,-3.0f,
         0.0f, 8.0f, 0.0f,



    };

    //this->object = create3DObject(GL_TRIANGLES, 96, vertex_buffer_data, color, GL_FILL);
    this->object = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data, COLOR_D_BLUE, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 36, &vertex_buffer_data[108], COLOR_PURPLE, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 12, &vertex_buffer_data[216], COLOR_B_BLACK, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 12, &vertex_buffer_data[252], COLOR_D_RED, GL_FILL);

}

void Enemy2::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
}

void Enemy2::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

bounding_box_t Enemy2::bounding_box() {
    float x = this->position.x, z = this->position.z;
    bounding_box_t bbox = { x, z, 6, 6 };
    return bbox;
}

void Enemy2::tick() {
    this->vec = glm::vec3(-sin(this->rotation * M_PI / 180.0f), 0 , -cos(this->rotation * M_PI / 180.0f));
    //this->rotation += speed;
    speed_x=speed_x/5;
    speed_z=speed_z/5;
    speed_y-=0.1;
     this->position.x += speed_x;
     this->position.z += speed_z;
     this->position.y += speed_y;
    if(this->position.y < 0)
    {
        this->position.y = 0;
        speed_y=0;
    }

}

