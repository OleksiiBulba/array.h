CC=cc
CFLAGS=-Wall -Wextra
LDFLAGS=-lcheck -lm -pthread -lsubunit

BIN_DIR=./bin
SRC_DIR=./tests
TEST_BINS=$(BIN_DIR)/check_array $(BIN_DIR)/check_array_out_of_bounds
TEST_SRCS=$(SRC_DIR)/check_array.c $(SRC_DIR)/check_array_out_of_bounds.c

all: test

clean:
	rm -f $(BIN_DIR)/*.o $(TEST_BINS)

test: $(TEST_BINS)
	$(BIN_DIR)/check_array
	$(BIN_DIR)/check_array_out_of_bounds

$(BIN_DIR)/check_array: $(SRC_DIR)/check_array.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

$(BIN_DIR)/check_array_out_of_bounds: $(SRC_DIR)/check_array_out_of_bounds.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

