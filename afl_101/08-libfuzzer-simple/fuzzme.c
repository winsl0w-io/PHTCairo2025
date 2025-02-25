#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>



 __attribute__((noinline)) void fuzz_one_input(char *input, int length) {
    char buffer[10];

    //printf("Enter some text: ");
    //fgets(input, sizeof(input), stdin);

    // Nested if statements to check for the trigger pattern directly
    if (input[0] == 't') {
        if (input[1] == 'r') {
            if (input[2] == 'i') {
                if (input[3] == 'g') {
                    if (input[4] == 'g') {
                        if (input[5] == 'e') {
                            if (input[6] == 'r') {
                                strcpy(buffer, input); // Unsafe copy
                            }
                        }
                    }
                }
            }
        }
    }

}


int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size){
	fuzz_one_input(Data, Size);

	return 0;

}

/*
int main() {
	size_t size;
	char input[100];

	size = read(0, input, sizeof(input) - 1);

	if (size < 0)
		exit(1);

	input[size] = '\0';

    fuzz_one_input(input, size);

    return 0;
}
*/
