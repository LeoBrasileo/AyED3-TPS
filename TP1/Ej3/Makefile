CC = g++
CPPFLAGS = -g -std=c++14 -Wall -O0
OUTPUT_PATH := bin

.PHONY: all clean

all: benchmark

benchmark: app
	@time $(OUTPUT_PATH)/app < test.txt

app: main.cpp
	@mkdir -p $(OUTPUT_PATH)
	$(CC) $(CPPFLAGS) $< -o $(OUTPUT_PATH)/app

clean:
	rm -f *.o
	rm -rf $(OUTPUT_PATH)
