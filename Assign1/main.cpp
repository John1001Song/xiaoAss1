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

#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
#include "Handler.h"

int WINDOW_SIZE = 600;

Handler* h;
PointHandler ph = PointHandler();
LineHandler lh = LineHandler();
RectangleHandler rh = RectangleHandler();
CircleHandler ch = CircleHandler();

std::stack<Point>* pStack = new std::stack<Point>();

void display(void){
//    glClearColor(1, 1, 1, 0);
//    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

// create point
//void point(int x, int y){
//    y = 600 - y;
//    glPointSize(3);
//    glBegin(GL_POINTS);
//        glVertex2i(x, y);
//    glEnd();
//    glFlush();
//}

void mouse(int btn, int state, int x, int y){
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        pStack->push(Point(x,y));
        h->draw(pStack);
    }
    glFlush();
}

void motion(int x, int y){
    if(h == &ph) {
        pStack->push(Point(x,y));
        h->draw(pStack);
    }
}

void timerRedisplay(int value){
    glutTimerFunc(32, timerRedisplay, 0);
    display();
}

//set up menu
void menu(int value){
//    printf("menu action\n");
    switch (value) {
        case 0:
            glColor3f(.0f, .0f, 1.0f);
            break;
            
        case 1:
            glColor3f(1.0f, 0.0f, .0f);
            break;
            
        case 2:
            glColor3f(.0f, 1.0f, 0.0f);
            break;
            
        case 3:
            glColor3f(.5f, 0, .5f);
            break;
        
        case 4:
            glColor3f(1, 1, 0);
            break;
            
        case 11:
            float r, g, b;
            r = (rand()%1000)*1.0/1000;
            g = (rand()%1000)*1.0/1000;
            b = (rand()%1000)*1.0/1000;
            glColor3f(r, g, b);
            printf("%f,%f,%f\n",r,g,b);
            break;
         
        case 5: // point
            h = &ph;
            break;
           
        case 6: // line
            h = &lh;
            break;
            
        case 7: // rectangle
            h = &rh;
            break;
            
        case 8: // circle
            h = &ch;
            break;
            
        case 9:
            exit(0);
            break;
            
        case 10:
            glClear(GL_COLOR_BUFFER_BIT);
            break;
            
        default:
            break;
    }
}

void initMenu(){
    int subColor = glutCreateMenu(menu);
    glutAddMenuEntry("Blue", 0);
    glutAddMenuEntry("Red", 1);
    glutAddMenuEntry("Green", 2);
    glutAddMenuEntry("Purple", 3);
    glutAddMenuEntry("Yellow", 4);
    glutAddMenuEntry("Random Color", 11);
    
    int subShape = glutCreateMenu(menu);
    glutAddMenuEntry("Point", 5);
    glutAddMenuEntry("Line", 6);
    glutAddMenuEntry("Rectangle", 7);
    glutAddMenuEntry("Circle", 8);
    
    int mainMenuId = glutCreateMenu(menu);
    glutAddSubMenu("Color", subColor);
    glutAddSubMenu("Shape", subShape);
    glutAddMenuEntry("Clear", 10);
    glutAddMenuEntry("Quit", 9);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    
   // glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 600);
    glutCreateWindow("JJ");
    
    initMenu();
    
    glutDisplayFunc(display);
    
    glutMouseFunc(mouse);
    
    glutMotionFunc(motion);
    
    gluOrtho2D(0, 600, 0, 600);
    
    timerRedisplay(0);
    
    glClearColor(1, 1, 1, 1);
    
    h = &ph;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 1);
    glPointSize(2);
    
    glutMainLoop();
    
    return (0);
}
