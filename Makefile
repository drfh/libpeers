TARGET_EXEC ?= testpeers
TARGET_LIB ?= libpeers.a

BUILD_DIR ?= ./build
TEST_DIR ?= $(BUILD_DIR)/tests
SRC_DIRS ?= ./src

MKDIR_P ?= mkdir -p
CC ?= gcc

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -o -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CFLAGS ?= $(INC_FLAGS) -Wall -fPIC -g
FLAGS ?= -std=c11 -Iinclude
LDFLAGS ?= -shared

#	Addind JSON support
CFLAGS += $(shell pkg-config --cflags json-c)
LDFLAGS += $(shell pkg-config --libs json-c)

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

all: libpeers tests

libpeers: libpeers.a libpeers.so

libpeers.a:
	$(MKDIR_P) $(BUILD_DIR)
	$(CC) $(CFLAGS) -c src/http.c -o build/http.o
	$(CC) $(CFLAGS) -c src/util/uuid4.c -o build/uuid4.o
	$(CC) $(CFLAGS) -c src/socks.c -o build/socks.o
	$(CC) $(CFLAGS) -c src/node.c -o build/node.o

	$(CC) $(CFLAGS) -c src/libpeers.c -o build/libpeers.o

	ar rs $(BUILD_DIR)/libpeers.a $(BUILD_DIR)/libpeers.o $(BUILD_DIR)/node.o $(BUILD_DIR)/socks.o $(BUILD_DIR)/uuid4.o


libpeers.so:
	gcc -shared -o libpeers.so $(BUILD_DIR)/libpeers.o $(BUILD_DIR)/node.o $(BUILD_DIR)/socks.o $(BUILD_DIR)/uuid4.o



tests: test1

test1: libpeers.a
	$(MKDIR_P) $(TEST_DIR)
	$(CC) -I ./src/ -c tests/test1.c -o $(TEST_DIR)/test1.o
	$(CC) -o $(TEST_DIR)/test1 $(TEST_DIR)/test1.o build/libpeers.a


.PHONY: clean
clean:
	rm -f libpeers *.o *.a *.gch
	rm -rf build/
