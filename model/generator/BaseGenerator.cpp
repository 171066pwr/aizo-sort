#include "BaseGenerator.h"

std::random_device BaseGenerator::rd;
std::mt19937 BaseGenerator::gen{BaseGenerator::rd()};