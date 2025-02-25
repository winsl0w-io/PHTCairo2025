#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>


int inited = 0;

void fuzz_one_input(char *input, int length) {

	if(inited == 0){
		printf("[-] Lib is not inited, please do before you can use it\n");
		return;
	}

	char buffer[10];

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

	printf("You entered: %s of lenght: %d\n", input, length);
}


int init(){
	printf("[-] Init the library\n");

	int random = rand()%3;

	sleep(random);

	inited = 1;
	
	return 0;
}
