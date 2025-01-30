#include "image.h"
#include "iostream"
#include "cstring"
#include "string"
using namespace std;

/*
g++ -o main main.cpp image.cpp -std=c++17
*/

int main(int argc, char *argv[])
{
  for (int i = 0; i < argc; i++) // Consider removing the loop.
  {
    if (std::strcmp(argv[1], "graylum") == 0)
    {
      Image test(argv[3]);

      Image gray_lum = test;
      gray_lum.grayscale_lum();
      gray_lum.write(argv[2]); // Could also convert using std::string(argv[2]).c_str()
      return 0;
    }
    else if (std::strcmp(argv[1], "copy") == 0)
    {
      Image test(argv[2]);
      // test.write("new.png");

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
      copy.write(argv[3]);

      // Image blank(100, 100, 3);
      // blank.write("blank.jpg");
    }
    else if (std::strcmp(argv[i], "noisefilter") == 0)
    {
      Image img(argv[2]);

      if (!img.read(argv[2]))
      {
        std::cerr << "Failed to load input_image.jpg" << std::endl;
        return -1;
      }
      // Apply the noise filtering and get a new filtered image
      Image filteredImg = img.applyNoiseFiltering();

      // Save the filtered image as a new JPEG
      if (!filteredImg.write(argv[3]))
      {
        std::cerr << "Failed to save filtered_image.jpg" << std::endl;
        return -1;
      }
      std::cout << "Filtered image saved as filtered_image.jpg" << std::endl;
      return 0;
    }
    else if (std::strcmp(argv[i], "colormask") == 0)
    {
      Image img(argv[2]);

      if (!img.read(argv[2]))
      {
        std::cerr << "Failed to load input_image.jpg" << std::endl;
        return -1;
      }

      // Default RGB values (0, 0, 1)
      int r = 0, g = 1, b = 0;  

      // If user provides enough arguments,
      if (argc > 4) r = std::atoi(argv[4]);
      if (argc > 5) g = std::atoi(argv[5]);
      if (argc > 6) b = std::atoi(argv[6]);

      img.colorMask(r, g, b);
      img.write(argv[3]);
      // printf("Got here!");
      return 0;
    } else if (std::strcmp(argv[i], "crop") == 0) {
      printf("%s, %s", argv[0], argv[1]);
      Image img(argv[2]);
      img.write("temp.png");
      img.crop(0, 0, 300, 300);
      img.write(argv[3]);
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