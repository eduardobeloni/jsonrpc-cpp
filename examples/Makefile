CXX ?= g++
ARM_CXX ?= arm-linux-g++

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
OBJ_ARM = $(SRC:.cpp=-arm.o)
DEP = $(OBJ:.o=.d)

CXXFLAGS += -static -I../src -L../src/
LDFLAGS += -ljsonrpc -lpthread

default: $(OBJ)
	$(CXX) $(CXXFLAGS) tcp-client.o -o tcp-client-ex $(LDFLAGS)
	$(CXX) $(CXXFLAGS) tcp-server.o test-rpc.o -o tcp-server-ex $(LDFLAGS)
	$(CXX) $(CXXFLAGS) udp-client.o -o udp-client-ex $(LDFLAGS)
	$(CXX) $(CXXFLAGS) udp-server.o test-rpc.o -o udp-server-ex $(LDFLAGS)
	$(CXX) $(CXXFLAGS) system.o -o system-ex $(LDFLAGS)

arm: $(OBJ_ARM)
	$(ARM_CXX) $(CXXFLAGS) tcp-client-arm.o -o tcp-client-arm $(LDFLAGS)
	$(ARM_CXX) $(CXXFLAGS) tcp-server-arm.o test-rpc-arm.o -o tcp-server-arm $(LDFLAGS)
	$(ARM_CXX) $(CXXFLAGS) udp-client-arm.o -o udp-client-arm $(LDFLAGS)
	$(ARM_CXX) $(CXXFLAGS) udp-server-arm.o test-rpc-arm.o -o udp-server-arm $(LDFLAGS)
	$(ARM_CXX) $(CXXFLAGS) system-arm.o -o system-arm $(LDFLAGS)

-include $(DEP)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<
	$(CXX) -MM $(CXXFLAGS) $< > $*.d

%-arm.o: %.cpp
	$(ARM_CXX) $(CXXFLAGS) -c $<
	$(ARM_CXX) -MM $(CXXFLAGS) $< > $*.d

clean:
	rm -rf *-arm *-ex *.o *.d
