// bunch of OpenGL libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp> //math library

#include <iostream>

#include <cmath> //need sqrt() and probably trig functions.

/*constants will be here*/


int main(){
//start GLFW library
    if (!glfwInit()) {
        std::cerr << "Failed to start GLFW" << std::endl;
        return -1;
    }
//create an 800x800 pixel window titled " Black Hole"
    GLFWwindow* window = glfwCreateWindow(800, 800, "Black Hole", NULL, NULL);

//make this window the active one for drawing
    glfwMakeContextCurrent(window);
 //initialize GLEW 
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to init GLEW" << std::endl;
        return -1;
    }
// Set the background color to Black (R=0, G=0, B=0)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    while (!glfwWindowShouldClose(window)) {

        //clear the screen 
        glClear(GL_COLOR_BUFFER_BIT);

        /*The main code*/

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
