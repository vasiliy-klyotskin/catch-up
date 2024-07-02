CC = gcc
SRC_INCLUDE_DIR = src
TESTS_INCLUDE_DIR = tests
INTERNAL_INCLUDE = -I $(SRC_INCLUDE_DIR) -I $(TESTS_INCLUDE_DIR)
EXTERNAL_INCLUDE = $(shell pkg-config --cflags raylib) 
CFLAGS = -Wall -std=c99 -O2 $(INTERNAL_INCLUDE) $(EXTERNAL_INCLUDE)
LDFLAGS = $(shell pkg-config --libs raylib)

SRC_DIR = src
SRC_MAIN = $(SRC_DIR)/main
SRC = $(filter-out $(SRC_MAIN).c, $(wildcard $(SRC_DIR)/*.c))
SRC_MAIN_OBJ = $(SRC_MAIN).o
SRC_OBJ = $(SRC:.c=.o)
SRC_OUTPUT = app.out

TESTS_DIR = tests
TESTS_MAIN = $(TESTS_DIR)/tests_main
TESTS_SRC = $(wildcard $(TESTS_DIR)/*.c)
TESTS_MAIN_OBJ = $(TESTS_MAIN).o
TESTS_OBJ = $(TESTS_SRC:.c=.o)
TESTS_OUTPUT = tests_app.out

all: $(SRC_OUTPUT)

$(SRC_OUTPUT): $(SRC_MAIN_OBJ) $(SRC_OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ 

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

test: $(TESTS_OUTPUT)
	./$(TESTS_OUTPUT)

$(TESTS_OUTPUT): $(TESTS_OBJ) $(SRC_OBJ) 
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

run: $(SRC_OUTPUT)
	./$(SRC_OUTPUT)

clean:
	rm -rf $(SRC_DIR)/*.o $(TESTS_DIR)/*.o $(SRC_OUTPUT) $(TESTS_OUTPUT) $(SRC_MAIN).o $(TESTS_MAIN).o