CXX ?= g++
ARM_CXX ?= arm-linux-g++

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
OBJ_ARM = $(SRC:.cpp=-arm.o)
DEP = $(OBJ:.o=.d)
TARGET = json-test
TARGET_ARM = $(TARGET)-arm

CXXFLAGS += -static -I../../src -L../../src/
LDFLAGS += -ljsonrpc

default: $(TARGET)

arm: $(TARGET_ARM)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

-include $(DEP)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<
	$(CXX) -MM $(CXXFLAGS) $< > $*.d

$(TARGET_ARM): $(OBJ_ARM)
	$(ARM_CXX) $(CXXFLAGS) $< -o $@

%-arm.o: %.cpp
	$(ARM_CXX) -c $@

clean:
	rm -rf *.o *.d $(TARGET) $(TARGET_ARM)
