#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include "lib/fuzz.h"


int main() {
	size_t size;
	char input[100];

	srand(time(NULL));


	size = read(0, input, sizeof(input) - 1);

	if (size < 0)
		exit(1);

	input[size] = '\0';

	init();
	
	fuzz_one_input(input, size);

    return 0;
}
