# 
#  Makefile for main build tree
#  fancywork
#  
#  Created by msqui on 2010-04-23.
#  Copyright 2010 greenfrog. All rights reserved.
# 

# =============
# = VARIABLES =
# =============

# =======================
# = compiler attributes =
# =======================
CC=g++

# compilation flags
CFLAGS=-W -Wall -pthread \
			`Magick++-config --cppflags`

# linking flags
LDFLAGS=`Magick++-config --ldflags --libs`


# ===================
# = file extensions =
# ===================
S_EXT=cpp
O_EXT=o


# =============
# = dir names =
# =============
SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin


# ==================
# = shell commands =
# ==================
mkdir=mkdir -p $(1)
RM=rm -rf


# ==============
# = File lists =
# ==============

# SOURCES

# source files list
SRC=main.cpp\
		util/Messages.cpp\
		fancy/Image.cpp\
		fancy/IMagickImage.cpp

# sources with dirs
SRC_LIST=$(patsubst %,$(SRC_DIR)/%,$(SRC))



# OBJECTS

# obj files corresponding to sources
OBJ_LIST=$(patsubst %.$(S_EXT),$(OBJ_DIR)/%.$(O_EXT),$(SRC))



# EXECUTABLES
EXEC=fancywork
TEST_EXEC=test/fancywork_test


# =================
# = BUILD TARGETS =
# =================
all: $(EXEC)

$(EXEC): $(OBJ_LIST)
	$(call mkdir,$(BIN_DIR))
	$(CC) $^ -o $(BIN_DIR)/$(EXEC) $(LDFLAGS)

$(OBJ_DIR)/%.$(O_EXT): $(SRC_DIR)/%.$(S_EXT)
	$(call mkdir,$(dir $@))
	$(CC) -c $< -o $@ $(CFLAGS)


# ================
# = TEST TARGETS =
# ================
.PHONY: test
test: all
	@ cd test; make
	@ $(TEST_EXEC)

clean_test:
	@ cd test; make mrproper


# =================
# = CLEAN TARGETS =
# =================
.PHONY: clean mrproper rebuild

clean:
	$(RM) $(OBJ_DIR)

mrproper: clean
	$(RM) $(BIN_DIR)

rebuild: mrproper all
