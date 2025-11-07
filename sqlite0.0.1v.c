#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char* buffer;   //Pointer to actual text string
    size_t buffer_length;   //Total allocated size of the buffer
    ssize_t input_length;   //Number of characters actually read
} InputBuffer;

InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    // Initialize all fields to a clean "empty" state
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}



void print_prompt() {
    printf("db > ");
}

void read_input (InputBuffer* input_buffer) {
    ssize_t bytes_read = 
        // Pass address of buffer pointer (char**)
        getline(&(input_buffer->buffer), 
                // Pass address of length variable (size_t*)
                &(input_buffer->buffer_length), 
                // Read from the keyboard
                stdin);

    
    if (bytes_read <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    //e.g., bytes_read = 6 (for "hello\n")
    
    // Store the useful length (5)
    input_buffer->input_length = bytes_read - 1;
    // Overwrite the newline at buffer[5] with a 0
    input_buffer->buffer[bytes_read - 1] = 0;
}


void close_input_buffer (InputBuffer* input_buffer) {
    // Free the contents (the string buffer)
    free(input_buffer->buffer);
    // Free the container (the struct)
    free(input_buffer);
}




int main(int args, char* argv[]) {
    // Allocate memory for our input buffer on the heap
    InputBuffer* input_buffer = new_input_buffer();
    // Start the infinite REFL loop
    while (true) {
        print_prompt();
        read_input(input_buffer);

        // Evaluate thr input
        if (strcmp(input_buffer->buffer, ".exit") == 0) {
            // Clean up and exit
            close_input_buffer(input_buffer);
            exit(EXIT_SUCCESS);
        } else {
            // print error and loop again
            printf("Unrecognized command '%s'. \n", input_buffer->buffer);
            }
        }
    }
