CXX ?= g++
RM = rm -f

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
DEP = $(OBJ:.o=.d)
CXXFLAGS += -Wall -O2 -fpic

-include $(DEP)

default: $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(C_STD) -c $< -o $@
	$(CXX) -MM $(CXXFLAGS) $< > $*.d

clean:
	$(RM) $(TARGET) *.o *.so *.a *.d
