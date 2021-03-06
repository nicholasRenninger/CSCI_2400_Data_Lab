#
# Makefile that builds btest and other helper programs for the CS:APP data lab
# 
CC = gcc
CFLAGS += -O -Wall -m32
CPPFLAGS += -Iinc # -I is a preprocessor flag, not a compiler flag
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

all: $(TARGET_DIR)/$(TARGET) $(TARGET_DIR)/fshow $(TARGET_DIR)/ishow

# Main test target
$(TARGET_DIR)/$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# show targets
$(TARGET_DIR)/fshow: show_obj/fshow.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(TARGET_DIR)/ishow: show_obj/ishow.o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

show_obj/%.o: show_src/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Forces a recompile. Used by the driver program. 
btestexplicit: $(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@
	$(CC) $(CFLAGS) $(LIBS) -o btest $(SRC_DIR)/bits.c $(SRC_DIR)/btest.c $(SRC_DIR)/decl.c $(SRC_DIR)/tests.c 

clean:
	rm -f $(OBJ_DIR)/*.o *~


