CC = gcc
CFLAGS = -Wall
LIBS = -lncurses
TARGET = cli-clock

all: $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) main.c -o $(TARGET) $(LIBS)

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/$(TARGET)

uninstall:
	rm -f /usr/local/bin/$(TARGET)

clean:
	rm -f $(TARGET)
