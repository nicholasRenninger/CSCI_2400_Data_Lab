#
# Makefile that builds btest and other helper programs for the CS:APP data lab
# 
CC = gcc
CFLAGS += -O -Wall -m32
CPPFLAGS += -Iinclude # -I is a preprocessor flag, not a compiler flag
CFLAGS += -O -Wall -m32 # some warnings about bad code, 32-bit only
LDFLAGS += -Llib # -L is a linker flag
LDLIBS += -lm # Left empty if no libs are needed

SRC_DIR = src
OBJ_DIR = obj
TARGET_DIR = bin
TARGET = btest

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean

all: $(TARGET) fshow ishow

# Main test target
$(TARGET_DIR)/$(TARGET): $(OBJ)
    $(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
    $(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# show targets
$(TARGET_DIR)/fshow: SHOW_OBJ/fshow.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(TARGET_DIR)/ishow: SHOW_OBJ/ishow.o
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

SHOW_OBJ/%.o: SHOW_SRC/%.c
    $(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Forces a recompile. Used by the driver program. 
btestexplicit:
	$(CC) $(CFLAGS) $(LIBS) -o btest bits.c btest.c decl.c tests.c 

clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET_DIR)/* *~


