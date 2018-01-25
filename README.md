### SDL Demo code and SDL Load/Display PPM image

Authors: Joshua Levine and Rohin Galhotra

This code provides an introductory demonstration of SDL as well as basic build scripts with CMake, and displays profeciency with loading and manipulating data in cpp.


### README

The sample code has been altered to draw the loaded PPM in a separate window. The PPM data is stored within a "ppm" data type defined by header and class files included. Usage is as thus:

'prog01 image'

Where image refers to the image file, 'image.ppm'. Does not handle edge case where a comment in a PPM header does not start at the beginning of the line.

### Attributions

I modified the CMakeLists.txt file to reflect the CMakeLists.txt file used by ECE 275 and other ECE classes in order to get CMake to work better. I used [cplusplus.com](http://www.cplusplus.com/) as an easy reference to find what functions to use for various file manipulation tasks. I also looked through several [Stack Overflow](https://stackoverflow.com/) posts when attempting to solve problems I had run into, but ended up not using any code found on that site in the end.
