#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <limits.h>


void* (*fuzz_one_input)(char*, int);
void* (*init)();


__AFL_FUZZ_INIT();

int main(int argc, char **argv){

	void *handle = dlopen("./libfuzz.so", RTLD_LAZY);

	fuzz_one_input = dlsym(handle, "fuzz_one_input");
	init = dlsym(handle, "init");

	if (handle == NULL){
		printf("Couldn't get the handle to fuzz_one_input\n");
		exit(1);
	}

	init();

	__AFL_INIT();

	unsigned char *buf = __AFL_FUZZ_TESTCASE_BUF;


	while (__AFL_LOOP(UINT_MAX)){
		unsigned int len = __AFL_FUZZ_TESTCASE_LEN;

	fuzz_one_input(buf, len);

	}

	return 0;



}
