# Variable definitions

# library paths
BOOST_PATH=/usr/local/src/boost_1_42_0
BOOST_INC_PATH=$(BOOST_PATH)
BOOST_LIB_PATH=$(BOOST_PATH)/stage/lib

# compiler attributes
CC=g++
CFLAGS=-W -Wall -pthread `Magick++-config --cppflags`\
				-I$(BOOST_INC_PATH)

LDFLAGS=`Magick++-config --ldflags --libs`\
				-L$(BOOST_LIB_PATH)

# extensions
S_EXT=cpp
O_EXT=o

# dir names
SRC_DIR=src
OBJ_DIR=obj
BIN_DIR=bin

# shell commands
mkdir=mkdir -p $(1)
RM=rm -rf

# file lists

SRC=main.cpp\
		util/Messages.cpp\
		fancy/Image.cpp\
		fancy/IMagickImage.cpp

SRC_LIST=$(patsubst %,$(SRC_DIR)/%,$(SRC))
OBJ=$(patsubst %.$(S_EXT),%.$(O_EXT),$(SRC))
OBJ_LIST=$(patsubst %,$(OBJ_DIR)/%,$(OBJ))

# artifact name
EXEC=fancywork


# Build targets

all: $(EXEC)

$(EXEC): $(OBJ_LIST)
	$(call mkdir,$(BIN_DIR))
	$(CC) $^ -o $(BIN_DIR)/$(EXEC) $(LDFLAGS)

$(OBJ_DIR)/%.$(O_EXT): $(SRC_DIR)/%.$(S_EXT)
	$(call mkdir,$(dir $@))
	$(CC) -c $< -o $@ $(CFLAGS)

# Clear targets

.PHONY: clean mrproper

clean:
	$(RM) $(OBJ_DIR)

mrproper: clean
	$(RM) $(BIN_DIR)

