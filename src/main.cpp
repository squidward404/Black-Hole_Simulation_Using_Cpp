// bunch of OpenGL libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp> //math library

#include <iostream>

#include <cmath> //need sqrt() and probably trig functions.

/*classes*/
class BlackHole{
public:

//variables 
float mass;
float radius;

BlackHole(float m) {
        mass=m;
        radius=2*mass; //schwarzschild radius(radius of the black hole is 2x of it's mass)
    }

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

};

/*constants*/
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

    //dark space blue grey(R=0.05,G=0.05,B=0.1)
    glClearColor(0.05f,0.05f,0.1f,1.0f);    
    BlackHole black_hole(0.1);
    Rays ray;

    while (!glfwWindowShouldClose(window)) {

        //clear the screen 
        glClear(GL_COLOR_BUFFER_BIT);

        /*The main code*/
        black_hole.DrawCircle();

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
