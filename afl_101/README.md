# AFL 101

Quick AFL "Get started" with simple target to illustrate some of the common modes. This project serves as a cheat sheet to these common setups.

## The target

The target has a function named `fuzz_one_input` that takes a buffer and its length, then parses it. The buffer will be copied to a fixed-sized 10 bytes buffer if it starts with `"trigger"`, leading to a stack-based buffer overflow upon input over 10 bytes.

<details>
<summary>target.c</summary>

```c
void fuzz_one_input(char *input, int length) {
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

```

</details>


## Using the examples

Each folder contains the target source code along with a `Makefile`, allowing to build and start fuzzing, respectively with `make` and `make fuzz`.


## Setups

1. instrumentation
	- Using `AFL` in default mode, with no particular arguments
2. qemu
	- Using `AFL` with `QEMU` against the already compiled version of the target.
3. frida-simple
	- Using `AFL` with `Frida` against the already compiled version of the target.
4. frida-persistent
	- Using `AFL` with `Frida` in persistent mode against the already compiled version
5. frida-slow
	- Using `AFL` with `Frida` without persistent mode against the already compiled version of the target. Here the target is slightly modified to introduce some slow down, so we can further fix it adding persistence.
6. shared-lib-qemu
	- Using `AFL` with `Qemu` against an already compiled shared library containing our target function.
7. shared-lib-frida
	- Using `AFL` with `Frida` against an already compiled shared library containing our target function.
8. libfuzzer-simple
	- Illustrating a harness to the same target function using `libfuzzer` for comparison purpose.



