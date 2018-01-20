//
//  opengl_cgr.cpp
//
//  Created by Magdalena Geißbauer on 09/01/2018.
//  Copyright © 2018 ue. All rights reserved.
//

#include <GLUT/GLUT.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshorten-64-to-32"


float move = 0.0f;
float first = 0.0f;
float second = 0.0f;
float bucket = 0.0f;

float preX = 0.0f;
float rotation = 0.0f;

// rotates everything
void onMotion(int x, int y) {
    if (fabs(x - preX))    {
        rotation = ((x - preX) > 0) ? rotation += 10.0 * 0.11 : rotation -= 10.0 * 0.11;
    }
    
    preX = x;
    glutPostRedisplay();
}

// mouse input with left button pressed
void onMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        preX = x;
        glutMotionFunc(onMotion);
    }
}

void description()
{
    std::cout << "You move the excavot in one direction. --> m" << std::endl;
    std::cout << "You move up the first arm. --> f" << std::endl;
    std::cout << "You move the first arm down --> F" << std::endl;
    std::cout << "You move up the second arm. --> s" << std::endl;
    std::cout << "You move the wirst second down --> S" << std::endl;
    std::cout << "You open the bucket --> o" << std::endl;
    std::cout << "You clorse the bucket --> c" << std::endl;
}


// EXCAVATOR - PARTS
// -----------------------------------------

// ----- drawing the arm combined with the spheres -----
void createArmWithSphere()
{
    glPushMatrix();
    glTranslatef(-1.5, 0, 0);
    glutWireSphere(0.8, 10, 10);
    glPopMatrix();
    
    glPushMatrix();
    glScaled(3.0, 1, 1);
    glutWireCube(1);
    glPopMatrix();
}

// ----- drawing the bucket -----
void createBucket()
{
    glPushMatrix();
    glTranslatef(-0.6, -0.1, 0);
    glScaled(1.1, 0.7, 1.3);
    glutWireCube(2);
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslatef(-1.7, -0.4, 0);
    glScaled(0.07, 1, 1.5);
    glutWireCube(2);
    glPopMatrix();
}

// ----- drawing the excavator arm -----
void createExcavatorArmAndBucket () {
    glPushMatrix();
    glRotatef(-45, 0, 0, 1);
    
    createArmWithSphere();
    glTranslatef(-1.5, 0, 0);
    glRotatef(first, 0, 0, 1);
    glTranslatef(1.5, 0, 0);
    
    glTranslatef(-1.5, 0, 0);
    glRotatef(40, 0, 0, 1);
    glTranslatef(-1.5, 0, 0);
    
    createArmWithSphere();
    glTranslatef(-1.5, 0, 0);
    glRotatef(second, 0, 0, 1);
    glTranslatef(1.5, 0, 0);
    
    glTranslatef(-1.5, 0, 0);
    glRotatef(80, 0, 0, 1);
    glTranslatef(-1.5, 0, 0);
    
    createArmWithSphere();
    glTranslatef(-1.5, 0, 0);
    glRotatef(bucket, 0, 0, 1);
    glTranslatef(1.5, 0, 0);
    
    glTranslatef(-1.3, 0, 0);
    glRotatef(90, 0, 0, 1);
    glTranslatef(-0.4, 0.6, 0);
    createBucket();
    
    glPopMatrix();
}


// ----- drawing the cabin -----
void createExcavatorCabin()
{
    glPushMatrix();
    glTranslatef(5, 1, 2);
    glScaled(1, 1.3, 1);
    glutWireCube(2);
    glPopMatrix();
    
    
    glPushMatrix();
    glTranslatef(0.1, -0.9, 2);
    glScaled(0.8, 1, 1);
    glutWireCube(1);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(3, -0.8, 2);
    glScaled(1.3, 0.5, 1);
    glutWireCube(4);
    glPopMatrix();
    
    
    glTranslatef(1, -1.5, -2);
    
    
}

// ----- draw the wheel -----
void createWheels()
{
    glPushMatrix();
    glScaled(1.2, 1.2, 0.5);
    glutWireSphere(1, 10, 10);
    glPopMatrix();
}


// ----- drawing the excavator -----
void drawExcavator()
{
    glTranslatef(2, 1, -16);
    
    createExcavatorArmAndBucket();
    
    glTranslatef(1, -0.35, 0);
    createExcavatorCabin();
    
    glPushMatrix();
    glTranslatef(2, -1, -3);
    createWheels();
    glTranslatef(4, 0, 0);
    createWheels();
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(2, -1, -1);
    createWheels();
    glTranslatef(4, 0, 0);
    createWheels();
    glPopMatrix();
}

// draw surface
void drawSurface()
{
    glPushMatrix();
    
    glTranslatef(0, -2, -15);
    glScaled(25, 0.1, 10);
    glutWireCube(1);
    
    glPopMatrix();
}

// renders everything
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(1.0, 1.0, 1.0);
    
    glRotatef(rotation, 0, 1, 0);
    
    drawSurface();
    
    glTranslatef(move, 0, 0);
    drawExcavator();
    
    glFlush();
}

// what it does with what key
void keysPressed(unsigned char key, int x, int y)
{
    switch (key) {
            
        case 'm':
            move -= 0.3;
            break;
            
        case 'h':
            description();
            break;
            
        case 'f':
            if (first > -60) // collision avoidance
            {
                first -= 10;
            }
            break;
            
        case 'F':
            if (first < 40) // collision avoidance
            {
                first += 10;
            }
            break;
            
        case 's':
            if (second > -80) // collision avoidance
            {
                second -= 10;
            }
            break;
            
        case 'S':
            if (second < 50) // collision avoidance
            {
                second += 10;
            }
            break;
            
        case 'o':
            if (bucket < 20) // collision avoidance
            {
                bucket += 10;
            }
            break;
            
        case 'c':
            if (bucket > -120) // collision avoidance
            {
                bucket -= 10;
            }
            break;
    }
    
    glutPostRedisplay();
}

//initialization of the application. only started once.
void init()
{
    //select clearing color (color that is used as 'background')
    glClearColor(0.0, 0.0, 0.0, 0.0);
    
    //initialize view
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float width = glutGet(GLUT_WINDOW_WIDTH);
    float height = glutGet(GLUT_WINDOW_HEIGHT);
    gluPerspective(65, width/height, 0.1, 60);
    
    //set matrix-mode back to model-view for rendering
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    
    //initialize display mode (single buffer and RGBA)
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    //initialize window size and position. open window
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("OpenGL - CGR");
    
    //call initialization routine
    init();
    
    glutKeyboardFunc(keysPressed);
    glutMouseFunc(onMouse);
    glutDisplayFunc(display);
    
    //enter main loop and process events
    glutMainLoop();
    
    return 0;
}

