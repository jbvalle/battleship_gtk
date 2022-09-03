.PHONY= clean run memleak

#=======================#
#== Compiler Binaries ==#
#=======================#

CC=gcc

#=================#
#== Directories ==#
#=================#

SRC_DIR=src

OBJ_DIR=obj

INC_DIR=inc

#====================#
#== Compiler FLAGS ==#
#====================#

INC_FLAGS=-I./INC_DIR

gtk_FLAGS=`pkg-config gtk+-3.0 --cflags --libs`

CFLAGS=-g -Wall -Wextra -pedantic 

VFLAGS=--leak-check=full --track-origins=yes

#=============================#
#== Object and Source Files ==#
#=============================#

SRCS=$(wildcard $(SRC_DIR)/*.c)

OBJ=$(patsubst $(SRC_DIR)/%.c, $(SRC_DIR)/$(OBJ_DIR)/%.o, $(SRCS))

TARGET=main

all: $(OBJ) $(TARGET) run

$(SRC_DIR)/$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | mkobjdir
	$(CC) -c -o $@ $^ $(gtk_FLAGS) $(CFLAGS) $(INC_FLAGS)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(gtk_FLAGS) $(CFLAGS) $(INC_FLAGS)

#===========================#
#== Miscellaneous Targets ==#
#===========================#

run:
	./$(TARGET)

memleak: $(TARGET)
	valgrind $(VFLAGS) ./$^

show:
	@echo $(OBJ)

mkobjdir:
	mkdir -p $(SRC_DIR)/$(OBJ_DIR)


clean:
	rm -rf $(TARGET) $(OBJ)
