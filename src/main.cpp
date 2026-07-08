// bunch of OpenGL libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp> //math library

#include <iostream>
#include <vector>
#include <cmath> //need sqrt() and trig functions(to draw the circle from triangles coz OpenGL doesn't have a native DrawCircle()).

/*classes*/
class BlackHole{
public:

//variables 
float mass=0.05;
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
        dir = glm::vec2(1,0); // Move along the x-axis(to the right)
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


//controll movement of the light rays relative to position and bending due to the bh
void update(float mass_of_the_bh,glm::vec2 position_of_the_bh){
    if (!active) return;

    glm::vec2 toBH=position_of_the_bh-pos; //find direction to the hole
    float distSq=toBH.x*toBH.x+toBH.y*toBH.y; //the distance^2 to calculate gravity
    float dist=sqrt(distSq);  //the actual distance     
    float black_hole_radius=2.0f*mass_of_the_bh;  //the radius of the black hole
    //don't draw over the black hole
    if(dist<black_hole_radius){
        active=false;
        return;
    }
    float force=mass_of_the_bh/distSq; //gravity(small distance=strong pull,large distance=weaker pull)
    glm::vec2 directionToBH =toBH/dist;//I don't understand this(google search)   
    glm::vec2 acceleration=directionToBH*force;//acceleration vector
    dir=dir+acceleration*0.01f;//intensity of bending due to acceleration(had to assume 0.01 coz don't want to do Runge-Kutta integration)
    //didn't understand this one too.I guess it has smt to do with bending angle correction(google search)
    float len=sqrt(dir.x*dir.x+dir.y*dir.y);
    dir =dir/len;   
    pos = pos+dir*0.005f; 
    path.push_back(pos);//save the trace  

   if (pos.x>1.2||pos.y>1.2||pos.y<-1.2){
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
    all_rays.clear();
    for (int i=0;i<100;i++){
        float startY=-4.0+(i*0.05); //heights from -0.8 to 0.8
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
        //pass mass (0.1f) and position (0,0)
        all_rays[i].update(0.05f,glm::vec2(0.0f,0.0f));   
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
