CXX ?= g++

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
DEP = $(OBJ:.o=.d)

CXXFLAGS += -static -I../src -L../src/
LDFLAGS += -ljsonrpc -lpthread

default: $(OBJ)
	$(CXX) $(CXXFLAGS) tcp-client.o -o tcp-client-ex $(LDFLAGS)
	$(CXX) $(CXXFLAGS) tcp-server.o test-rpc.o -o tcp-server-ex $(LDFLAGS)
	$(CXX) $(CXXFLAGS) udp-client.o -o udp-client-ex $(LDFLAGS)
	$(CXX) $(CXXFLAGS) udp-server.o test-rpc.o -o udp-server-ex $(LDFLAGS)
	$(CXX) $(CXXFLAGS) system.o -o system-ex $(LDFLAGS)

-include $(DEP)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<
	$(CXX) -MM $(CXXFLAGS) $< > $*.d

clean:
	rm -rf *-ex *.o *.d
