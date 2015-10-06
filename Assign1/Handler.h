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
#include <cmath>
#include "Point.h"
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

extern int WINDOW_SIZE;
#define PI 3.14159265

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
//        printf("stack size : %d\n", (int)stack->size());
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
    
    /*
    void draw1(std::stack<Point>* stack) {
//        printf("stack size : %d\n", (int)stack->size());
        if(stack->size() < 2) {
            return;
        }
        
        Point p1 = stack->top();
        stack->pop();
        Point p2 = stack->top();
        stack->pop();
        
        float dx = p2.x - p1.x;
        float dy = p2.y - p1.y;
        float max = myabs(dx) > myabs(dy) ? myabs(dx) : myabs(dy);
        dx /= max;
        dy /= max;
        float i = p1.x, j = p1.y;
        
        glBegin(GL_POINTS);
        
        while((int)i != p2.x) {
            drawPoint(i, j);
            i += dx;
            j += dy;
        }
        
        glEnd();
        glFlush();
    }
    
    */
    
    void draw(std::stack<Point>* stack) {
        if(stack->size() < 2) {
            return;
        }
        
        Point* p2 = &stack->top();
        stack->pop();
        Point* p1 = &stack->top();
        stack->pop();
        
        int dx = p2->x - p1->x;
        int dy = p2->y - p1->y;
        bool xincrease = myabs(dx) > myabs(dy);
        int x0, y0, x1, y1, inc = 1;
        
        if(xincrease) {
            if(p2->x < p1->x) {
                Point* temp = p1;
                p1 = p2;
                p2 = temp;
            }
            x0 = p1->x;
            y0 = p1->y;
            x1 = p2->x;
            y1 = p2->y;
        }
        else {
            if(p2->y < p1->y) {
                Point* temp = p1;
                p1 = p2;
                p2 = temp;
            }
            x0 = p1->y;
            y0 = p1->x;
            x1 = p2->y;
            y1 = p2->x;
        }
        
        if(y1 < y0) {
            inc = -1;
        }
        
        dx = x1 - x0;
        dy = y1 - y0;
        if(dy < 0) {
            dy = -dy;
        }
        int d = 2 * dy - dx;
        int einc = dy * 2;
        int edec = 2 * dy - 2 * dx;
//        printf("dx=%d,dy=%d\n", dx, dy);
        
        glBegin(GL_POINTS);
        
        if(!xincrease) {
            drawPoint(y0, x0);
        } // draw single dot when double click
        
        while(x0 < x1) {
            if(d <= 0) {
                d += einc;
                x0++;
            }
            else {
                d += edec;
                x0++;
                y0 += inc;
            }
            if(xincrease) {
                drawPoint(x0, y0);
            }
            else {
                drawPoint(y0, x0);
            }
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

        Point p2 = stack->top();
        stack->pop();
        Point p1 = stack->top();
        stack->pop();
        
        Point eP1 = Point(p1.x, p2.y);
        Point eP2 = Point(p2.x, p1.y);
        
        LineHandler lineForRec = LineHandler();
        
        stack->push(eP1);
        stack->push(p1);
        lineForRec.draw(stack);
        
        stack->push(p1);
        stack->push(eP2);
        lineForRec.draw(stack);
        
        stack->push(eP2);
        stack->push(p2);
        lineForRec.draw(stack);
        
        stack->push(p2);
        stack->push(eP1);
        lineForRec.draw(stack);
    }
};

class CircleHandler : public Handler {
public:
    void draw(std::stack<Point>* stack) {
        if(stack->size() < 2) {
            return;
        }
        
        Point p2 = stack->top();
        stack->pop();
        Point p1 = stack->top();
        stack->pop();
        
        double r = getRadius(p1, p2);
        
        double ox = p1.x;
        double oy = p1.y;
        double px = ox - r;
        double py = oy;
        double qx = ox;
        double qy = oy + r;
        
        glBegin(GL_POINTS);
        
        for(double i = 0; i <= r; i += 1) {
            //        for(int i = 0; i <= 90; i++) {
            double a, h, x;
            double nx, ny;
            double mx, my;
            
            /* x-axis method */
            a = sqrtf(2 * r * i);
            h = sqrtf(a * a - i * i);
            nx = px + i;
            ny = py + h;
            mx = qx - h;
            my = qy - i;
            
            /* cos method */
            //            a = 2 * r * cos(i * PI / 180);
            //            x = 0.5 * a * a / r;
            //            h = sqrtf(a * a - i * i);
            //            nx = px + x;
            //            ny = py + h;
            
            ny = WINDOW_SIZE - ny;
            my = WINDOW_SIZE - my;
            glVertex2d(nx, ny);
            glVertex2d(mx, my);
            
            nx += 2 * (r - i);
            mx += 2 * h;
            glVertex2d(nx, ny);
            glVertex2d(mx, my);
            
            ny += 2 * h;
            my += 2 * (r - i);
            glVertex2d(nx, ny);
            glVertex2d(mx, my);
            
            nx -= 2 * (r - i);
            mx -= 2 * h;
            glVertex2d(nx, ny);
            glVertex2d(mx, my);
        }
        
        glEnd();
        glFlush();
    }
    
//    void draw(std::stack<Point>* stack) {
//        if(stack->size() < 2) {
//            return;
//        }
//        
//        Point p2 = stack->top();
//        stack->pop();
//        Point p1 = stack->top();
//        stack->pop();
//        
//        double r = getRadius(p1, p2);
//        
//        double ox = p1.x;
//        double oy = WINDOW_SIZE - p1.y;
//        
//        glBegin(GL_LINE_LOOP);
//        
//        double nx, ny;
//        for(int i = 0; i <= 360; i++) {
//            nx = r * cos(2.0 * PI * i / 360) + ox;
//            ny = r * sin(2.0 * PI * i / 360) + oy;
//            glVertex2d(nx, ny);
//        }
//        
//        glEnd();
//        glFlush();
//    }
    
private:
    double getRadius(Point p1, Point p2) {
        return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    }
    
    
};

#endif /* defined(__Assign1__Handler__) */
