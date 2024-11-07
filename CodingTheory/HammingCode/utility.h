#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <string>

std::vector<bool> stringToVecBool(std::string code);
std::string vecBoolToString(std::vector<bool> vector_code);
std::vector<bool> flipBit(std::vector<bool> encoded);
int calculateNumberParityBits(int numDataBits);

#endif