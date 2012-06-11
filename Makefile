LIBNAME = libjsonrpc
PREFIX ?= /usr/local

default:
	$(MAKE) -C ./src

arm:
	$(MAKE) -C ./src ARCH=arm

clean:
	$(MAKE) -C ./src clean

install:
	install -d $(PREFIX)/lib/
	install -m 755 src/$(LIBNAME).so $(PREFIX)/lib/
	install -m 644 src/$(LIBNAME).a $(PREFIX)/lib/
	install -d $(PREFIX)/include/jsonrpc/
	install -m 644 src/*.h $(PREFIX)/include/jsonrpc/

uninstall:
	rm -f $(PREFIX)/lib/$(LIBNAME).*
	rm -rf $(PREFIX)/include/jsonrpc/
