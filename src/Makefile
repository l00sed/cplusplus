# Compiler: gcc for C program, g++ for C++
CC = g++
# Compiler flags:
# -g 		-- adds debugging information to the executable
# -Wall -- turns on most compiler warnings
CFLAGS = -g -Wall

# The build target
TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).cpp
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp

clean: $(RM) $(TARGET)
