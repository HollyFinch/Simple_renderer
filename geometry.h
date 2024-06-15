#ifndef GEOMETRY_H
#define GEOMETRY_H

typedef struct {
    float x;
    float y;
    float z;
} Point;

typedef struct {
    Point p1;
    Point p2;
    Point p3;
    int color;  
} Triangle;

#endif