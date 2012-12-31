#include "railfence.h"

int main(int argc, char** argv) {
  int depth;
  char* direction;
  char* input;
  char* output;
  FILE* output_file;

  check_parameters(argc, argv);
  
  depth = atoi(argv[3]);
  direction = argv[4];
  input = read_input(argv[1]);
  
  if ((output_file = fopen(argv[2], "w")) == NULL) {
    fprintf(stderr, "Error: Cannot open the output file.");
  }

  if (strcmp(direction, "1") == 0) {
    output = encrypt_string(input, depth);
    fputs(output, output_file);
  } else {
    output = decrypt_string(input, depth);
    fputs(output, output_file);
  }

  fclose(output_file);
    
  free(input);
  input = NULL;

  free(output);
  output = NULL;
 
  return 0;
}

void check_parameters(int argc, char** argv) {
  int depth;
  FILE* file;

  if (argc != 5) {
    fprintf(stderr, "Usage: ./railfence <input file> <ouput file> <depth> <encode/decode>\n");
    exit(1);
  }

  if ((file = fopen(argv[1], "r"))) {
    fclose(file);
  } else {
    fprintf(stderr, "Error: Input file not found.\n");
    exit(2);
  }

  depth = atoi(argv[3]);
  if (depth <= 0 || depth >= 100) {
    fprintf(stderr, "Error: Depth must be greater than 0 and less than 100");
    exit(3);
  }

  if (strcmp(argv[4], "1") != 0 && strcmp(argv[4], "0") != 0) {
    fprintf(stderr, "Error: Encode/Decode must be set to either 0 or 1\n");
    exit(4);
  }
}

char* read_input(char* filename) {
  int input_size = 1024;
  int buffer_fills = 1;
  char buffer[input_size];
  char* input = (char*) malloc(sizeof(char) * input_size);
  FILE* input_file = fopen(filename, "r");

  input[0] = '\0';
  while (fgets(buffer, input_size, input_file) != NULL) {
    // Remove any newline from the end of the buffer.
    if (buffer[strlen(buffer) - 1] == '\n')
      buffer[strlen(buffer) - 1] = '\0';

    input = (char*) realloc(input, buffer_fills * input_size);
    memcpy(&(input[(buffer_fills - 1) * input_size]), buffer, input_size);
    ++buffer_fills;
  }

  fclose(input_file);
  return input;
}

char* encrypt_string(char* input, int depth) {
  int input_length = strlen(input);
  int number_full_columns = input_length / depth;
  int number_full_rows = input_length % depth == 0 ? depth : input_length % depth;
  int total_columns = input_length % depth == 0 ? number_full_columns : number_full_columns + 1;
  char* ciphertext = (char*) malloc((sizeof(char) * input_length) + 1);
  char rail_fence[depth][total_columns];

  int row_counter;
  int column_counter;
  int character_counter;

  character_counter = 0;
  for (column_counter = 0; column_counter < total_columns; ++column_counter) {
    for (row_counter = 0; row_counter < depth; ++row_counter) {
      if (character_counter < input_length) {
	rail_fence[row_counter][column_counter] = input[character_counter];
	++character_counter;
      }
    }
  } 

  character_counter = 0;
  
  // Read full rows first.
  for (row_counter = 0; row_counter < number_full_rows; ++row_counter) {
    for (column_counter = 0; column_counter < total_columns; ++column_counter) {
      ciphertext[character_counter] = rail_fence[row_counter][column_counter];
      ++character_counter;
    }
  }
  
  // Now read the remaining rows.
  for (; row_counter < depth; ++row_counter) {
    for (column_counter = 0; column_counter < total_columns - 1; ++column_counter) {
      ciphertext[character_counter] = rail_fence[row_counter][column_counter];
      ++character_counter;
    }
  }

  ciphertext[input_length] = '\0';
  return ciphertext;
}

char* decrypt_string(char* input, int depth) {
  int input_length = strlen(input);
  int number_full_columns = input_length / depth;
  int number_full_rows = input_length % depth == 0 ? depth : input_length % depth;
  int total_columns = input_length % depth == 0 ? number_full_columns : number_full_columns + 1;
  char* plaintext = (char*) malloc((sizeof(char) * input_length) + 1);
  char rail_fence[depth][total_columns];

  int row_counter;
  int column_counter;
  int character_counter = 0;

  // Write full rows first.
  for (row_counter = 0; row_counter < number_full_rows; ++row_counter) {
    for (column_counter = 0; column_counter < total_columns; ++column_counter) {
      rail_fence[row_counter][column_counter] = input[character_counter];
      ++character_counter;
    }
  }
  
  // Now write the remaining rows.
  for (; row_counter < depth; ++row_counter) {
    for (column_counter = 0; column_counter < total_columns - 1; ++column_counter) {
      rail_fence[row_counter][column_counter] = input[character_counter];
      ++character_counter;
    }
  }
  
  character_counter = 0;
  for (column_counter = 0; column_counter < total_columns; ++column_counter) {
    for (row_counter = 0; row_counter < depth; ++row_counter) {
      if (character_counter < input_length) {
	plaintext[character_counter] = rail_fence[row_counter][column_counter];
	++character_counter;
      }
    }
  }
  
  plaintext[input_length] = '\0';
  return plaintext;
}
