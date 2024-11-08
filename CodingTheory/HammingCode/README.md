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
```

## Usage
This will create an executible with the name ./hamming, which can be run with:

```bash
./hamming
```

Example Interaction:

Input: Hello, World!

```plaintext 
Enter the message to encode: Hello, World!
```

Output:

```plaintext 
This is a Hamming(111, 104) Code
Code Rate: 0.936937

Original Message: Hello, World!
Original Message in Binary: 01001000011001010110110001101100011011110010110000100000010101110110111101110010011011000110010000100001

Encoded Message in Binary:  000110001000011100101011011000101011000110111100101100001000000010101110110111101110010011011000110010000100001
Noisy Message in Binary:    000110011000011100101011011000101011000110111100101100001000000010101110110111101110010011011000110010000100001

Error Syndrome: 8
Decoded Message in Binary:  01001000011001010110110001101100011011110010110000100000010101110110111101110010011011000110010000100001
Decoded Message: Hello, World!
```