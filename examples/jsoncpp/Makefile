CXX ?= g++

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
DEP = $(OBJ:.o=.d)
TARGET = json-test

CXXFLAGS += -static -I../../src -L../../src/
LDFLAGS += -ljsonrpc

default: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

-include $(DEP)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<
	$(CXX) -MM $(CXXFLAGS) $< > $*.d

clean:
	rm -rf *.o *.d $(TARGET)
