# Hamming Code Implementation in C++

## Overview
This project provides an implementation of the Hamming Code in C++, which is an error-detecting and error-correcting code used in digital communication systems. The code demonstrates encoding a message, introducing a single-bit error, and then detecting and correcting that error.

## Files
- **main.cpp**: The main program that ties all components together.
- **HammingCode.h** and **HammingCode.cpp**: Contains functions for encoding, calculating error syndrome, and decoding.
- **utility.h** and **utility.cpp**: Utility functions for data conversion and error simulation.
- **Makefile**: Build instructions for compiling the program.

## Features
- **Encoding**: Converts input data bits into a Hamming code with appropriate parity bits.
- **Error Introduction**: Simulates transmission errors by flipping a random bit in the encoded message.
- **Error Detection and Correction**: Calculates the error syndrome and corrects any single-bit errors.
- **Data Conversion**: Handles conversion between strings and binary representations.

## Requirements
- C++11 compatible compiler
- Standard C++ libraries

## Compilation
Use the provided Makefile to compile the program:

```bash
make
