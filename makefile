OUT_FILE = shell
CC = gcc 
CFLAGS = -Wall -pedantic -Wextra -Wconversion -Wshadow -std=gnu99
SRC_DIR = src
OBJECT_FILES = proj1.o

$(OUT_FILE): $(OBJECT_FILES)
	$(CC) $(CFLAGS)  -o $(OUT_FILE) $^
	rm -rf *.o

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OUT_FILE)
	rm -rf *~