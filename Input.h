#ifndef INPUT_H
#define INPUT_H

#include "Shared.h"

//The 'Input' process' code, split into after the program forks.
void input(int pipeToOutput[], int pipeToTranslate[]);

#endif //INPUT_H
