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
  int energy_total;
  int rx, bx, gx, ry, by, gy;
  int xleft, xright, yup, ydown;

  if(edgePixel){
    if(x == 0){
      xleft = width-1;
      xright = x+1;
    }
    else if(x == width-1){
      xleft = x-1;
      xright = 0;
    }
    if(y == 0){
      ydown = height-1;
      yup = y+1;
    }
    else if(x == width-1){
      ydown = x-1;
      yup = 0;
    }
  }
  else{
    xleft = x-1;
    xright = x+1;
    yup = y+1;
    ydown = y-1;
  }
  
  rx = image[xright][y].r - image[xleft][y].r;
  gx = image[xright][y].g - image[xleft][y].g;
  bx = image[xright][y].b - image[xleft][y].b;

  ry = image[x][yup].r - image[x][ydown].r;
  gy = image[x][yup].g - image[x][ydown].g;
  by = image[x][yup].b - image[x][ydown].b;


  rx*=rx;
  gx*=gx;
  bx*=bx;
  ry*=ry;
  gy*=gy;
  by*=by;

  energy_total = (rx+gx+bx+ry+by+gy);

  energy_total = std::abs(energy_total);
  return (unsigned int)energy_total;
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
