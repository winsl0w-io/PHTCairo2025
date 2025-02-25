CC=clang

CFLAGS=-I. -L./lib

LDFLAGS=-lfuzz -Wl,-rpath,$(PWD)/lib

TARGET=./fuzzme

SRC=fuzzme.c

all:$(TARGET)

$(TARGET):$(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)
#afl-fuzz -Q -i in -o out -- ./fuzzme
#afl-fuzz -O -i in -o out -- ./fuzzme

fuzz:
	afl-fuzz -Q -i in -o out -t 3000 -- $(TARGET)
