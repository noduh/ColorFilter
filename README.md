# Overview

The goal of this project is to gain a basic understanding of C++. I also wanted to do something fun and I think this is a neat little project.

This project is a color adjuster for images that are in the `.ppm` format. This format was chosen due to it's simplicity for programming (the Portable Pixel Map format explicitly describes each color of each pixel). Currently the filter is just described as a way to adjust each color by a multiplier.

The purpose of this project, as described above, is to demonstrate an understanding of C++.
It also has an additional goal of demonstrating an understanding of efficiently handling and manipulating data.
This is done by writing a program that is _efficient_ and changes data using references instead of copying the data.
It does some simple math, changes how the computer looks at the data, and only iterates if it's necessary.
I'm sure it could be more efficient, but I think it's pretty good right now.
Most of the program that doesn't require accessing things one at a time operates at O(1) by accessing individual memory addresses, and skips the copying of that data.
Who needs to copy it when it's already there, am I right?

Currently there is no video made yet.
When it is made it will be linked below.

[Software Demo Video](#)

# Development Environment

Like most of my projects, this project was written in a VSCode environment that's tailored to my preferred setup.
This also was written mostly on a computer with ZSH as my shell and using git for version control.
Originally written on x86-64 on Linux.

This was written in C++, with CMake as the builder and compiled with G++.
This code should work with C++23, but to give myself the newest libraries, this is C++26.

The things I used were all part of the C++ Standard Library (`std`), at least so far.
They included:

- `iostream`
- `vector`
- `ranges`
- `string`
- `span`
- `fstream`
- `sstream`
- `optional`

Naturally, you can also see this list at the top of [main.cpp](main.cpp).

# Useful Websites

Here are some websites that were helpful during this project:

- [W3Schools](https://www.w3schools.com/cpp/)
- [PPM Format Specification](https://netpbm.sourceforge.net/doc/ppm.html)
- [Google AI Mode](https://google.com/aimode)
- [StackOverflow](https://stackoverflow.com)
- [cppreference.com](https://en.cppreference.com/)
- [CMake](https://cmake.org)
- [cplusplus.com](https://cplusplus.com/)
- [VSCode Docs](https://code.visualstudio.com/docs/)

# Future Work

There are a few features and fixes I would like to make.

- Currently the program only uses 1 byte per color per pixel. This needs to be changed to support a `maxval` higher than `255`, which the program allows but does not correctly handle.
- I want an improved TUI
- Other types of color filters, not just adjusting RGB (grey-scale, contrast, etc.)
- Gamma adjustment
- Verifying the integrity of the file
- Related to the previous one: wayyyyy more error handling
- "Plain PPM" (magic number is P3 instead of P6)
- Possibly expanding beyond just a color filter (cropping, scaling, etc.)
