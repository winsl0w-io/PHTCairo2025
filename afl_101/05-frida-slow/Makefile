CC=clang

CFLAGS=

TARGET=fuzzme

SRC=fuzzme.c

all:$(TARGET)

$(TARGET):$(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)
clean:
	rm -f $(TARGET)

fuzz-qemu:
	afl-fuzz -Q -i in -o out -t 3000 -- ./fuzzme
fuzz-frida:
	afl-fuzz -O -i in -o out -t 3000 -- ./fuzzme

fuzz-frida-persistent:
	AFL_FRIDA_JS_SCRIPT=afl.js.script afl-fuzz -O -i in -o out -t 3000 -- ./fuzzme
