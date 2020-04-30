CXX = g++
CXXFLAGS = -std=gnu++11 -Wall -Werror

TARGET = main.exe
TESTTARGET = test.exe
TARGETDIR = ./bin

INCLUDES = -I. \
           -Igoogletest/googletest/include

SRCDIR = ./src
SRCS = $(wildcard $(SRCDIR)/*.cc)
OBJS := $(SRCS:.cc=.o)

TESTDIR = ./test
TESTSRCS = $(wildcard $(TESTDIR)/test_*.cc)
TESTOBJS := $(TESTSRCS:.cc=.o)

GTESTLIB += ./googletest/build/lib/libgtest.a \
            ./googletest/build/lib/libgtest_main.a
GTESTFLAGS = -Lgoogletest/build/lib \
             -lgtest \
             -lgtest_main \
             -lpthread

.PHONY: all clean
.SUFFIXES: .c .cc .o

all: $(TARGETDIR)/$(TARGET) $(TARGETDIR)/$(TESTTARGET)

$(TARGETDIR)/$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

$(TARGETDIR)/$(TESTTARGET): $(filter-out %main.o, $(OBJS)) $(TESTOBJS)
	$(CXX) -o $@ $^ $(GTESTLIB) $(GTESTFLAGS)
	$@  # Execute gtest

.cc.o:
	$(CXX) $(INCLUDES) $(CXXFLAGS) -o $@ -c $^
.cc:
	$(CXX) $(INCLUDES) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(TESTOBJS)
	rm -f ./bin/*.exe
	rm -f ./src/*.o
	rm -f ./test/*.o
