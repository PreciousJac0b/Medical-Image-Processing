#include "image.h"
#include "iostream"
#include "cstring"
#include "string"

/*
g++ -o main main.cpp image.cpp -std=c++17
*/

int main(int argc, char *argv[])
{
  for (int i = 0; i < argc; i++)
  {
    if (std::strcmp(argv[i], "graylum") == 0)
    {
      // printf("Got called!");
      Image test("test1.jpg");

      Image gray_lum = test;
      gray_lum.grayscale_lum();
      gray_lum.write("gray_lum.png");
      return 0;
    }
    else if (std::strcmp(argv[i], "copy") == 0)
    {
      Image test("test1.jpg");
      test.write("new.png");

      Image copy = test;

      for (int y = 0; y < copy.h / 2; ++y)
      {
        for (int x = 0; x < copy.w; ++x)
        {
          int pixelIndex = (y * copy.w + x) * copy.channels;
          for (int c = 0; c < copy.channels; ++c)
          {
            copy.data[pixelIndex + c] = 0;
          }
        }
      }
      copy.write("copy.png");

      Image blank(100, 100, 3);
      blank.write("blank.jpg");
    }
    else if (std::strcmp(argv[i], "noisefilter") == 0)
    {
      Image img("test1.jpg");
      if (!img.read("test1.jpg"))
      {
        std::cerr << "Failed to load input_image.jpg" << std::endl;
        return -1;
      }
      // Apply the noise filtering and get a new filtered image
      Image filteredImg = img.applyNoiseFiltering();

      // Save the filtered image as a new JPEG
      if (!filteredImg.write("filtered_image.jpg"))
      {
        std::cerr << "Failed to save filtered_image.jpg" << std::endl;
        return -1;
      }
      std::cout << "Filtered image saved as filtered_image.jpg" << std::endl;
      return 0;
    }
    // std::cout << "Index: ";
    // std::cout << i << std::endl;
    // std::cout << argv[i] << std::endl;
  }
}

// int main(int argc, char** argv) {
// Image test("test1.jpg");

// Image gray_lum = test;
// gray_lum.grayscale_lum();
// gray_lum.write("gray_lum.png");
// return 0;

//   test.write("new.png");

//   Image copy = test;
//   // for (int j = 0; j < (copy.h); ++j) {
//   //   for (int i = 0; i < copy.w*copy.channels; ++i) {
//   //     copy.data[i] = 255;
//   //   };
//   // }

//   for (int y = 0; y < copy.h / 2; ++y) {
//     for (int x = 0; x < copy.w; ++x) {
//         int pixelIndex = (y * copy.w + x) * copy.channels;
//         for (int c = 0; c < copy.channels; ++c) {
//             copy.data[pixelIndex + c] = 0;
//         }
//     }
// }
//   copy.write("copy.png");

//   Image blank(100, 100, 3);
//   blank.write("blank.jpg");

// }