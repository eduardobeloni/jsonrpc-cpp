LIBNAME = libjsonrpc

CXX ?= g++
AR ?= ar
RM = rm -f

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
DEP = $(OBJ:.o=.d)
TARGET = $(LIBNAME).so
TARGET_ST = $(LIBNAME).a
JSONCPP_SRC = $(wildcard ./jsoncpp/*.cpp)
JSONCPP_OBJ = $(JSONCPP_SRC:.cpp=.o)
CXXFLAGS += -Wall -O2 -fpic -I./
LDFLAGS += -lcurl -lpthread

default: $(TARGET) $(TARGET_ST)

$(TARGET): $(JSONCPP_OBJ) $(OBJ)
	$(CXX) $(LDFLAGS) -shared $^ -o $@

$(TARGET_ST): $(JSONCPP_OBJ) $(OBJ)
	$(AR) rcs $@ $^

-include $(DEP)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(C_STD) -c $< -o $@
	$(CXX) -MM $(CXXFLAGS) $< > $*.d

$(JSONCPP_OBJ):
	$(MAKE) -C jsoncpp/

clean:
	$(RM) $(TARGET) *.o *.so *.a *.d
	$(MAKE) -C ./jsoncpp clean
