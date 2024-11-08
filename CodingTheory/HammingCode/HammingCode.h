#ifndef HAMMINGCODE_H
#define HAMMINGCODE_H

#include <vector>

/**
 * Encodes the input data bits into a Hamming code.
 * @param input The data bits to encode.
 * @param totalBits The total number of bits after encoding (data bits + parity bits).
 * @return A vector of booleans representing the encoded Hamming code.
 */
std::vector<bool> encode(const std::vector<bool>& input, int totalBits);

/**
 * Calculates the error syndrome of a received Hamming code.
 * @param noisy_encoded The received Hamming code with potential errors.
 * @return The error syndrome as an integer.
 */
int calculateErrorSyndrome(const std::vector<bool>& noisy_encoded);

/**
 * Decodes the received Hamming code, correcting any single-bit errors.
 * @param noisy_encoded The received Hamming code with potential errors.
 * @param error_syndrome The calculated error syndrome.
 * @return A vector of booleans representing the corrected data bits.
 */
std::vector<bool> decode(const std::vector<bool>& noisy_encoded, int error_syndrome);

#endif // HAMMINGCODE_H
