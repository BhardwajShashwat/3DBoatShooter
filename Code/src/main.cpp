#include "main.h"
#include "timer.h"
#include "ball.h"
#include "ground.h"
#include "rock.h"
#include "cannonball.h"
#include "enemy.h"
#include "enemy2.h"
#include "barrel.h"
#include "boost1.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Cannonball cannonball1, cannonball2;
Ground sea;
Rock rock[4];
Enemy enemy;
Enemy2 boss;
int toggle=0;
char Health[1000];
int i;
glm::vec3 aim, unit_aim;
Barrel barrel[4];
Boost1 boost1[2];

double xpos,ypos,y1pos,x1pos;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle_x = 0;
float camera_rotation_angle_y = 0;
float mag=10;
int cam_flag=5;
int project=2;
int cannon1=0;
int cannon2=0;
int bossflag=0;
int count=0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    //glm::vec3 eye ( 10*cos(camera_rotation_angle_x * M_PI/180.0f), 10*sin(camera_rotation_angle_y * M_PI/180.0f), 10*sin(camera_rotation_angle_x * M_PI/180.0f) );
    glm::vec3 eye ( 10*sin(camera_rotation_angle_x * M_PI/180.0f) , 10*sin(camera_rotation_angle_y * M_PI/180.0f), 10*cos(camera_rotation_angle_x * M_PI/180.0f) );
    //eye = glm::vec3(0, 5, 5);
    //printf("%f,%f,%f\n",eye.x, eye.y, eye.z);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    if(cam_flag==1)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        eye = ball1.position +2.0f*ball1.vec + glm::vec3(0,2,0);
        target = ball1.position +5.0f*ball1.vec;
    }

    if(cam_flag==2)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        eye= ball1.position +  glm::vec3 (0, 15, 0);
        target = ball1.position;
        up = glm::vec3(0,0,-1);
    }

    if(cam_flag==3)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        eye = glm::vec3(0, 15, 15);
        target = glm::vec3(0,0,0);
    }

    if(cam_flag==4)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        eye= ball1.position - 4.0f*ball1.vec + glm::vec3(0,4,0);
        target = ball1.position;
    }

    if(cam_flag==5)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
       // eye = ball1.position+  glm::vec3( 10*sin(camera_rotation_angle_x * M_PI/180.0f) , 10*sin(camera_rotation_angle_y * M_PI/180.0f), 10*cos(camera_rotation_angle_x * M_PI/180.0f) );
        eye = ball1.position+  glm::vec3( mag*sin(camera_rotation_angle_x * M_PI/180.0f) , mag*sin(camera_rotation_angle_y * M_PI/180.0f), mag*cos(camera_rotation_angle_x * M_PI/180.0f) );

        target=ball1.position;
    }


    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    ball1.draw(VP);
    sea.draw(VP);
    for(i=0;i<4;i++)rock[i].draw(VP);
    enemy.draw(VP);
    for(i=0;i<2;i++)boost1[i].draw(VP);

    for(i=0;i<4;i++)
    {
        barrel[i].draw(VP);
    }

    if(cannon1==1){
        cannonball1.draw(VP);
        //printf("%f,%f\n", cannonball1.speed_x, cannonball1.speed_z);
    }

    if(cannon2==1){
        cannonball2.draw(VP);
        //printf("%f,%f\n", cannonball1.speed_x, cannonball1.speed_z);
    }

    if(bossflag==1)
    {
        boss.draw(VP);
    }
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int f  = glfwGetKey(window, GLFW_KEY_F);


    /*int w  = glfwGetKey(window, GLFW_KEY_W);
    int s  = glfwGetKey(window, GLFW_KEY_S);
    int a  = glfwGetKey(window, GLFW_KEY_A);
    int d  = glfwGetKey(window, GLFW_KEY_D);
    */



    int o  = glfwGetKey(window, GLFW_KEY_O);
    int p  = glfwGetKey(window, GLFW_KEY_P);

    int boat = glfwGetKey(window, GLFW_KEY_1);
    int top = glfwGetKey(window, GLFW_KEY_2);
    int tower = glfwGetKey(window, GLFW_KEY_3);
    int follow_cam = glfwGetKey(window, GLFW_KEY_4);
    int helicopter = glfwGetKey(window, GLFW_KEY_5);

    int jump = glfwGetKey(window, GLFW_KEY_SPACE);

    if(o)
    {
        project=1;
        reset_screen();
    }

    if(p)
    {
        project=2;
        reset_screen();
    }

    if (boat) {
        cam_flag=1;
    }

    if(top)
    {
        cam_flag=2;
    }

    if(tower)
    {
        cam_flag=3;
    }

    if(follow_cam)
    {
        cam_flag=4;
    }
    if(helicopter)
    {
        cam_flag=5;

    }

   /* if(cam_flag==5)
    {
        if (a) {
            camera_rotation_angle_x -= 1;
        }

        if(d){
            camera_rotation_angle_x += 1;
        }

        if(w){
            camera_rotation_angle_y -= 1;
        }

        if(s){
         camera_rotation_angle_y += 1;
        }
    }*/

    if(left){
        ball1.rotation+=3;
    }


    if(right){
        ball1.rotation-=3;
    }

    if(up)
    {
        ball1.speed_z = ball1.vec.z;
        ball1.speed_x = ball1.vec.x;
    }

    if(down)
    {
        ball1.speed_z = -ball1.vec.z;
        ball1.speed_x = -ball1.vec.x;
    }

    if(jump)
    {
         if(ball1.position.y<=1)ball1.speed_y = 2;
    }

    if(f)//if(f && cannon1==0)
    {
        cannon1=1;
        cannonball1 = Cannonball(ball1.position.x,ball1.position.y,ball1.position.z,COLOR_BLACK, ball1.vec);
    }
}

void tick_elements() {
    ball1.tick();
    cannonball1.tick();
    cannonball2.tick();
    enemy.tick();

        if(ball1.position.x-enemy.position.x<=20 && ball1.position.x-enemy.position.x>=-20 && ball1.position.z-enemy.position.z<=20 && ball1.position.z-enemy.position.z>=-20 )
        {
            enemy.vec=ball1.position-enemy.position;
            enemy.speed_x=enemy.vec.x*0.04f;
            enemy.speed_z=enemy.vec.z*0.04f;
        }
        else
        {
            enemy.speed_x=0;
            enemy.speed_z=0;
        }


       for(i=0;i<4;i++)
       {
        if (detect_collision(ball1.bounding_box(), rock[i].bounding_box()))
        {
            while(detect_collision(ball1.bounding_box(), rock[i].bounding_box()))
            {
                ball1.position=ball1.position-ball1.vec;
            }
             ball1.health-=10;
        }
       }

       if (detect_collision(ball1.bounding_box(), enemy.bounding_box()))
       {
        while(detect_collision(ball1.bounding_box(), enemy.bounding_box()))
        {
            ball1.position=ball1.position+enemy.vec*0.5f;
        }
         ball1.health-=10;
       }


        if (detect_collision(cannonball1.bounding_box(), enemy.bounding_box()))
        {
            enemy = Enemy(1200,-1000,1200, COLOR_GREEN, 0, glm::vec3(0,0,0));
            bossflag=1;
            if(bossflag==1)boss= Enemy2(-60,0,-60, COLOR_RED, 0, glm::vec3(0,0,0));
        }


       /*if(cannonball1.position.x-ball1.position.x>30 || cannonball1.position.x-ball1.position.x<-30 || cannonball1.position.z-ball1.position.x>30 || cannonball1.position.z-ball1.position.x<-30 )
       {
            cannonball1 = Cannonball(100,-1000,100,COLOR_BLACK, glm::vec3(0,0,0));
            cannon1=0;
       }*/
       if(detect_collision(cannonball1.bounding_box(), boss.bounding_box()))
       {
           cannonball1 = Cannonball(100,-1000,100,COLOR_BLACK, glm::vec3(0,0,0));
           cannon1=0;
           boss.health-=ball1.damage;
       }
       for(i=0;i<4;i++)
       {
        if(detect_collision(cannonball1.bounding_box(), rock[i].bounding_box()))
        {
               cannonball1 = Cannonball(100,-1000,100,COLOR_BLACK, glm::vec3(0,0,0));
            cannon1=0;
        }
       }

       if(detect_collision(cannonball2.bounding_box(), ball1.bounding_box()))
       {
           cannonball1 = Cannonball(100,-1000,100,COLOR_BLACK, glm::vec3(0,0,0));
           ball1.health-=3;
       }


       if(bossflag==1)
       {
           //printf("Bossflag reached\n");
           count++;
           if(count%240==0)
           {
                printf("Shot reached\n");
                cannon2=1;
                aim=ball1.position-boss.position;
                unit_aim.x=aim.x/sqrt(aim.x*aim.x + aim.z*aim.z)*3;
                unit_aim.z=aim.z/sqrt(aim.x*aim.x + aim.z*aim.z)*3;
                cannonball2 = Cannonball(boss.position.x,boss.position.y,boss.position.z,COLOR_D_RED, unit_aim);
                //printf("%f,%f,%f\n",aim.x,aim.y,aim.z);

           }
           if(count>240)printf("%f,%f\n",cannonball2.speed_x, cannonball2.speed_z);
           boss.rotation+=4;
           if(boss.position.x>=40)toggle=0;
           if(boss.position.x<=-40) toggle=1;
           if(toggle==0)boss.position.x+=-0.1;
           if(toggle==1)boss.position.x+=0.1;
       }

       if(boss.health<=0)
       {
           bossflag=0;
         \
       }

       for(i=0;i<4;i++)
       {
           if(detect_collision(barrel[i].bounding_box(), ball1.bounding_box()))
           {
               barrel[i] = Barrel(100,-1000,100,COLOR_BROWN);
               if(i%2==0)
               {
                   ball1.health+=20;
               }
               else
               {
                   ball1.damage+=10;
               }
           }

       }
        for(i=0;i<2;i++)
        {
            if(detect_collision(boost1[i].bounding_box(), ball1.bounding_box()) && ball1.position.y<=0)
            {
                ball1.speed_y+=5;
                //boost1[i] = Boost1(100,-1000,100,COLOR_ORANGE);
            }
        }

        glfwGetCursorPos(window, &xpos,&ypos);
        if(x1pos>xpos)camera_rotation_angle_x += 3;
        if(x1pos<xpos)camera_rotation_angle_x -= 3;
        if(y1pos>ypos)camera_rotation_angle_y += 2;
        if(y1pos<ypos)camera_rotation_angle_y -= 2;
        if(camera_rotation_angle_y <= 25)camera_rotation_angle_y = 25;

        y1pos=ypos;
        x1pos=xpos;

        glfwSetScrollCallback(window, scroll_callback);

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1       = Ball(50, 0, 50, COLOR_RED, 0, glm::vec3(0, 0, -1));
    rock[0]        = Rock(35, 0, 50, COLOR_B_BLACK);
    rock[1]        = Rock(-35, 0, -50, COLOR_B_BLACK);
    rock[2]        = Rock(35, 0, -50, COLOR_B_BLACK);
    rock[3]        = Rock(-35, 0, 50, COLOR_B_BLACK);
    sea         = Ground(COLOR_OCEAN_BLUE);
    enemy       = Enemy(30,0, 30, COLOR_GREEN, 0, glm::vec3(0,0,0));
    barrel[0]   = Barrel(10, 0, 10, COLOR_BROWN);
    barrel[1]   = Barrel(-10, 0, 10, COLOR_BROWN);
    barrel[2]   = Barrel(10, 0, -10, COLOR_BROWN);
    barrel[3]   = Barrel(-10, 0, -10, COLOR_BROWN);
    boost1[0]   = Boost1(40, 0, 10, COLOR_ORANGE);
    boost1[1]   = Boost1(-40, 0, 10, COLOR_ORANGE);

    glfwGetCursorPos(window, &xpos, &ypos);
    x1pos=xpos;
    y1pos=ypos;


    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            if(ball1.health<=0)quit(window);
            tick_input(window);
            sprintf(Health, "Health: %d\t Attack: %d", ball1.health,ball1.damage);
            if(bossflag==1) sprintf(Health, "Health: %d \t Attack: %d \t\t\t\t\t\t\t Boss Health: %d", ball1.health,ball1.damage, boss.health);
            glfwSetWindowTitle(window,Health);
            printf("%d\n",bossflag);

        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 100 / screen_zoom;
    float bottom = screen_center_y - 100 / screen_zoom;
    float left   = screen_center_x - 100 / screen_zoom;
    float right  = screen_center_x + 100 / screen_zoom;
    if(project==1)Matrices.projection = glm::ortho(left, right, bottom, top, 0.05f, 500.0f);
    if(project==2)Matrices.projection = glm::perspective(90.0f, 1.0f, 0.05f, 500.0f);

}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    // Do something
    if(yoffset<0) mag=1.1*mag;
    if(mag>20)mag=20;
    if(mag<3)mag=3;
    if(yoffset>0) mag=mag/1.1;
    reset_screen();
}


