CC=gcc
CFLAGS=-Wall -g
LIBS=-ljson-c

# Nome do arquivo executável
TARGET=exec_ciclico

# Nome do arquivo fonte
SRC=exec_ciclico.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

clean:
	rm -f $(TARGET)

.PHONY: clean
