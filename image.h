#include <iostream>
#include <stdint.h>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <cstddef>

// Setting up an image type.
enum ImageType {
  PNG, JPG, BMP, TGA
};

struct Image {
  uint8_t* data = NULL;
  size_t size = 0;
  int w;
  int h;
  int channels; // How many color values per pixel, rgb = 3, rgba = 4

  Image(const char* filename); // Readfile constructor.
  Image(int w, int h, int channels); // Constructor that creates a black image that we can manipulate willfully
  Image(const Image& img); // Copy constructor. Creates a copy of the image.
  ~Image();

  bool read(const char* filename); // Reads from a file (Called from the readfile constructor).
  bool write(const char* filename);

  ImageType getFileType(const char* filename);

  Image& grayscale_avg();
  Image& grayscale_lum();

  Image& colorMask(float r, float g, float b); 

  void applyNoiseFiltering(); // Applies median filter to reduce noise
};

void insertionSort(int arr[], int n);
// int noise_filtering();