CC=clang

CFLAGS=

TARGET=fuzzme

SRC=fuzzme.c

all:$(TARGET)

$(TARGET):$(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)
clean:
	rm -f $(TARGET)

fuzz:
	afl-fuzz -Q -i in -o out -- ./fuzzme
