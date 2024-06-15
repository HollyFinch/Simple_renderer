#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "geometry.h"

//forgot how to declare global var LOL
#define width 500
#define height 500

int framebuffer[width][height]; 

void rasterizeTriangle(Triangle triangle) {
  // Calculate bounding box
  int minX = floor(fmin(triangle.p1.x, fmin(triangle.p2.x, triangle.p3.x)));
  int maxX = ceil(fmax(triangle.p1.x, fmax(triangle.p2.x, triangle.p3.x)));
  int minY = floor(fmin(triangle.p1.y, fmin(triangle.p2.y, triangle.p3.y)));
  int maxY = ceil(fmax(triangle.p1.y, fmax(triangle.p2.y, triangle.p3.y)));


  for (int y = minY; y <= maxY; y++) {
    for (int x = minX; x <= maxX; x++) {
      if (isInsideTriangle(x, y, triangle)) {
        framebuffer[y][x] = triangle.color;
      }
    }
  }
}

bool isInsideTriangle(int x, int y, Triangle triangle) {
  // Implement barycentric coordinate check here
}

void render(Triangle triangle) {
  rasterizeTriangle(triangle);
  // Display framebuffer (implementation depends on your chosen method)
}


int main() {

  Point p1 = {100.0f, 50.0f, 0.0f};
  Point p2 = {200.0f, 200.0f, 0.0f};
  Point p3 = {50.0f, 200.0f, 0.0f};
  Triangle triangle = {p1, p2, p3};

  render(triangle);

  
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      printf("%d ", framebuffer[y][x]); 
    }
    printf("\n");
  }

  return 0;
}