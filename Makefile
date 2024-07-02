CC = gcc
SRC_INCLUDE_DIR = src
TESTS_INCLUDE_DIR = tests
INTERNAL_INCLUDE = -I$(SRC_INCLUDE_DIR) -I$(TESTS_INCLUDE_DIR)
EXTERNAL_INCLUDE = $(shell pkg-config --cflags raylib) 
CFLAGS = -Wall -std=c99 -O2 $(INTERNAL_INCLUDE) $(EXTERNAL_INCLUDE)
LDFLAGS = $(shell pkg-config --libs raylib)

SRC_DIR = src
SRC_MAIN = $(SRC_DIR)/main
SRC_OUTPUT = catch_up.out
SRC = $(wildcard $(SRC_DIR)/*.c)
SRC_OBJ = $(SRC:.c=.o)
SRC_OBJ_WITHOUT_MAIN = $(filter-out $(SRC_MAIN).o, $(SRC_OBJ))

TESTS_DIR = tests
TESTS_MAIN = $(TESTS_DIR)/tests_main
TESTS_OUTPUT = tests_catch_up.out
TESTS_SRC = $(wildcard $(TESTS_DIR)/*.c)
TESTS_OBJ = $(TESTS_SRC:.c=.o)

all: $(SRC_OUTPUT)

$(SRC_OUTPUT): $(SRC_OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

test: $(TESTS_OUTPUT)
	./$(TESTS_OUTPUT)

$(TESTS_OUTPUT): $(TESTS_OBJ) $(SRC_OBJ_WITHOUT_MAIN)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

run: $(SRC_OUTPUT)
	./$(SRC_OUTPUT)

clean:
	rm -rf $(SRC_OBJ) $(TESTS_OBJ) $(SRC_OUTPUT) $(TESTS_OUTPUT)