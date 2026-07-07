// bunch of OpenGL libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp> //math library

#include <iostream>
#include <vector>
#include <cmath> //need sqrt() and probably trig functions.

/*classes*/
class BlackHole{
public:

//variables 
float mass=0.1;

float radius=2*mass; //schwarzschild radius(radius of a black hole is 2x of it's mass)

//draw the circle for the hole
void DrawCircle() {
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(0,0,0);//black Color
        glVertex2f(0,0);//center

        //draw 100 segments for a smooth circle
        for (int i=0;i<=100;i++) {
            float angle =2*3.14159265*(float)i /100;
            float x = cos(angle) * radius;
            float y = sin(angle) * radius;
            glVertex2f(x, y);
        }
        glEnd();
    }
};

class Rays{
public:

//declaring 2d vector variables for position and directon
glm::vec2 pos;
glm::vec2 dir;

bool active; //detect the collision with the hole
std::vector<glm::vec2> path; //store history of positions

//constractor function 
Rays(float startX, float startY) {
        pos = glm::vec2(startX,startY);
        dir = glm::vec2(1,0); // Move along the x-axis (to the Right)
        active = true;
        path.push_back(pos); //save the starting point
    }

//draw the light rays
void draw() {
        // 3. Draw the trace (connect all saved points)
        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_STRIP); 
        for (const auto& point : path) {
            glVertex2f(point.x, point.y);
        }
        glEnd();

        //draw the moving dot at the end
        glBegin(GL_POINTS);
        glVertex2f(pos.x, pos.y);
        glEnd();
    }


//controll movement of the light rays relative to position
void update(){
    if (!active) return;
    pos = pos+dir*0.005f; 
    path.push_back(pos);
    if (pos.x > 1.2f) {
            active = false;
        }

}

};


int main(){
//start GLFW library
    if (!glfwInit()) {
        std::cerr << "Failed to start GLFW" << std::endl;
        return -1;
    }
//create an 800x800 pixel window titled " Black Hole"
    GLFWwindow* window = glfwCreateWindow(900,800,"Black Hole",NULL,NULL);

//make this window the active one for drawing
    glfwMakeContextCurrent(window);
 //initialize GLEW 
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to init GLEW" << std::endl;
        return -1;
    }

    //background-dark space blue grey(R=0.05,G=0.05,B=0.1)
    glClearColor(0.05,0.05,0.1,1.0);  
    
    //instantiating objects
    BlackHole black_hole;
    //store the multiple rays inside a vector
    std::vector<Rays> all_rays;
    for (int i=0;i<70;i++){
        float startY=-0.8+(i*0.03); //heights from -0.8 to 0.8
        all_rays.push_back(Rays(-1.5f, startY)); //start further left (-1.5)
    }

    while (!glfwWindowShouldClose(window)) {

        //clear the screen 
        glClear(GL_COLOR_BUFFER_BIT);

        /*The main code*/
        //draw the circle
        black_hole.DrawCircle();
        //print all rays in a loop
        for(int i=0;i<all_rays.size();++i){
        all_rays[i].update();
        all_rays[i].draw();
        }
        //swap the back buffer
        glfwSwapBuffers(window);
        
        //check for keyboard/mouse events 
        glfwPollEvents();

}
 // Cleanup when the loop ends
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;

}
