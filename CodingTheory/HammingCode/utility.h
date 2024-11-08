#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <string>

/**
 * Converts a string into a vector of booleans representing its binary form.
 * @param code The input string.
 * @return A vector of booleans representing the binary form of the string.
 */
std::vector<bool> stringToVecBool(const std::string& code);

/**
 * Converts a vector of booleans into its corresponding string.
 * @param vector_code The vector of booleans.
 * @return The reconstructed string.
 */
std::string vecBoolToString(const std::vector<bool>& vector_code);

/**
 * Introduces a single-bit error by flipping a random bit in the encoded vector.
 * @param encoded The encoded Hamming code.
 * @return The encoded vector with one bit flipped.
 */
std::vector<bool> flipBit(std::vector<bool>& encoded);

/**
 * Calculates the number of parity bits required for the given number of data bits.
 * @param numDataBits The number of data bits.
 * @return The number of parity bits required.
 */
int calculateNumberParityBits(int numDataBits);

#endif
