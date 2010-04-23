# 
#  Makefile for tests
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
CFLAGS=-W -Wall -I$(CURDIR)/../ \
			`Magick++-config --cppflags`

# linking flags
LDFLAGS=-lgtest \
			`Magick++-config --ldflags --libs`


# =============
# = dir names =
# =============
SRC_DIR=src
OBJ_DIR=obj

MAIN_TREE_OBJ_DIR=$(CURDIR)/../obj


# ==================
# = shell commands =
# ==================
mkdir=mkdir -p $(1)
RM=rm -rf


# ==============
# = File lists =
# ==============

# SOURCES

# Tests corresponding to classes
CLASS_TEST_SRC=util/Messages.hpp \
					fancy/Image.hpp \
					fancy/IMagickImage.hpp

# Standalone and other misc. tests
OTHER_TEST_SRC=

# Full test sources list
TEST_SRC=$(CLASS_TEST_SRC) $(OTHER_TEST_SRC)

# Test sources with dirs
TEST_SRC_LIST=$(patsubst %,$(SRC_DIR)/%,$(TEST_SRC))



# OBJECTS

# Main build tree objects, corresponding to tests
CLASS_OBJ_LIST=$(patsubst %.hpp,$(MAIN_TREE_OBJ_DIR)/%.o,$(CLASS_TEST_SRC))

# Other objects, needed to build tests
OTHER_OBJ_LIST=

# Full objects list
OBJ_LIST=$(CLASS_OBJ_LIST) $(OTHER_OBJ_LIST)




# EXECUTABLES

EXEC=fancywork_test

# =================
# = BUILD TARGETS =
# =================
all: $(EXEC)

$(EXEC): $(OBJ_DIR)/test_main.o $(OBJ_LIST)
	$(CC) $^ -o $(EXEC) $(LDFLAGS)

$(OBJ_DIR)/test_main.o: $(SRC_DIR)/main.cpp $(TEST_SRC_LIST)
	$(call mkdir,$(OBJ_DIR))
	$(CC) -c $< -o $@ $(CFLAGS)


# =================
# = CLEAN TARGETS =
# =================
.PHONY: clean mrproper rebuild

clean:
	$(RM) $(OBJ_DIR)

mrproper: clean
	$(RM) $(EXEC)

rebuild: mrproper all
