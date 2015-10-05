//
//  Handler.h
//  Assign1
//
//  Created by Xuchao Ding on 2015-10-04.
//  Copyright (c) 2015 Jinyue Song. All rights reserved.
//

#ifndef __Assign1__Handler__
#define __Assign1__Handler__

#include <stdio.h>
#include <stack>
#include "Point.h"
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

extern int WINDOW_SIZE;

class Handler {
public:
    virtual void draw(std::stack<Point> list) {
        
    }
};

class PointHandler : public Handler {
public:
    void draw(std::stack<Point> stack) {
        Point p = stack.top();
        int x = p.x;
        int y = WINDOW_SIZE - p.y;
        glPointSize(3);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();
        stack.pop();
    }
};

class LineHandler : public Handler {
public:
    void draw(std::stack<Point> stack) {
        if(stack.size() < 2) {
            return;
        }
    }
};

class RectangleHandler : public Handler {
public:
    void draw(std::stack<Point> stack) {
        if(stack.size() < 2) {
            return;
        }
    }
};

class CircleHandler : public Handler {
public:
    void draw(std::stack<Point> stack) {
        if(stack.size() < 2) {
            return;
        }
    }
};

#endif /* defined(__Assign1__Handler__) */
