#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using std::cout, std::endl, std::string, std::cin;

void initializeImage(Pixel image[][MAX_HEIGHT]) {
  // iterate through columns
  for (unsigned int col = 0; col < MAX_WIDTH; col++) {
    // iterate through rows
    for (unsigned int row = 0; row < MAX_HEIGHT; row++) {
      // initialize pixel
      image[col][row] = {0, 0, 0};
    }
  }
}

void loadImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int& width, unsigned int& height) {
  std::ifstream inFS;
  string filetype;
  string garbage;
  int maxcolorval;
  unsigned short pr;
  unsigned short pg;
  unsigned short pb;
  inFS.open(filename);
  if(!inFS.is_open()){
    throw std::runtime_error("Failed to open " + filename);
  }

  inFS >> filetype;

  if(filetype != "P3" && filetype != "p3"){
    throw std::runtime_error("Invalid type " + filetype);
  }

  inFS >> width >> height;
  if(!inFS.good() && width > 0 && height > 0 && width <= MAX_WIDTH && height <= MAX_HEIGHT){
    throw std::runtime_error("Invalid dimensions");
  }


  inFS >> maxcolorval;

  for(unsigned int i = 0; i < height; i++){
    for(unsigned int j = 0; j < width; j++){
      inFS >> pr >> pg >> pb;
      if(inFS.fail() || pr >= 256 || pb >= 256 || pg >= 256){
        throw std::runtime_error("Invalid color value");
      }

      
      Pixel p = {(short)pr,(short)pg,(short)pb};
      image[j][i] = p;  
    }
  }

  inFS >> garbage;
  if(!inFS.eof()){
    throw std::runtime_error("Too many values");
  }
}

void outputImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height) {
  std::ofstream outFS;
  outFS.open(filename);
  if(!outFS.is_open()){
    throw std::runtime_error("Failed to open " + filename);
  }

  outFS << "P3" << endl;
  outFS << width << " " << height << endl;
  outFS << "255" << endl;
  for(unsigned int i = 0; i < height; i++){
    for(unsigned int j = 0; j < width; j++){
      Pixel p = image[j][i];
      outFS << p.r << " " << p.g << " " << p.b << " ";
    }
    outFS << endl;
  }
}

unsigned int energy(Pixel image[][MAX_HEIGHT], unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
  bool edgePixel = (x == 0 || y == 0 || x == (width-1) || y == (height-1));
  unsigned int energy_total;

  if(!edgePixel){
    int rx = image[y][x+1].r - image[y][x-1].r;
    int bx = image[y][x+1].g - image[y][x-1].g;
    int gx = image[y][x+1].b - image[y][x-1].b;

    int ry = image[y+1][x].r - image[y-1][x].r;
    int by = image[y+1][x].g - image[y-1][x].g;
    int gy = image[y+1][x].b - image[y-1][x].b;
  }
  else{
    if(x == 0){
      int rx = image[y][x+1].r - image[y][width-1].r;
      int gx = image[y][x+1].g - image[y][width-1].g;
      int bx = image[y][x+1].b - image[y][width-1].b;
    }
    if(x == (width-1)){
      int rx = image[y][0].r - image[i][x-1].r;
      int gx = image[y][0].g - image[i][x-1].g;
      int bx = image[y][0].b - image[i][x-1].b;
    }
    if(y == 0){
      int ry = image[y+1][x].r - image[height-1][x].r;
      int gy = image[y+1][x].g - image[height-1][x].g;
      int by = image[y+1][x].b - image[height-1][x].b;
    }
    if(y == (height-1)){
      int ry = image[0][x].r - image[y-1][x].r;
      int gy = image[0][x].g - image[y-1][x].g;
      int by = image[0][x].b - image[y-1][x].b;
    }
  }

  energy_total = (rx*rx + gx*gx + by*by) + (ry*ry + gy*gy + by*by)

  return energy_total;
}

// uncomment functions as you implement them (part 2)

// unsigned int loadVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_col, unsigned int width, unsigned int height, unsigned int seam[]) {
//   // TODO: implement (part 2)
//   return 0;
// }

// unsigned int loadHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_row, unsigned int width, unsigned int height, unsigned int seam[]) {
//   // TODO: implement (part 2)
//   return 0;
// }

// void findMinVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[]) {
//   // TODO: implement (part 2)
// }

// void findMinHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[]) {
//   // TODO: implement (part 2)
// }

// void removeVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int& width, unsigned int height, unsigned int verticalSeam[]) {
//   // TODO: implement (part 2)
// }

// void removeHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int& height, unsigned int horizontalSeam[]) {
//   // TODO: implement (part 2)
// }
