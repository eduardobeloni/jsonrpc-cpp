## 
# JsonRpc-Cpp build file.
#

# Configure compiler arguments
cflags = ['-std=c++98', '-Wall', '-W', '-pedantic', '-Wredundant-decls', '-Wshadow', '-Werror', '-O2'];

# Build with debug symbols or not
if ARGUMENTS.get('mode', 0) == 'debug':
  cflags.append('-g');

# Create an environment
env = Environment(tools = ["default", "doxygen"], toolpath = ['.', './doc'], CXXFLAGS = cflags);

# Sources and name of the JsonRpc-Cpp library
install_dir = '/usr/local';
lib_target  = 'jsonrpc';
lib_sources = ['src/jsonrpc_handler.cpp', 'src/jsonrpc_server.cpp', 'src/jsonrpc_client.cpp',
               'src/jsonrpc_udpserver.cpp', 'src/jsonrpc_tcpserver.cpp', 'src/jsonrpc_udpclient.cpp',
               'src/jsonrpc_tcpclient.cpp', 'src/netstring.cpp'];
lib_includes = ['src/jsonrpc.h', 'src/jsonrpc_handler.h', 'src/jsonrpc_server.h', 'src/jsonrpc_client.h',
                'src/jsonrpc_udpserver.h', 'src/jsonrpc_tcpserver.h', 'src/jsonrpc_udpclient.h',
                'src/jsonrpc_tcpclient.h', 'src/jsonrpc_common.h', 'src/netstring.h'];

# Build libjsonrpc
libjsonrpc = env.SharedLibrary(target = lib_target, source = lib_sources, LIBS=['json']);

# Build examples
test_sources = ['test/test-rpc.cpp'];
udpserver_sources = ['test/udp-server.cpp'];
tcpserver_sources = ['test/tcp-server.cpp'];
udpclient_sources = ['test/udp-client.cpp'];
tcpclient_sources = ['test/tcp-client.cpp'];

test = env.Object(test_sources);
tcpserver = env.Program(target = 'test/tcp-server', source = [tcpserver_sources, test], LIBS=['json', 'jsonrpc']);
udpserver = env.Program(target = 'test/udp-server', source = [udpserver_sources, test], LIBS=['json', 'jsonrpc']);
tcpclient = env.Program(target = 'test/tcp-client', source = [tcpclient_sources], LIBS=['json', 'jsonrpc']);
udpclient = env.Program(target = 'test/udp-client', source = [udpclient_sources], LIBS=['json', 'jsonrpc']);

# Install script
env.Install(dir = install_dir + "/lib/", source = libjsonrpc);
env.Install(dir = install_dir + "/include/jsonrpc/", source = lib_includes);

# Doxygen
doxygen = env.Doxygen("Doxyfile");
Clean(doxygen, "doc/doxygen.pyc");
AlwaysBuild(doxygen);
env.Alias('doxygen', doxygen);


# Alias for target
env.Alias('build', [libjsonrpc]);
env.Alias('examples', ['test/tcp-server', 'test/udp-server', 'test/tcp-client', 'test/udp-client']);
env.Alias('all', ['build', 'examples', 'doc']);
env.Alias('install', [install_dir]);

# Help documentation
Help("""
Type: 'scons build' to build JsonRpc-Cpp library,
      'scons install' to install the JsonRpc-Cpp library in the system,
      'scons doc' to build documentation (doxygen),
      'scons -c' to clean object files,
      'scons -c install' to uninstall library and include files,
      'scons -c doc' to remove documentation files.
      \n
      Default target when launching scons without argument is 'scons build.
""");

# Default target when running scons without arguments
Default('build');

