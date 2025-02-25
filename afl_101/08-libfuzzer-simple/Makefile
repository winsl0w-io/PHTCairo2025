CC=clang

CFLAGS=-fsanitize=fuzzer -g2

TARGET=fuzzme

SRC=fuzzme.c

all:$(TARGET)

$(TARGET):$(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)
clean:
	rm -f $(TARGET)

fuzz:
	./$(TARGET) ./CORPUS
