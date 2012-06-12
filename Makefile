LIBNAME = libjsonrpc
PREFIX ?= /usr/local

default:
	$(MAKE) -C ./src

ex:
	$(MAKE) -C ./examples
	$(MAKE) -C ./examples/jsoncpp

clean:
	$(MAKE) -C ./src clean
	$(MAKE) -C ./examples clean
	$(MAKE) -C ./examples/jsoncpp clean

install:
	install -d $(PREFIX)/lib/
	install -m 755 src/$(LIBNAME).so $(PREFIX)/lib/
	install -m 644 src/$(LIBNAME).a $(PREFIX)/lib/
	install -d $(PREFIX)/include/jsonrpc/
	install -m 644 src/*.h $(PREFIX)/include/jsonrpc/
	install -d $(PREFIX)/include/jsoncpp/
	install -m 644 src/jsoncpp/json.h $(PREFIX)/include/jsoncpp/

uninstall:
	rm -f $(PREFIX)/lib/$(LIBNAME).*
	rm -rf $(PREFIX)/include/jsonrpc/
