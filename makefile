TARGETS = $(BIN1)

BIN1 = connector
BIN1_OBJS = $(OBJS)
BIN1_LIBS = pthread log4cplus mysqlcppconn
BIN1_LFLAGS = -L$(LOG4CPLUS_ROOT)/lib
INCS = -I. -I$(LOG4CPLUS_ROOT)/include
SOURCE := $(wildcard *.cpp)

OBJS := $(patsubst %.cpp,%.o,$(SOURCE))

CC := g++
CFLAGS := -std=c++11 -ggdb -Wall -O3 -Wno-deprecated -fPIC -D _FILE_OFFSET_BITS=64 $(INCS) #-m64
CXXFLAGS := $(CFLAGS)
RM := rm -f

.PHONY : all objs clean rebuild

all : $(TARGETS)

objs : $(OBJS)

clean :
	$(RM) *.o
	$(RM) *.d
	$(RM) *~
	$(RM) $(BIN1)

rebuild: clean all

$(BIN1) : $(BIN1_OBJS)
	$(CC) $(CFLAGS) -o $@ $(BIN1_LFLAGS) $^ $(addprefix -l,$(BIN1_LIBS))

