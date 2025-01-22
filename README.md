# MEDICAL IMAGE PROCESSING


## USAGE
Navigate to the home directory. The functions required is presently located in the image.cpp and main.cpp file so they are both required during compilation. The code can be compiled using:

```g++ -o main main.cpp image.cpp -std=c++17```

The code presently supports three arguments. "graylum", "copy", "noisefilter"

* Graylum: Creates a grayscale version of the image. 
* Copy: Creates a copy version of the image. 
* noisefilter: Creates a filtered version of the image. 


# Example Usage
```./main graylum```

This creates a graylum version of the image.
