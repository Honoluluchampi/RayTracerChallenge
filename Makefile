UNIT_NAME	=matrix
LIB_NAME	=renderer

UNAME 		= $(shell uname)
ifeq ($(UNAME), Linux)
GTEST_DIR	=/home/honolulu/programs/downloaded-libraries/googletest/googletest
else
GTEST_DIR	=/Users/toyotariku/downloaded_libralies/googletest/googletest
endif

SRC_DIR		=./src
INC_DIR		=./include
TEST_DIR	=./test
LIB_DIR		=./lib
BIN_DIR		=./bin
OBJ_DIR		=./obj
TEST_OBJ_DIR=./test_obj
INCS 	   +=-I$(INC_DIR)

UNAME 	   := $(shell uname -s)
CXX=g++
CXXFLAGS 	=-g -Wall
SRCS    	=$(wildcard $(SRC_DIR)/*.cpp)
TARGET 		=$(LIB_DIR)/lib$(LIB_NAME).a
OBJS  		=$(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.cpp=.o)))
DEPENDS 	=$(OBJS:.o=.d)

default: $(TARGET)
.PHONY: default

$(TARGET): $(OBJS)
		@[ -d $(LIB_DIR) ] || mkdir -p $(LIB_DIR)
		$(AR) rcs $(TARGET) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
		@[ -d $(OBJ_DIR) ] || mkdir -p $(OBJ_DIR)
		$(CXX) $(CXXFLAGS) $(INCS) -o $@ -c $<


TEST_SRCS 	=$(TEST_DIR)/$(UNIT_NAME)_test.cpp
TEST_TARGET =$(BIN_DIR)/$(UNIT_NAME)_test
TEST_OBJS  	=$(addprefix $(TEST_OBJ_DIR)/, $(notdir $(TEST_SRCS:.cpp=.o)))
# honolulu renderer
LIBS 	   +=-L$(LIB_DIR)
LIBS 	   +=-l$(LIB_NAME)
# png++
LIBS	   +=$(shell libpng-config --ldflags)

CPPFLAGS   +=-isystem $(GTEST_DIR)/include
CXXFLAGS 	=-g -Wall -Wextra -pthread

# All Google Test headers
GTEST_HEADERS 	= $(GTEST_DIR)/include/gtest/*.h $(GTEST_DIR)/include/gtest/internal/*.h
GTEST_SRCS_ 	= $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# build google test
$(OBJ_DIR)/gtest-all.o : $(GTEST_SRCS_)
		$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
                    -o $@ $(GTEST_DIR)/src/gtest-all.cc

$(OBJ_DIR)/gtest_main.o : $(GTEST_SRCS_)
		$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
                    -o $@ $(GTEST_DIR)/src/gtest_main.cc

$(LIB_DIR)/gtest.a : $(OBJ_DIR)/gtest-all.o
		$(AR) $(ARFLAGS) $@ $^

$(LIB_DIR)/gtest_main.a : $(OBJ_DIR)/gtest-all.o $(OBJ_DIR)/gtest_main.o
		$(AR) $(ARFLAGS) $@ $^

.PHONY: test
test: $(TEST_TARGET)
$(TEST_TARGET): $(OBJS) $(TEST_OBJS) $(LIB_DIR)/gtest_main.a
		@[ -d $(BIN_DIR) ] || mkdir -p $(BIN_DIR)
		$(CXX) $(LDFLAGS) -o $@ $(TEST_OBJS) $(LIBS)\
		$(LIB_DIR)/gtest_main.a -lpthread

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp $(GTEST_HEADERS)
		@[ -d $(TEST_OBJ_DIR) ] || mkdir -p $(TEST_OBJ_DIR)
		$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INCS) -o $@ -c $<

.PHONY: clean
clean:
		rm -f $(TARGET) $(TEST_TARGET) $(OBJS) $(TEST_OBJS)

.PHONY: run
run:
	$(TEST_TARGET)

.PHONY: all
all:
	make clean
	make
	make test
	make run

.PHONY: diff
diff:
	make
	make test
	make run

-include $(DEPENDS)