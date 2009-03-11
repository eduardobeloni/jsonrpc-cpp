## 
# JsonRpc-Cpp build file
#

# configure compiler arguments
cflags = ['-std=c++98', '-Wall', '-W', '-pedantic', '-Wredundant-decls', '-Wshadow', '-Werror'];

# Create an environment
env = Environment(tools = ["default", "doxygen"], toolpath = ['.', './doc'], CXXFLAGS = cflags);

install_dir = '/usr/local';
lib_target  = 'jsonrpc';
lib_sources = ['src/jsonrpc_handler.cpp', 'src/jsonrpc_server.cpp', 'src/jsonrpc_udpserver.cpp', 'src/jsonrpc_tcpserver.cpp', 'src/netstring.cpp'];
lib_includes = ['src/jsonrpc.h', 'src/jsonrpc_handler.h', 'src/jsonrpc_server.h', 'src/jsonrpc_udpserver.h', 'src/jsonrpc_tcpserver.h', 'src/netstring.h'];

# Build the libjsonrpc
libjsonrpc = env.SharedLibrary(target = lib_target, source = lib_sources, LIBS=['json']);

# Build examples
test_sources = ['test/test.cpp'];
udpserver_sources = ['test/udp-server.cpp'];
tcpserver_sources = ['test/tcp-server.cpp'];

test = env.Object(test_sources);
tcpserver = env.Program(target = 'test/tcp-server', source = [tcpserver_sources, test], LIBS=['json', 'jsonrpc']);
udpserver = env.Program(target = 'test/udp-server', source = [udpserver_sources, test], LIBS=['json', 'jsonrpc']);

# Install script
env.Install(dir = install_dir + "/lib/", source = libjsonrpc);
env.Install(dir = install_dir + "/include/jsonrpc/", source = lib_includes);
env.Alias('install', [install_dir]);
env.Alias('examples', ['test/tcp-server', 'test/udp-server']);

# Doxygen
doxygen = env.Doxygen("Doxyfile");
AlwaysBuild(doxygen);
env.Alias('doxygen', doxygen);

# Default target when running scons without arguments
Default(libjsonrpc);
#Default(tcpserver);
#Default(udpserver);

