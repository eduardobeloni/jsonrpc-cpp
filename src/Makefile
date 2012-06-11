LIBNAME = libjsonrpc

CXX ?= g++
AR ?= ar
RM = rm -f

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
DEP = $(OBJ:.o=.d)
TARGET = $(LIBNAME).so
TARGET_ST = $(LIBNAME).a
CXXFLAGS += -Wall -O2 -fpic
LDFLAGS += -lcurl -lpthread

ifeq ($(ARCH), arm)
CXX = arm-linux-g++
AR = arm-linux-ar
endif

default: $(TARGET) $(TARGET_ST)

$(TARGET): $(OBJ)
	$(CXX) $(LDFLAGS) -shared $^ -o $@

$(TARGET_ST): $(OBJ)
	$(AR) rcs $@ $^

-include $(DEP)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(C_STD) -c $< -o $@
	$(CXX) -MM $(CXXFLAGS) $< > $*.d

clean:
	$(RM) $(TARGET) *.o *.so *.a *.d
