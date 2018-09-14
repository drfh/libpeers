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

CFLAGS ?= $(INC_FLAGS) -Wall -g
FLAGS ?= -std=c11 -Iinclude
LDFLAGS ?= -pthread

#	Addind JSON support
CFLAGS += $(shell pkg-config --cflags json-c)
#CFLAGS += $(shell pkg-config --cflags pthread)
LDFLAGS += $(shell pkg-config --libs json-c)
#LDFLAGS += $(shell pkg-config --libs pthread)

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

all: libpeers tests

libpeers: libpeers.a libpeers.so

CORE_FILES=$(BUILD_DIR)/libpeers.o $(BUILD_DIR)/node.o $(BUILD_DIR)/socks.o $(BUILD_DIR)/util/uuid4.o $(BUILD_DIR)/util/arraylist.o

libpeers.a:
	$(MKDIR_P) $(BUILD_DIR)
	$(MKDIR_P) $(BUILD_DIR)/util

	$(CC) $(CFLAGS) $(LDFLAGS) -c src/util/uuid4.c -o build/util/uuid4.o
	$(CC) $(CFLAGS) $(LDFLAGS) -c src/util/arraylist.c -o build/util/arraylist.o
	$(CC) $(CFLAGS) $(LDFLAGS) -c src/http.c -o build/http.o
	$(CC) $(CFLAGS) $(LDFLAGS) -c src/socks.c -o build/socks.o
	$(CC) $(CFLAGS) $(LDFLAGS) -c src/node.c -o build/node.o

	$(CC) $(CFLAGS) $(LDFLAGS) -c src/libpeers.c -o build/libpeers.o
	ar rs $(BUILD_DIR)/libpeers.a $(CORE_FILES)


libpeers.so:
	$(CC) $(CFLAGS) $(LDFLAGS) -shared -o libpeers.so $(BUILD_DIR)/libpeers.o $(BUILD_DIR)/node.o $(BUILD_DIR)/socks.o $(BUILD_DIR)/util/uuid4.o $(BUILD_DIR)/util/arraylist.o


#libpeers.a: libpeers.o node.o http.o sockets.o uuid4.o
#	mkdir $(BUILD_DIR)/
#	ar rcs $(BUILD_DIR)/libpeers.a $(BUILD_DIR)/libpeers.o $(BUILD_DIR)/node.o $(BUILD_DIR)/http.o $(BUILD_DIR)/sockets.o $(BUILD_DIR)/uuid4.o

tests: test1 test2

test1: libpeers.a libpeers.so
	$(MKDIR_P) $(TEST_DIR)
#	echo $(INC_DIRS)
	$(CC) $(CFLAGS) $(LDFLAGS) -I ./src/ -I ./src/util -c ./tests/test1.c -o $(TEST_DIR)/test1.o
	$(CC) $(CFLAGS) -pthread -o $(TEST_DIR)/test1 $(TEST_DIR)/test1.o $(CORE_FILES)

test2: libpeers.a libpeers.so
	$(MKDIR_P) $(TEST_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -I ./src/ -I ./src/util -c ./tests/test2.c -o $(TEST_DIR)/test2.o
	$(CC) $(CFLAGS) -pthread -o $(TEST_DIR)/test2 $(TEST_DIR)/test2.o $(CORE_FILES)

.PHONY: clean
clean:
	rm -f libpeers *.o *.a *.gch
	rm -rf build/
