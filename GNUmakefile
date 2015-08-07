CFLAGS = -shared -fPIC
LDLIBS = -lcrypto -lkeyutils

pam_kdf.so: pam_kdf.c
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@
