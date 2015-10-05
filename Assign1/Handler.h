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
    virtual void draw(std::stack<Point>* list) {
        // blank
    }
};

class PointHandler : public Handler {
public:
    void draw(std::stack<Point>* stack) {
        Point p = stack->top();
        drawPoint(p);
        stack->pop();
        printf("stack size : %d\n", (int)stack->size());
    }
    
private:
    void drawPoint(Point p) {
        int x = p.x;
        int y = WINDOW_SIZE - p.y;
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();
    }
};

class LineHandler : public Handler {
public:
    void draw(std::stack<Point>* stack) {
        printf("stack size : %d\n", (int)stack->size());
        if(stack->size() < 2) {
            return;
        }
        Point p1 = stack->top();
        stack->pop();
        Point p2 = stack->top();
        stack->pop();
        double dx = p2.x - p1.x;
        double dy = p2.y - p1.y;
        double max = myabs(dx) > myabs(dy) ? myabs(dx) : myabs(dy);
        dx /= max;
        dy /= max;
        double i = p1.x, j = p1.y;
        glBegin(GL_POINTS);
        while((int)i != p2.x) {
            drawPoint(i, j);
            i += dx;
            j += dy;
        }
        glEnd();
        glFlush();
    }
    
private:
    int myabs(double x) {
        if(x < 0)
            x = -x;
        return x;
    }
    
    void drawPoint(int x, int y) {
        y = WINDOW_SIZE - y;
        glVertex2i(x, y);
    }
};

class RectangleHandler : public Handler {
public:
    void draw(std::stack<Point>* stack) {
        if(stack->size() < 2) {
            return;
        }

        
    }
};

class CircleHandler : public Handler {
public:
    void draw(std::stack<Point>* stack) {
        if(stack->size() < 2) {
            return;
        }
    }
};

#endif /* defined(__Assign1__Handler__) */
