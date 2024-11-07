#ifndef HAMMINGCODE_H
#define HAMMINGCODE_H

#include <vector>

std::vector<bool> encode(std::vector<bool> input, int totalBits);
int calculateErrorSyndrome(std::vector<bool> noisy_encoded);
std::vector<bool> decode(std::vector<bool> noisy_encoded, int error_syndrome);

#endif