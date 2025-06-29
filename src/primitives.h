#pragma once
#include "game.h"

enum Primitives { TRIANGLE, RECT };

void createTriangle(unsigned int *VAO, unsigned int *VBO);
void createRect(unsigned int *VAO, unsigned int *VBO, unsigned int *EBO);
