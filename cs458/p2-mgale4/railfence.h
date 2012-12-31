#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Function Declarations
void check_parameters(int argc, char** argv);
char* read_input(char* filename);
char* encrypt_string(char* input, int depth);
char* decrypt_string(char* input, int depth);
