#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "image.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>


void insertionSort(int arr[], int n)
{
  int i, key, j;
  for (i = 1; i < n; i++)
  {
    key = arr[i];
    j = i - 1;
    while (j >= 0 && arr[j] > key)
    {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }
}

Image::Image(const char *filename)
{
  if (read(filename))
  {
    printf("Read %s\n", filename);
    size = w * h * channels;
  }
  else
  {
    printf("Failed to read %s\n", filename);
  }
}
Image::Image(int w, int h, int channels) : w(w), h(h), channels(channels)
{
  size = w * h * channels;
  data = new uint8_t[size];
}
Image::Image(const Image &img) : Image(img.w, img.h, img.channels)
{
  memcpy(data, img.data, size);
}
Image::~Image()
{
  // cleans all the data. Call when an image gets destructed.
  stbi_image_free(data);
}

bool Image::read(const char *filename)
{
  data = stbi_load(filename, &w, &h, &channels, 0); // Function will fail if data is null.
  return data != NULL;
}
bool Image::write(const char *filename)
{
  ImageType type = getFileType(filename);
  int success;
  switch (type)
  {
  case PNG:
    success = stbi_write_png(filename, w, h, channels, data, w * channels);
    break;
  case BMP:
    success = stbi_write_bmp(filename, w, h, channels, data);
    break;
  case JPG:
    success = stbi_write_jpg(filename, w, h, channels, data, 100);
    break;
  case TGA:
    success = stbi_write_tga(filename, w, h, channels, data);
    break;
  }
  return success != 0;
}

ImageType Image::getFileType(const char *filename)
{
  const char *ext = strrchr(filename, '.');
  if (ext != nullptr)
  {
    if (strcmp(ext, ".png") == 0)
    {
      return PNG;
    }
    else if (strcmp(ext, ".jpg") == 0)
    {
      return JPG;
    }
    else if (strcmp(ext, ".bmp") == 0)
    {
      return BMP;
    }
    else if (strcmp(ext, ".tga") == 0)
    {
      return TGA;
    }
  }
  return PNG;
}

Image &Image::grayscale_avg()
{
  if (channels < 3)
  {
    printf("Image %p channels is less than 3. It is assumed to be already grayscaled.", this);
  }
  else
  {
    for (int i = 0; i < size; i += channels)
    {
      int gray = (data[i] + data[i + 1] + data[i + 2]) / 3;
      memset(data + i, gray, 3);
    }
  }
  return *this;
}
Image &Image::grayscale_lum()
{
  if (channels < 3)
  {
    printf("Image %p channels is less than 3. It is assumed to be already grayscaled.", this);
  }
  else
  {
    for (int i = 0; i < size; i += channels)
    {
      int gray = (0.2126 * data[i] + 0.7152 * data[i + 1] + 0.0722 * data[i + 2]) / 3;
      memset(data + i, gray, 3);
    }
  }
  return *this;
}

// Image &Image::colorMask(float r, float g, float b)
// {
//   if (channels < 3)
//   {
//     printf("\e[31m[ERROR] Color mask requires at least 3 channels but this image has %d channels\e[0m\n", channels);
//     for (int i = 0; i < size; i += channels)
//     {
//     }
//   }
// }

// void Image::applyNoiseFiltering()
// {
//   if (data == nullptr)
//   {
//     std::cerr << "Image data is null. Load an image first." << std::endl;
//     return;
//   }

//   uint8_t *filteredData = new uint8_t[w * h * channels](); // New filtered image buffer
//   int window[9];

//   // Apply median filter
//   for (int row = 1; row < h - 1; ++row)
//   {
//     for (int col = 1; col < w - 1; ++col)
//     {
//       for (int c = 0; c < channels; ++c)
//       {
//         // Populate the 3x3 window for the current pixel
//         window[0] = data[((row - 1) * w + (col - 1)) * channels + c];
//         window[1] = data[((row - 1) * w + col) * channels + c];
//         window[2] = data[((row - 1) * w + (col + 1)) * channels + c];
//         window[3] = data[(row * w + (col - 1)) * channels + c];
//         window[4] = data[(row * w + col) * channels + c];
//         window[5] = data[(row * w + (col + 1)) * channels + c];
//         window[6] = data[((row + 1) * w + (col - 1)) * channels + c];
//         window[7] = data[((row + 1) * w + col) * channels + c];
//         window[8] = data[((row + 1) * w + (col + 1)) * channels + c];

//         // Sort the window to find the median
//         insertionSort(window, 9);

//         // Assign the median value to the filtered data
//         filteredData[(row * w + col) * channels + c] = window[4];
//       }
//     }
//   }

//   // Replace old data with the filtered data
//   delete[] data;
//   data = filteredData;
// }

Image Image::applyNoiseFiltering() const {
    if (data == nullptr) {
        std::cerr << "Image data is null. Load an image first." << std::endl;
        return Image(0, 0, 0); // Return an empty image
    }

    // Create a new image for the filtered data
    Image filteredImage(w, h, channels);
    uint8_t *filteredData = filteredImage.data; // Pointer to the new image's data
    int window[9];

    // Apply median filter
    for (int row = 1; row < h - 1; ++row) {
        for (int col = 1; col < w - 1; ++col) {
            for (int c = 0; c < channels; ++c) {
                // Populate the 3x3 window for the current pixel
                window[0] = data[((row - 1) * w + (col - 1)) * channels + c];
                window[1] = data[((row - 1) * w + col) * channels + c];
                window[2] = data[((row - 1) * w + (col + 1)) * channels + c];
                window[3] = data[(row * w + (col - 1)) * channels + c];
                window[4] = data[(row * w + col) * channels + c];
                window[5] = data[(row * w + (col + 1)) * channels + c];
                window[6] = data[((row + 1) * w + (col - 1)) * channels + c];
                window[7] = data[((row + 1) * w + col) * channels + c];
                window[8] = data[((row + 1) * w + (col + 1)) * channels + c];

                // Sort the window to find the median
                insertionSort(window, 9);

                // Assign the median value to the filtered data
                filteredData[(row * w + col) * channels + c] = window[4];
            }
        }
    }

    return filteredImage;
}