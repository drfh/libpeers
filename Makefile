TARGET_EXEC ?= testpeers
TARGET_LIB ?= libpeers.a

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

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


libpeers.o:
	gcc src/p2plib.c -o build/libpeers.o

libpeers: libpeers.o node.o http.o sockets.o uuid4.o
	ar rcs libpeers.a libpeers.o node.o http.o sockets.o uuid4.o


.PHONY: clean
clean:
	rm -f libpeers *.o *.a *.gch
	rm -rf build/
