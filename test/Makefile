CC=g++

BOOST_PATH=/usr/local/src/boost_1_42_0
BOOST_INC_PATH=$(BOOST_PATH)
BOOST_LIB_PATH=$(BOOST_PATH)/stage/lib

CFLAGS=-W -Wall -I../ \
			-I$(BOOST_INC_PATH) \
			`Magick++-config --cppflags`
LDFLAGS=-lgtest \
			-L$(BOOST_LIB_PATH) \
			`Magick++-config --ldflags --libs`

SRC_DIR=src
OBJ_DIR=obj

mkdir=mkdir -p $(1)
RM=rm -rf

# Tests corresponding to classes
CLASS_TEST_SRC=util/Messages.hpp \
					fancy/Image.hpp \
					fancy/IMagickImage.hpp

OTHER_TEST_SRC=sample_test.hpp
TEST_SRC=$(CLASS_TEST_SRC) $(OTHER_TEST_SRC)
TEST_SRC_LIST=$(patsubst %,$(SRC_DIR)/%,$(TEST_SRC))

OBJ_LIST=$(patsubst %.hpp,../obj/%.o,$(CLASS_TEST_SRC))

# OBJ=util/Messages.o\
# 		fancy/Image.o\
# 		fancy/IMagickImage.o
# OBJ_LIST=$(patsubst %,../obj/%,$(OBJ))

EXEC=fancywork_test

all: $(EXEC)

$(EXEC): $(OBJ_DIR)/test_main.o $(OBJ_LIST)
	$(CC) $^ -o $(EXEC) $(LDFLAGS)

$(OBJ_DIR)/test_main.o: $(SRC_DIR)/main.cpp $(TEST_SRC_LIST)
	$(call mkdir,$(OBJ_DIR))
	$(CC) -c $< -o $@ $(CFLAGS)



.PHONY: clean mrproper rebuild

clean:
	$(RM) $(OBJ_DIR)

mrproper: clean
	$(RM) $(EXEC)

rebuild: mrproper all
