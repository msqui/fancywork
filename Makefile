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
			-I$(CURDIR)/$(SRC_DIR) \
			`Magick++-config --cppflags`

# linking flags
LDFLAGS=`Magick++-config --ldflags --libs`

# library making flags
LIBFLAGS=


# ===================
# = file extensions =
# ===================
S_EXT=cpp
H_EXT=h
O_EXT=o


# =============
# = dir names =
# =============
SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin
LIB_DIR=lib


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
COMMON_SRC=\
		main.cpp\

CLASS_SRC=\
		util/Messages.cpp\
		types/Color.cpp\
		types/Symbol.cpp\
		types/Correspondence.cpp\
		config/TransformationTable.cpp\
		fancy/Image.cpp\
		fancy/IMagickImage.cpp

SRC=$(COMMON_SRC) $(CLASS_SRC)

# sources with dirs
SRC_LIST=$(patsubst %,$(SRC_DIR)/%,$(SRC))



# OBJECTS

# common obj files
COMMON_OBJ_LIST=$(patsubst %.$(S_EXT),$(OBJ_DIR)/%.$(O_EXT),$(COMMON_SRC))

# obj files corresponding to sources
OBJ_LIST=$(patsubst %.$(S_EXT),$(OBJ_DIR)/%.$(O_EXT),$(CLASS_SRC))



# EXECUTABLES
EXEC=fancywork
LIB_EXEC=libfancywork.a
TEST_EXEC=test/fancywork_test


# =================
# = BUILD TARGETS =
# =================
all: $(EXEC)

lib: $(LIB_EXEC)

$(EXEC): $(COMMON_OBJ_LIST) $(OBJ_LIST)
	$(call mkdir,$(BIN_DIR))
	$(CC) $^ -o $(BIN_DIR)/$(EXEC) $(LDFLAGS)

$(LIB_EXEC): $(OBJ_LIST)
	$(call mkdir,$(LIB_DIR))
	ar rcs $(LIB_DIR)/$(LIB_EXEC) $^
	# $(CC) $^ -o $(LIB_DIR)/$(LIB_EXEC) $(LIBFLAGS) $(LDFLAGS)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(call mkdir,$(dir $@))
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/%.$(O_EXT): $(SRC_DIR)/%.$(S_EXT) $(SRC_DIR)/%.$(H_EXT)
	$(call mkdir,$(dir $@))
	$(CC) -c $< -o $@ $(CFLAGS)


# ================
# = TEST TARGETS =
# ================
.PHONY: test
test: lib
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
	$(RM) $(LIB_DIR)

rebuild: mrproper all
