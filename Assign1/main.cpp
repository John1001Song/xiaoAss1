//
//  main.cpp
//  Assign1
//
//  Created by Jinyue Song on 2015-10-03.
//  Copyright © 2015 Jinyue Song. All rights reserved.
//

//The program should support drawing several primitive types and multiple colours

/*
 
 Left clicking should draw primitives in the current colour, of the current type (as selected from the menu). You should support the following shapes:
 
    a) Points – draw a dot at the point clicked with the mouse. Clicking and dragging should draw points constantly, i.e., free-form drawing. You can use the GL_POINT primitive for these.
    b) Lines – draw a line between two subsequently clicked points. A few line drawing algorithms were discussed in class – full marks will only be awarded here for implementing Bresenham’s algorithm!
    c) Rectangles – draw a rectangle with top-left corner specified by the first click, and the bottom right corner specified by a second click.
    d) Circles – draw a circle centered at the position of the first click, with its radius set by a second click
 (i.e., the length of the vector between the two clicks).
 
 
 Do not use: glClear, glutSwapBuffers, glutPostRedisplay, glut_Double_buffer.

 
 You should include the following functionality (e.g., as GLUT menu items, or keys – include a reference with your code):
    a) Drawing the primitive types above with your own drawing routines 
    b) Changing drawing colour
    c) Clear the screen. 
    d) Quit the program
    e) Random drawing colour
 
 */

#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <OpenGL/glu.h>

void display(void){
    
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex2f(-.6f, -.6f);
    glEnd();
    
    glFlush();
}


void mouse(int btn, int state, int x, int y){
    
    y = 600 - y;
    
    switch (btn) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                glBegin(GL_POINTS);
                glColor3f(.0f, .0f, 1.0f);
                glEnd();
            }
    }
    
    glFlush();
        
    
}

void motion(int x, int y){
    y = 600 - y;
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}


void glutCallbacks(){
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    
}

void timerRedisplay(int value){
    glutTimerFunc(32, timerRedisplay, 0);
    display();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    glutCreateWindow("JJ");
    
    glutDisplayFunc(display);
    
    glutMouseFunc(mouse);
    
    glutMotionFunc(motion);
    
    gluOrtho2D(0, 600, 0, 600);
    
    timerRedisplay(0);
    
    glutMainLoop();
    
    return (0);
}











































