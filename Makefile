CC = gcc
CFLAGS = -Wall -std=c99 -O2
INCLUDE_DIR = include
OUTPUT = app.out
TESTS_OUTPUT = app_tests.out

SRC_DIR = src
MAIN = $(SRC_DIR)/main
SRC = $(filter-out $(MAIN).c, $(wildcard $(SRC_DIR)/*.c))

TESTS_DIR = tests
TESTS_SRC = $(wildcard $(TESTS_DIR)/*.c)

MAIN_OBJ = $(MAIN).o
SRC_OBJ = $(SRC:.c=.o)
TESTS_OBJ = $(TESTS_SRC:.c=.o)

all: $(OUTPUT)

$(OUTPUT): $(MAIN_OBJ) $(SRC_OBJ) 
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE_DIR)

test: $(TESTS_OUTPUT)
	./$(TESTS_OUTPUT)

$(TESTS_OUTPUT): $(TESTS_OBJ) $(SRC_OBJ) 
	$(CC) $(CFLAGS) -o $@ $^

run: $(OUTPUT)
	./$(OUTPUT)

clean:
	rm -rf $(SRC_DIR)/*.o $(TESTS_DIR)/*.o $(OUTPUT) $(TESTS_OUTPUT) $(MAIN).o