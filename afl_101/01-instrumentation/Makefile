CC=afl-clang

CFLAGS=

TARGET=fuzzme

SRC=fuzzme.c

all:$(TARGET)

$(TARGET):$(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)
clean:
	rm -f $(TARGET)

fuzz:
	afl-fuzz -i in -o out -- ./$(TARGET)
