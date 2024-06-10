CC=cc
CFLAGS=-Wall -Wextra
LDFLAGS=-lcheck -lm -pthread -lsubunit

BIN_DIR=./bin
TEST_BIN=$(BIN_DIR)/check_array
SRC_DIR=./tests
TEST_SRC=$(SRC_DIR)/check_array.c

all: test

clean:
	rm -f $(BIN_DIR)/*.o $(TEST_BIN)

test: $(TEST_BIN)
	$(TEST_BIN)

$(TEST_BIN): $(TEST_SRC)
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_BIN) $(LDFLAGS)

