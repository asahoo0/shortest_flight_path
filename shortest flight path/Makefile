EXE = final_proj
TEST = test

OBJS = main.o graph.o cs225/HSLAPixel.o cs225/PNG.o cs225/lodepng/lodepng.o
TEST_OBJS = test.o graph.o catchmain.o cs225/HSLAPixel.o cs225/PNG.o cs225/lodepng/lodepng.o

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

# Custom Clang version enforcement logic:
ccred=$(shell echo -e "\033[0;31m")
ccyellow=$(shell echo -e "\033[0;33m")
ccend=$(shell echo -e "\033[0m")

IS_EWS=$(shell hostname | grep "ews.illinois.edu") 
IS_CORRECT_CLANG=$(shell clang -v 2>&1 | grep "version 6")
ifneq ($(strip $(IS_EWS)),)
ifeq ($(strip $(IS_CORRECT_CLANG)),)
CLANG_VERSION_MSG = $(error $(ccred) On EWS, please run 'module load llvm/6.0.1' first when running CS225 assignments. $(ccend))
endif
else
ifneq ($(strip $(SKIP_EWS_CHECK)),True)
CLANG_VERSION_MSG = $(warning $(ccyellow) Looks like you are not on EWS. Be sure to test on EWS before the deadline. $(ccend))
endif
endif

.PHONY: all test clean output_msg

all : $(EXE)

$(TEST) : output_msg $(TEST_OBJS)
	$(LD) $(TEST_OBJS) $(LDFLAGS) -o $(TEST)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXE) : output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXE)

main.o : main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

graph.o : graph/graph.cpp graph/graph.h graph/edge.h
	$(CXX) $(CXXFLAGS) graph/graph.cpp

edge.o : graph/edge.h
	$(CXX) $(CXXFLAGS) graph/edge.h

test.o : tests/test.cpp graph/graph.h graph/edge.h
	$(CXX) $(CXXFLAGS) tests/test.cpp

catchmain.o : tests/catch/catch.hpp tests/catch/catchmain.cpp
	$(CXX) $(CXXFLAGS) tests/catch/catchmain.cpp

clean :
	-rm -f *.o $(EXE) $(TEST)
